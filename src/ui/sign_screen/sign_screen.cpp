#include "sign_screen.h"

SignScreen::SignScreen(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(standard_Width, standard_height);
    //setStyleSheet("background-color:blue;");
    main_layout = new QVBoxLayout(this); // Set the main_layout directly with 'this' as parent
    main_layout->setAlignment(Qt::AlignCenter);
    main_layout->setContentsMargins(40, 0, 40, 0); // Set margin from right and left sides

    // Header Label
    QLabel *headerLabel = new QLabel("Registration", this);
    headerLabel->setAlignment(Qt::AlignCenter);
    QFont font("Segoe UI", 24, QFont::Bold);
    headerLabel->setFont(font);
    main_layout->addWidget(headerLabel);
    main_layout->addSpacing(120);

    // Username
    QVBoxLayout *user_name_layout = new QVBoxLayout(); // Define user_name_layout
    user_name = new QLabel("Username:");
    user_name_edit = new QLineEdit();
    user_name_edit->setStyleSheet("padding: 15px;"); // Add padding
    user_name_layout->addWidget(user_name);
    user_name_layout->addWidget(user_name_edit);
    main_layout->addLayout(user_name_layout);
    main_layout->addSpacing(20);

    // Password
    QVBoxLayout *password_layout = new QVBoxLayout(); // Define password_layout
    password = new QLabel("Password:");
    password_edit = new QLineEdit();
    password_edit->setEchoMode(QLineEdit::EchoMode::Password);
    password_edit->setStyleSheet("padding: 15px;"); // Add padding
    password_layout->addWidget(password);
    password_layout->addWidget(password_edit);
    main_layout->addLayout(password_layout);
    main_layout->addSpacing(20);

    // Buttons
    QHBoxLayout *button_layout = new QHBoxLayout(); // Define button_layout
    login = new Custom_Button("login");
    signup = new Custom_Button("signup");
    login->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    signup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    button_layout->addWidget(login);
    button_layout->addWidget(signup);
    main_layout->addLayout(button_layout);

    db.createTable();
    connect(signup, &QPushButton::clicked, this, &SignScreen::signup_pressed);
    connect(login, &QPushButton::clicked, this, &SignScreen::login_pressed);
}

void SignScreen::signup_pressed() {
    int signed_up = db.signup(user_name_edit->text(), password_edit->text());
    if (signed_up == 1) {
        msgBox.setText("Signed Up Successfully");
        msgBox.exec();
    } else if (signed_up == 2) {
        msgBox.setText("Username is already registered");
        msgBox.exec();
    } else {
        msgBox.setText("Error in the database");
        msgBox.exec();
    }
}

void SignScreen::login_pressed() {
    int logged_in = db.login(user_name_edit->text(), password_edit->text());

    if (logged_in == 1) {
        MainScreen *mainScreen = new MainScreen();
        mainScreen->setUserName(user_name_edit->text());
        mainScreen->show();
        this->hide();
    } else {
        msgBox.setText("Wrong username or password");
        msgBox.exec();
    }
}
