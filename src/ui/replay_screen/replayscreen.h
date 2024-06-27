#ifndef REPLAY_SCREEN_H
#define REPLAY_SCREEN_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QtDebug>
// #include <limits>
#include "CellButtonR.h"
#include "../history_screen/history_screen.h"
#include "../../../utilities/Buttons/custom_button.h"
#include "../../../utilities/main_includes.h"
#include "../sign_screen/database.h"

class ReplayScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ReplayScreen(QWidget *parent = nullptr);
    // ~ReplayScreen();

    void setMode(const int &mode);
    void setUsername(QString username);
    void setEntry(Database::GameHistoryEntry entry);
    void setGameId(int gameId);
signals:
    void ReveivedEntry();
public slots:
    void ShowButtons();
    void redo();
    void undo();
private:

    QVBoxLayout *mainLayout;
    QVBoxLayout *centralLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *buttonLayout;
    Custom_Button *undoButton;
    Custom_Button *redoButton;
    Custom_Button *ReturnMenu;
    enum class Player { X, O };
    // Player currentPlayer;
    CellButtonR *cellButtons[3][3];
    char gameData[3][3];
    bool gameEnded;
    int mode;
    QString username;
    QLabel *modeLabel;
    Database::GameHistoryEntry entry;
    int movIndex;
    int gameId;
    // Database db;
    // void handleResetButtonClicked();
    void handleBackClicked();
    void UpdateButtons();
    // void handleButtonClick(int row, int col, QPushButton *button);
    // bool checkDraw();
    // bool checkWinner();
    // void disableGameButtons();
    // void enableGameButtons();
    // void btnsToArray();
    // void makeMoveEasy();
    // void makeMoveNormal();
    // void makeMoveHard();
    // int minimax(int depth, bool isMax, int maxDepth);
    // int evaluateBoard();
    // bool isMovesLeft();
    // void makeBestMove(int maxDepth);
};


#endif // GAME_SCREEN_H
