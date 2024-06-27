#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariant>
#include <QCryptographicHash>


using namespace std;
class Database
{
public:
    Database();
    ~Database();
    QString username;

    struct currentMove{
        char cMove[3][3];
        currentMove(char CMove[3][3]){
            for (int i = 0;i<3;i++){
                for (int j = 0;j<3;j++){
                    cMove[i][j] = CMove[i][j];
                }
            }
        }
    };
    struct GameHistoryEntry {
        int gameId;
        QString username;
        QString timestamp;
        int mode;
        QList<currentMove> movesHistory;
        int state;
    };
    QList<currentMove> movesHistory;
    QList<GameHistoryEntry> getAllGameHistory();
    void createTable();
    void createGameTable();
    void connClose();
    bool connOpen();
    int signup(QString username, QString password);
    int login(QString username, QString password);
    void addGameHistory0(const QString &username, const char matrix[3][3], int mode);
    bool addGameHistory(const QString &username, int mode, QList<currentMove> movesHistory, int state);
    QList<currentMove> getGameHistory(int gameId);
    char (&getBoard(int gameId, int index))[3][3];


private:
    QSqlDatabase xodb;

    QString serializeMovesHistory(QList<currentMove> movesHistory);
    QList<currentMove> deserializeMovesHistory(const QString &jsonString);




};

#endif // DATABASE_H
