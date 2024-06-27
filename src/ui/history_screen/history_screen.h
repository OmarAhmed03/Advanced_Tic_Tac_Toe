#ifndef HISTORY_SCREEN_H
#define HISTORY_SCREEN_H

#include <QMainWindow>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QString>
#include <QScrollArea>
#include <QScrollArea>
#include <QPushButton>
#include <string>
#include "../../../utilities/main_includes.h"
#include "../../../utilities/Buttons/custom_button.h"
#include "../replay_screen/replayscreen.h"
// #include "../../../utilities/Animation/animation.h"
// #include "../game_screen/game_screen.h"
// #include "../sign_screen/sign_screen.h"
#include "../main_screen/main_screen.h"
#include "../sign_screen/database.h"

class HistoryScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryScreen(QWidget *parent = nullptr);
    void handleGoBack();
    void backToMenu();

    void setUserName(QString username);
    // ~HistoryScreen();
public slots:
    void handleReplayScreen(Database::GameHistoryEntry entry);
signals:

private:
    // Ui::HistoryScreen *ui;
    QString username;
    Database db;
    QList<Database::GameHistoryEntry> history;
};

#endif // HISTORY_SCREEN_H

