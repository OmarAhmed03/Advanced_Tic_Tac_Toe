#include "replayscreen.h"

    ReplayScreen::ReplayScreen(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setContentsMargins(20, 20, 20, 20); // Set margins for the main layout
    setWindowTitle("Match Replay");

    // db.createGameTable();
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
    connect(backButton, &Custom_Button::clicked, this, &ReplayScreen::handleBackClicked);
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
    movIndex = 0;

    ////////////////////////// The GRID ///////////////////////////////////
    gridLayout = new QGridLayout;
    gridLayout->setSpacing(10); // V/H grid spacing
    gridLayout->setContentsMargins(30, 10, 30, 10);


    connect(this,&ReplayScreen::ReveivedEntry,this,&ReplayScreen::ShowButtons);
    centralLayout->addLayout(gridLayout);
    //////////////////////////////////////////////////////////////////////////////////

    undoButton = new Custom_Button("↺", this);
    QFont undoFont("Segoe UI", 25);
    undoButton->setFont(undoFont);
    // Set the button to expand horizontally while maintaining its preferred height
    undoButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(undoButton, &QPushButton::clicked, this, &ReplayScreen::undo);

    redoButton = new Custom_Button("↻", this);
    redoButton->setFont(undoFont);
    // Set the button to expand horizontally while maintaining its preferred height
    redoButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(redoButton, &QPushButton::clicked, this, &ReplayScreen::redo);
    // Create a horizontal layout for the button
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignCenter);

    // Add stretchable spacers to the left and right of the button
    buttonLayout->addStretch(); // Left spacer
    buttonLayout->addWidget(undoButton);
    buttonLayout->addStretch(); // Left spacer
    buttonLayout->addWidget(redoButton); // Center button
    buttonLayout->addStretch(); // Right spacer

    // Add the button layout to the central layout
    centralLayout->addLayout(buttonLayout);



    gameEnded = false;

}

void ReplayScreen::handleBackClicked()
{
    HistoryScreen *historyScreen = new HistoryScreen();

    // Will be changed latter.
    historyScreen->setUserName(this->username);
    //
    historyScreen->show();
    this->hide();
}

void ReplayScreen::setUsername(QString username)
{
    this->username = username;
}

void ReplayScreen::setEntry(Database::GameHistoryEntry entry)
{
    this->entry = entry;
    emit ReplayScreen::ReveivedEntry();

}

    //qDebug() << this->entry.movesHistory.at(0).cMove[0][0];
void ReplayScreen::setGameId(int gameId)
{
    this->gameId = gameId;
}

void ReplayScreen::ShowButtons()
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            CellButtonR *button = new CellButtonR(this);
            // Set cell style
            button->setStyleSheet("background-color: #333333; border: 2px solid white; border-radius: 20px; color: white; font-size: 80px");
            button->setFont(QFont("Arial", 24)); // Set font size
            button->setMinimumSize(105, 105); // Set minimum size for each cell button
            gridLayout->addWidget(button, row, col);
            // connect(button, &QPushButton::clicked, this, [=](){ handleButtonClick(row, col, button); });
            char c = entry.movesHistory.at(movIndex).cMove[row][col];
            button->setText(QString(QChar::fromLatin1(c)));
            if (c == 'X')
                button->setStyleSheet("background-color: #333333; border: 2px solid #49FF00; border-radius: 20px; color: #49FF00; font-size: 80px");
            else if (c == 'O')
                button->setStyleSheet("background-color: #333333; border: 2px solid #FF1E00; border-radius: 20px; color: #FF1E00; font-size: 80px");
            cellButtons[row][col] = button; // Store the button in your array for later use
        }
    }
    QString MD;
    switch(entry.mode){
    case 0:
        MD = "Multiplayer";
        break;
    case 1:
        MD = "Easy Mode";
        break;
    case 2:
        MD = "Normal Mode";
        break;
    case 3:
        MD = "Hard Mode";
        break;
    }
    QString ResultText;
    if (entry.mode == 0){
        switch(entry.state){
        case 0:
            ResultText = "Player 1 Won";
            break;
        case 1:
            ResultText = "Draw";
            break;
        case 2:
            ResultText = "Player 2 Won";
            break;
        }

    }
    else{
        switch(entry.state){
        case 0:
            ResultText = "Player Won";
            break;
        case 1:
            ResultText = "Draw";
            break;
        case 2:
            ResultText = "AI Won";
            break;
        }
    }
    modeLabel->setText(ResultText + " on " + MD);
}
void ReplayScreen::UpdateButtons()
{
    for (int row = 0; row < 3; ++row)
    {
        for (int col = 0; col < 3; ++col)
        {
            CellButtonR *button;
            button = cellButtons[row][col]; // Store the button in your array for later use
            char c = entry.movesHistory.at(movIndex).cMove[row][col];
            button->setText(QString(QChar::fromLatin1(c)));
            if (c == 'X')
                button->setStyleSheet("background-color: #333333; border: 2px solid #49FF00; border-radius: 20px; color: #49FF00; font-size: 80px");
            else if (c == 'O')
                button->setStyleSheet("background-color: #333333; border: 2px solid #FF1E00; border-radius: 20px; color: #FF1E00; font-size: 80px");
            else
                button->setStyleSheet("background-color: #333333; border: 2px solid white; border-radius: 20px; color: white; font-size: 80px");
            cellButtons[row][col] = button;
        }
    }
}

void ReplayScreen::redo()
{

    if (movIndex >= 0 && movIndex < this->entry.movesHistory.length() - 1){
        this->movIndex++;
        UpdateButtons();
    }
}

void ReplayScreen::undo()
{
    if (movIndex > 0 && movIndex < this->entry.movesHistory.length()){
        this->movIndex--;
        UpdateButtons();
    }
}
