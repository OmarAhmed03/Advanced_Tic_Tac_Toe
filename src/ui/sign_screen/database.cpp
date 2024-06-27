#include "database.h"

Database::Database() {
    createTable();
}

Database::~Database()
{
}

void Database::createTable()
{
    connOpen();
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS PLAYERDATA("
               "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "USERNAME TEXT NOT NULL UNIQUE, "
               "PASSWORD TEXT NOT NULL)");

    query.clear();
    connClose();
}

void Database::createGameTable()
{
    connOpen();
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS GAMEHISTORY("
               "GameID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "USERNAME TEXT NOT NULL, "
               "moves_history TEXT, "
               "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP, "
               "MODE INTEGER, "
               "STATE INTEGER, "
               "FOREIGN KEY(username) REFERENCES PlayerData(username))"
               );
    QSqlError last_error = query.lastError();
    qDebug() << last_error;
    query.clear();
    connClose();
}

void Database::connClose()
{
    xodb.close();
    xodb.removeDatabase(QSqlDatabase::defaultConnection);
}

bool Database::connOpen()
{
    xodb = QSqlDatabase::addDatabase("QSQLITE");

    xodb.setDatabaseName("database1.db");

    if(!xodb.open()){
        qDebug() << "Failed to open the database "<<"\n";
        return false;
    }
    else
        qDebug() << "Connected.... "<<"\n";
    return true;
}

int Database::signup(QString username,QString password)
{
    connOpen();
    // return codes: 1-inserted succesfully , 0-Error ,2-Username is already registered
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    QString pp = QString(hashedPassword);
    QSqlQuery query;
    query.prepare("INSERT INTO PLAYERDATA (USERNAME , PASSWORD) VALUES (?,?)");
    query.addBindValue(username);
    query.addBindValue(pp);
    if (!query.exec()){
        QSqlError last_error = query.lastError();
        if(last_error.nativeErrorCode() == "2067"){
            qDebug() << "Username is already registered";
            query.clear();
            connClose();
            return 2;
        }
        qDebug() << last_error;
        query.clear();
        connClose();
        return 0;
    }
    query.clear();
    connClose();
    return 1;
}

int Database::login(QString username, QString password)
{
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
    QString pp = QString(hashedPassword);
    connOpen();
    QSqlQuery query;
    query.prepare("SELECT username, password FROM PLAYERDATA Where username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(pp); // Store the hashed password
    QSqlError last_error = query.lastError();
    qDebug() << last_error;
    if (query.exec()){
        int count = 0;
        while(query.next()){
            count++;
        }
        if(count ==1){
            qDebug() << "login success";
            this->username = username;
            connClose();
            return 1;
        }
        else{
            qDebug() << "wrong username or password";
            qDebug() << hashedPassword <<"\n";
            connClose();
            return 0;
        }
    }
}
QString Database::serializeMovesHistory(QList<currentMove>movesHistory) {
    QJsonArray jsonArray;
    for (const auto &move : movesHistory) {
        QJsonArray rowArray;
        for (int i = 0; i < 3; ++i) {
            QJsonArray colArray;
            for (int j = 0; j < 3; ++j) {
                colArray.append(QJsonValue(QChar(move.cMove[i][j])));
            }
            rowArray.append(colArray);
        }
        jsonArray.append(rowArray);
    }
    QJsonDocument jsonDoc(jsonArray);
    return jsonDoc.toJson(QJsonDocument::Compact);
}

QList<Database::currentMove> Database::deserializeMovesHistory(const QString &jsonString) {
    QList<currentMove> movesHistory;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray jsonArray = jsonDoc.array();

    for (const auto &jsonMove : jsonArray) {
        QJsonArray rowArray = jsonMove.toArray();
        char matrix[3][3];
        for (int i = 0; i < 3; ++i) {
            QJsonArray colArray = rowArray[i].toArray();
            for (int j = 0; j < 3; ++j) {
                matrix[i][j] = colArray[j].toString().at(0).toLatin1();
            }
        }
        movesHistory.append(currentMove(matrix));
    }

    return movesHistory;
}



bool Database::addGameHistory(const QString &username, int mode, QList<currentMove> movesHistory, int state) {
    connOpen();
    QSqlQuery query;
    query.prepare("INSERT INTO GAMEHISTORY (username, mode, moves_history, state) VALUES (?, ?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(mode);
    query.addBindValue(serializeMovesHistory(movesHistory));
    query.addBindValue(state);
    if (!query.exec()) {
        qDebug() << "Failed to add game history:" << query.lastError();
        query.clear();
        connClose();
        return false;
    }
    query.clear();
    connClose();
    return true;

}

QList<Database::currentMove> Database::getGameHistory(int gameId) {
    QSqlQuery query;
    query.prepare("SELECT moves_history FROM GameHistory WHERE game_id = :game_id");
    query.bindValue(":game_id", gameId);

    if (!query.exec()) {
        qDebug() << "Failed to retrieve game history:" << query.lastError();
        return QList<currentMove>();
    }

    if (query.next()) {
        QString jsonString = query.value(0).toString();
        return deserializeMovesHistory(jsonString);
    }

    return QList<currentMove>();
}



QList<Database::GameHistoryEntry> Database::getAllGameHistory() {
    connOpen();
    QList<GameHistoryEntry> allGamesHistory;
    QSqlQuery query("SELECT GameID, username, timestamp, mode, moves_history, state FROM GAMEHISTORY");

    if (!query.exec()) {
        qDebug() << "Failed to retrieve all game histories:" << query.lastError();
        return allGamesHistory;
    }

    while (query.next()) {
        int gameId = query.value(0).toInt();
        QString username = query.value(1).toString();
        QString timestamp = query.value(2).toString();
        int mode = query.value(3).toInt();
        QString jsonString = query.value(4).toString();
        int state = query.value(5).toInt();
        QList<currentMove> movesHistory = deserializeMovesHistory(jsonString);
        allGamesHistory.append ({gameId, username, timestamp, mode, movesHistory, state});
    }
    query.clear();
    connClose();
    return allGamesHistory;
}



void Database::addGameHistory0(const QString &username, const char matrix[3][3], int mode)
{
    connOpen();
    QJsonArray jsonArray;
    for (int i = 0; i < 3; ++i) {
        QJsonArray rowArray;
        for (int j = 0; j < 3; ++j) {
            rowArray.append(QString(matrix[i][j]));
        }
        jsonArray.append(rowArray);
    }
    QJsonDocument jsonDoc(jsonArray);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

    QSqlQuery query;
    query.prepare("INSERT INTO GameHistory (username, matrix_column, mode) VALUES (?,?,?)");
    query.addBindValue(username);
    query.addBindValue(jsonString);
    query.addBindValue(mode);
    if (!query.exec()) {
        qDebug() << "Failed to insert game history:" << query.lastError();
    }
    query.clear();
    connClose();
}





