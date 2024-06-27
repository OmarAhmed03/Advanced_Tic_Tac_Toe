#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QtDebug>
#include <limits>
#include <QList>
#include "CellButton.h"
#include "../../../utilities/Buttons/custom_button.h"
#include "../../../utilities/main_includes.h"
#include "../main_screen/main_screen.h"
#include "../sign_screen/database.h"
#include <QThread>

class GameScreen : public QWidget
{
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = nullptr);
    ~GameScreen();

    void setMode(const int &mode);
    void setUsername(QString &username);
private:

    QVBoxLayout *mainLayout;
    QVBoxLayout *centralLayout;
    QHBoxLayout *buttonLayout;
    Custom_Button *resetButton;
    Custom_Button *ReturnMenu;
    enum class Player { X, O };
    Player currentPlayer;
    CellButton *cellButtons[3][3];
    char gameData[3][3];
    bool gameEnded;
    int mode;
    QString username;
    QLabel *modeLabel;
    Database db;
    QList<Database::currentMove> movesHistory;
    int state;
    void handleResetButtonClicked();
    void handleReturnClicked();
    void handleButtonClick(int row, int col, QPushButton *button);
    bool checkDraw();
    bool checkWinner();
    void disableGameButtons();
    void enableGameButtons();
    void btnsToArray();
    void makeMoveEasy();
    void makeMoveNormal();
    void makeMoveHard();
    int minimax(int depth, bool isMax, int maxDepth);
    int evaluateBoard();
    bool isMovesLeft();
    void makeBestMove(int maxDepth);
    void updateHistory();
};


#endif // GAME_SCREEN_H
