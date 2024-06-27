#include "main_screen.h"

MainScreen::MainScreen(QWidget *parent) :
    QWidget{parent}
{
    setWindowTitle("Tic Tac Toe");

    // Create the vertical layout for the main screen
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // standard
    setFixedSize(standard_Width, standard_height);

    // Create a horizontal layout for the toolbar
    QHBoxLayout *toolbarLayout = new QHBoxLayout();
    toolbarLayout->setSpacing(10);
    toolbarLayout->setAlignment(Qt::AlignTop); // Align top without specific alignment for left or right

    // Create the logout button
    Custom_Button *logoutButton = new Custom_Button("↩", this);

    QFont bannerFont("Segoe UI", 15);
    logoutButton->setFont(bannerFont);

    logoutButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    toolbarLayout->addWidget(logoutButton);
    connect(logoutButton, &Custom_Button::clicked, this, &MainScreen::handleLogout);

    // Add a spacer to push the history button to the right
    QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    toolbarLayout->addItem(spacer);

    // Create the History button
    Custom_Button *historyButton = new Custom_Button("≡", this);
    historyButton->setFont(bannerFont);

    historyButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    toolbarLayout->addWidget(historyButton);
    connect(historyButton, &Custom_Button::clicked, this, &MainScreen::handleHistory);

    // Add the toolbar layout to the main layout
    mainLayout->addLayout(toolbarLayout);


    // Add spacing
    mainLayout->addSpacing(80);

    // Title label with variable
    QLabel *userLabel = new QLabel(this);
    userLabel->setAlignment(Qt::AlignCenter);
    userLabel->setStyleSheet("font-weight: bold; font-size: 24px;");
    mainLayout->addWidget(userLabel);

    mainLayout->addSpacing(40);

    // Label for game mode selection
    QLabel *modeLabel = new QLabel("Choose Game Mode:", this);
    modeLabel->setStyleSheet("font-size: 16px;"); // Set font size
    modeLabel->setAlignment(Qt::AlignCenter); // Align center
    mainLayout->addWidget(modeLabel);

    mainLayout->addSpacing(20);

    Custom_Button *custButton = new Custom_Button("Multiplayer", this);

    QFont btnFont("Segoe UI", 15, QFont::Bold);
    custButton->setFont(btnFont);

    custButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mainLayout->addWidget(custButton);
    connect(custButton, &Custom_Button::clicked, this, &MainScreen::handleMultiplayer);

    Custom_Button *custButton2 = new Custom_Button("Single Player", this);

    custButton2->setFont(btnFont);

    custButton2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    mainLayout->addWidget(custButton2);

    // Create the difficulty buttons (easy, normal, hard)
    Custom_Button *easyButton = new Custom_Button("Easy", this);

    QFont btn2Font("Segoe UI", 10);
    easyButton->setFont(btn2Font);

    easyButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(easyButton, &Custom_Button::clicked, this, &MainScreen::handleSingleplayerEasy);

    Custom_Button *normalButton = new Custom_Button("Normal", this);

    normalButton->setFont(btn2Font);

    normalButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(normalButton, &Custom_Button::clicked, this, &MainScreen::handleSingleplayerNormal);

    Custom_Button *hardButton = new Custom_Button("Hard", this);

    hardButton->setFont(btn2Font);

    hardButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(hardButton, &Custom_Button::clicked, this, &MainScreen::handleSingleplayerHard);

    // Hide the difficulty buttons initially
    easyButton->hide();
    normalButton->hide();
    hardButton->hide();

    // Add the difficulty buttons to a horizontal layout
    QHBoxLayout *difficultyLayout = new QHBoxLayout();
    difficultyLayout->addWidget(easyButton);
    difficultyLayout->addWidget(normalButton);
    difficultyLayout->addWidget(hardButton);
    mainLayout->addLayout(difficultyLayout);

    bool difficultyVisible = false;

    // Connect the Single Player button to show/hide the difficulty buttons with fade animation
    QObject::connect(custButton2, &Custom_Button::clicked, [=]() mutable {
        if (!difficultyVisible) {
            easyButton->show();
            normalButton->show();
            hardButton->show();
            createFadeAnimation(easyButton, true);
            createFadeAnimation(normalButton, true);
            createFadeAnimation(hardButton, true);
        } else {
            createFadeAnimation(easyButton, false);
            createFadeAnimation(normalButton, false);
            createFadeAnimation(hardButton, false);
        }
        difficultyVisible = !difficultyVisible;
    });
}

void MainScreen::setUserName(QString userName)
{
    this->userName = userName;
    QLabel *userLabel = findChild<QLabel *>();
    if (userLabel)
        userLabel->setText(("Welcome back, " + userName));
}

void MainScreen::handleLogout()
{
    SignScreen *signWindow = new SignScreen();
    signWindow->show();
    this->hide();
}

void MainScreen::handleHistory()
{
    HistoryScreen *historyWindow = new HistoryScreen();
    historyWindow->show();
    historyWindow->setUserName(this->userName);
    this->hide();
}

void MainScreen::handleMultiplayer()
{
    GameScreen *gameWindow = new GameScreen();
    gameWindow->setUsername(this->userName);
    gameWindow->setMode(0);
    gameWindow->show();
    this->hide();
}

void MainScreen::handleSingleplayerEasy()
{
    GameScreen *gameWindow = new GameScreen();
    gameWindow->setUsername(this->userName);
    gameWindow->setMode(1);
    gameWindow->show();
    this->hide();
}

void MainScreen::handleSingleplayerNormal()
{
    GameScreen *gameWindow = new GameScreen();
    gameWindow->setUsername(this->userName);
    gameWindow->setMode(2);
    gameWindow->show();
    this->hide();
}

void MainScreen::handleSingleplayerHard()
{
    GameScreen *gameWindow = new GameScreen();
    gameWindow->setUsername(this->userName);
    gameWindow->setMode(3);
    gameWindow->show();
    this->hide();
}
