#include "game_screen.h"

GameScreen::GameScreen(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setContentsMargins(20, 20, 20, 20); // Set margins for the main layout
    setWindowTitle("XO Match");

    db.createGameTable();
    // Set standard W,H
    setFixedSize(standard_Width, standard_height);

    // Create a horizontal layout for the toolbar
    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    toolbarLayout->setSpacing(10);
    toolbarLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop); // Align top left

    // Create the back button
    Custom_Button *backButton = new Custom_Button("↩", this);

    QFont bannerFont("Segoe UI", 15);
    backButton->setFont(bannerFont);

    backButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    toolbarLayout->addWidget(backButton);
    toolbarLayout->addStretch(); // Add a stretch spacer to push everything else to the left
    connect(backButton, &Custom_Button::clicked, this, &GameScreen::handleReturnClicked);
    mainLayout->addLayout(toolbarLayout);

    // mode label with variable
    modeLabel = new QLabel(this);
    modeLabel->setAlignment(Qt::AlignCenter);
    QFont modeFont("Segoe UI", 15);
    modeLabel->setFont(modeFont);
    mainLayout->addWidget(modeLabel);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->setAlignment(Qt::AlignCenter);
    centralLayout->setSpacing(20); // Set spacing between widgets
    centralWidget->setLayout(centralLayout);

    mainLayout->addWidget(centralWidget);

    ////////////////////////// The GRID ///////////////////////////////////
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setSpacing(10); // V/H grid spacing
    gridLayout->setContentsMargins(30, 10, 30, 10);

    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            CellButton *button = new CellButton(this);
            // Set cell style
            button->setStyleSheet("background-color: #333333; border: 2px solid white; border-radius: 20px; color: white; font-size: 80px");
            button->setFont(QFont("Arial", 24)); // Set font size
            button->setMinimumSize(105, 105); // Set minimum size for each cell button
            gridLayout->addWidget(button, row, col);
            connect(button, &QPushButton::clicked, this, [=](){ handleButtonClick(row, col, button); });
            cellButtons[row][col] = button; // Store the button in your array for later use

        }
    }

    centralLayout->addLayout(gridLayout);
    //////////////////////////////////////////////////////////////////////////////////

    resetButton = new Custom_Button("⟳", this);

    QFont resetFont("Segoe UI", 25);
    resetButton->setFont(resetFont);

    // Set the button to expand horizontally while maintaining its preferred height
    resetButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // Create a horizontal layout for the button
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignCenter);

    // Add stretchable spacers to the left and right of the button
    buttonLayout->addStretch(); // Left spacer
    buttonLayout->addWidget(resetButton); // Center button
    buttonLayout->addStretch(); // Right spacer

    // Add the button layout to the central layout
    centralLayout->addLayout(buttonLayout);

    connect(resetButton, &QPushButton::clicked, this, &GameScreen::handleResetButtonClicked);

    // Initialize the game state to player X
    currentPlayer = Player::X;

    // Initialize gameEnded to false
    gameEnded = false;


}

////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief Used Functions
///

void GameScreen::setMode(const int &mode)
{
    /*
     *
     * 0 -> Multiplayer
     *
     * 1 -> Single Player (Easy)
     * 2 -> Single Player (Norm)
     * 3 -> Single Player (Hard)
     *
     */

    this->mode = mode;

    QString modeString;

    switch (mode)
    {
    case 0:
        modeString = "Multiplayer";
        break;
    case 1:
        modeString = "Single Player (Easy)";
        break;
    case 2:
        modeString = "Single Player (Normal)";
        break;
    case 3:
        modeString = "Single Player (Hard)";
        break;
    default:
        modeString = "Unknown Mode";
        break;
    }

    if (modeLabel)
    {
        modeLabel->setText(modeString);
    }
}
void GameScreen::setUsername(QString &username)
{
    this->username = username;
}

GameScreen::~GameScreen()
{
    // TODO :: Destructor Implementation
}

void GameScreen::handleReturnClicked()
{
    MainScreen *mainScreen = new MainScreen();

    // Will be changed latter.
    mainScreen->setUserName(this->username);
    //
    mainScreen->show();
    this->hide();
}

void GameScreen::handleResetButtonClicked()
{
    // Reset the game
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            cellButtons[row][col]->setText("");
        }
    }
    currentPlayer = Player::X; // Reset the current player to Player::X
    gameEnded = false; // Reset gameEnded to false
    this->movesHistory.clear();
    //db.addGameHistory(this->username, mode, this->movesHistory, this->state);
    enableGameButtons(); // Enable game buttons
}

bool GameScreen::checkDraw()
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if(cellButtons[row][col]->text() == "")
            {
                return 0;
            }
        }
    }

    return 1;
}

bool GameScreen::checkWinner()
{
    // Check rows
    for (int row = 0; row < 3; ++row)
    {
        if (cellButtons[row][0]->text() != "" &&
            cellButtons[row][0]->text() == cellButtons[row][1]->text() &&
            cellButtons[row][1]->text() == cellButtons[row][2]->text())
            return true;
    }

    // Check columns
    for (int col = 0; col < 3; ++col)
    {
        if (cellButtons[0][col]->text() != "" &&
            cellButtons[0][col]->text() == cellButtons[1][col]->text() &&
            cellButtons[1][col]->text() == cellButtons[2][col]->text())
            return true;
    }

    // Check diagonals
    if (cellButtons[0][0]->text() != "" &&
        cellButtons[0][0]->text() == cellButtons[1][1]->text() &&
        cellButtons[1][1]->text() == cellButtons[2][2]->text())
        return true;

    if (cellButtons[0][2]->text() != "" &&
        cellButtons[0][2]->text() == cellButtons[1][1]->text() &&
        cellButtons[1][1]->text() == cellButtons[2][0]->text())
        return true;

    return false;
}

void GameScreen::disableGameButtons()
{
    QString btn;
    // Disable all game buttons
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            btn = (cellButtons[row][col]->text());
            if (btn == "X" || btn == "O")
                gameData[row][col] = btn.at(0).toLatin1();
            else
                gameData[row][col] = ' ';
            cellButtons[row][col]->setEnabled(false);

        }
    }
}

void GameScreen::enableGameButtons()
{
    // Enable all game buttons
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            cellButtons[row][col]->setEnabled(true);

            cellButtons[row][col]->setStyleSheet("background-color: #333333; border: 2px solid white; border-radius: 20px; color: white; font-size: 80px");

        }
    }
}

void GameScreen::btnsToArray()
{
    QString btn;
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            btn = (cellButtons[row][col]->text());
            if (btn == "X" || btn == "O")
                gameData[row][col] = btn.at(0).toLatin1();
            else
                gameData[row][col] = ' ';
            //qDebug() << gameData[row][col]<<"\n";

        }

    }

}

void GameScreen::handleButtonClick(int row, int col, QPushButton *button)
{

    if(this->mode == 0)
    // Multiplayer mode
    {
        if (!gameEnded && button->text() == "")
        {
            if (currentPlayer == Player::X)
            {
                button->setText("X");
                button->setStyleSheet("background-color: #333333; border: 2px solid #49FF00; border-radius: 20px; color: #49FF00; font-size: 80px");
            }
            else
            {
                button->setText("O");
                button->setStyleSheet("background-color: #333333; border: 2px solid #FF1E00; border-radius: 20px; color: #FF1E00; font-size: 80px");
            }

            // Check for a winner
            if (checkWinner())
            {
                gameEnded = true; // Set gameEnded to true
                QString winnerText = (currentPlayer == Player::X) ? "Player X Won!" : "Player O Won!";
                state = (currentPlayer == Player::X) ? 0:2;
                QMessageBox::information(this, "Game Over", winnerText);
                disableGameButtons(); // Disable game buttons

                ////////////////////////////////////////
                // Game will be added to history here //
                //           Multiplayer Mode         //
                ////////////////////////////////////////

            }
            else if(checkDraw())
            {
                gameEnded = true; // Set gameEnded to true
                QString winnerText = "Draw!";
                state = 1;
                QMessageBox::information(this, "Game Over", winnerText);
                disableGameButtons(); // Disable game buttons

                ////////////////////////////////////////
                // Game will be added to history here //
                //        Multiplayer Mode Draw       //
                ////////////////////////////////////////

            }
            else
            {
                // Switch players
                currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
            }
        }
    }
    else
    // Single Player Mode
    {
        if (!gameEnded && button->text() == "")
        {
            button->setText("X");
            button->setStyleSheet("background-color: #333333; border: 2px solid #49FF00; border-radius: 20px; color: #49FF00; font-size: 80px");
            //QThread::msleep(500);
            // Check for a winner
            if (checkWinner())
            {
                gameEnded = true; // Set gameEnded to true
                QString winnerText = (currentPlayer == Player::X) ? "You Won!" : "AI Won!";
                QMessageBox::information(this, "Game Over", winnerText);
                state = (currentPlayer == Player::X) ? 0:2;
                disableGameButtons(); // Disable game buttons

                ////////////////////////////////////////
                // Game will be added to history here //
                //         Singleplayer Mode          //
                ////////////////////////////////////////

            }
            else if(checkDraw())
            {
                gameEnded = true; // Set gameEnded to true
                QString winnerText = "Draw!";
                QMessageBox::information(this, "Game Over", winnerText);
                state = 1;
                disableGameButtons(); // Disable game buttons

                ////////////////////////////////////////
                // Game will be added to history here //
                //       Singleplayer Mode Draw       //
                ////////////////////////////////////////
            }
            else
            {
                // Switch players
                currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;

                ////////////////////
                /// \brief makeMoves
                ///switch between modes

                if(this->mode == 1)
                {
                    // Easy Mode
                    updateHistory();
                    makeMoveEasy();
                }
                else if(this->mode == 2)
                {
                    // Normal Mode
                    updateHistory();
                    makeMoveNormal();
                }
                else if(this->mode == 3)
                {
                    // Hard Mode
                    updateHistory();
                    makeMoveHard();
                }

                //////////////////////////
                /////////////////////////

                // Check for a winner
                if (checkWinner())
                {
                    gameEnded = true; // Set gameEnded to true
                    QString winnerText = (currentPlayer == Player::X) ? "You Won!" : "AI Won!";
                    state = (currentPlayer == Player::X) ? 0:2;
                    QMessageBox::information(this, "Game Over", winnerText);
                    disableGameButtons(); // Disable game buttons

                    ////////////////////////////////////////
                    // Game will be added to history here //
                    ////////////////////////////////////////

                }
                else if(checkDraw())
                {
                    gameEnded = true; // Set gameEnded to true
                    QString winnerText = "Draw!";
                    state = 1;
                    QMessageBox::information(this, "Game Over", winnerText);
                    disableGameButtons(); // Disable game buttons

                    ////////////////////////////////////////
                    // Game will be added to history here //
                    ////////////////////////////////////////
                }
                else
                {
                    // Switch players
                    currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
                }
            }
        }
    }
    // Disable all game buttons
    updateHistory();
    //qDebug() << "Grid saved \n";
    if (gameEnded){
        qDebug() << mode << '\n';
        db.addGameHistory(this->username, mode, this->movesHistory, this->state);
    }
}

////////////////////////////////////////
////////// Mini Max Algorithm //////////
////////////////////////////////////////

/*
 * This Algorithm will be used in normal and hard mode only.
 *
 * makeMoveNormal: Uses the MiniMax algorithm but limits the depth of the search to make it less challenging.
 * makeMoveHard: Uses the MiniMax algorithm with full depth to play optimally.
 *
 */

int GameScreen::evaluateBoard()
{
    // Check rows and columns for a win
    for (int i = 0; i < 3; i++)
    {
        if (cellButtons[i][0]->text() == cellButtons[i][1]->text() && cellButtons[i][1]->text() == cellButtons[i][2]->text())
        {
            if (cellButtons[i][0]->text() == "O") return +10;
            else if (cellButtons[i][0]->text() == "X") return -10;
        }
        if (cellButtons[0][i]->text() == cellButtons[1][i]->text() && cellButtons[1][i]->text() == cellButtons[2][i]->text())
        {
            if (cellButtons[0][i]->text() == "O") return +10;
            else if (cellButtons[0][i]->text() == "X") return -10;
        }
    }

    // Check diagonals for a win
    if (cellButtons[0][0]->text() == cellButtons[1][1]->text() && cellButtons[1][1]->text() == cellButtons[2][2]->text())
    {
        if (cellButtons[0][0]->text() == "O") return +10;
        else if (cellButtons[0][0]->text() == "X") return -10;
    }
    if (cellButtons[0][2]->text() == cellButtons[1][1]->text() && cellButtons[1][1]->text() == cellButtons[2][0]->text())
    {
        if (cellButtons[0][2]->text() == "O") return +10;
        else if (cellButtons[0][2]->text() == "X") return -10;
    }

    return 0;
}

bool GameScreen::isMovesLeft()
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if (cellButtons[row][col]->text() == "")
            {
                return true;
            }
        }
    }
    return false;
}

int GameScreen::minimax(int depth, bool isMax, int maxDepth)
{
    int score = evaluateBoard();

    if (score == 10) return score - depth;
    if (score == -10) return score + depth;
    if (!isMovesLeft()) return 0;
    if (depth == maxDepth) return 0;

    if (isMax) {
        int best = -1000;

        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                if (cellButtons[row][col]->text() == "")
                {
                    cellButtons[row][col]->setText("O");
                    best = qMax(best, minimax(depth + 1, !isMax, maxDepth));
                    cellButtons[row][col]->setText("");
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;

        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                if (cellButtons[row][col]->text() == "")
                {
                    cellButtons[row][col]->setText("X");
                    best = qMin(best, minimax(depth + 1, !isMax, maxDepth));
                    cellButtons[row][col]->setText("");
                }
            }
        }
        return best;
    }
}

void GameScreen::makeBestMove(int maxDepth)
{
    int bestVal = -1000;
    QPair<int, int> bestMove = qMakePair(-1, -1);

    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if (cellButtons[row][col]->text() == "")
            {
                cellButtons[row][col]->setText("O");
                int moveVal = minimax(0, false, maxDepth);
                cellButtons[row][col]->setText("");

                if (moveVal > bestVal)
                {
                    bestMove.first = row;
                    bestMove.second = col;
                    bestVal = moveVal;
                }
            }
        }
    }

    cellButtons[bestMove.first][bestMove.second]->setText("O");
    cellButtons[bestMove.first][bestMove.second]->setStyleSheet("background-color: #333333; border: 2px solid #FF1E00; border-radius: 20px; color: #FF1E00; font-size: 80px");
}


////////////////////////////////////////

void GameScreen::makeMoveEasy()
{
    // Make a random move
    QVector<QPair<int, int>> availableMoves;

    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            if (cellButtons[row][col]->text() == "")
            {
                availableMoves.append(qMakePair(row, col));
            }
        }
    }

    if (!availableMoves.isEmpty())
    {
        int randomIndex = QRandomGenerator::global()->bounded(availableMoves.size());
        QPair<int, int> move = availableMoves[randomIndex];
        cellButtons[move.first][move.second]->setText("O");
        cellButtons[move.first][move.second]->setStyleSheet("background-color: #333333; border: 2px solid #FF1E00; border-radius: 20px; color: #FF1E00; font-size: 80px");
    }

    // Another dummy algo.
/*
    // for(int i = 0 ; i < 3 ; ++i)
    // {
    //     for(int j = 0 ; j < 3 ; ++j)
    //     {
    //         if(cellButtons[i][j]->text() == "")
    //         {
    //             cellButtons[i][j]->setText("O");
    //             cellButtons[i][j]->setStyleSheet("background-color: #333333; border: 2px solid #FF1E00; border-radius: 20px; color: #FF1E00; font-size: 80px");
    //             return;
    //         }
    //     }
    // }
*/
}

void GameScreen::makeMoveNormal()
{
    makeBestMove(NORMAL_MODE_DEPTH);
}

void GameScreen::makeMoveHard()
{
    makeBestMove(HARD_MODE_DEPTH);
}

void GameScreen::updateHistory()
{
    QString btn;
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            btn = (cellButtons[row][col]->text());
            if (btn == "X" || btn == "O")
                gameData[row][col] = btn.at(0).toLatin1();
            else
                gameData[row][col] = ' ';
        }
    }
    Database::currentMove cm(gameData);
    movesHistory.append(cm);

}
