#ifndef SIGN_SCREEN_H
#define SIGN_SCREEN_H

#include <QMainWindow>
#include <QWidget>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QLayout>
#include <QPixmap>
#include <QFile>
#include "../../../utilities/Buttons/custom_button.h"
#include "../../../utilities/main_includes.h"
#include "../main_screen/main_screen.h"
#include "database.h"

class SignScreen : public QWidget
{
    Q_OBJECT
public:
    explicit SignScreen(QWidget *parent = nullptr);

public slots:
    //void login_pressed();
    void signup_pressed();
    void login_pressed();
private:
    QVBoxLayout *main_layout;
    QHBoxLayout *row1;
    QHBoxLayout *row2;
    QHBoxLayout *row3;
    QLabel* user_name;
    QLineEdit* user_name_edit;
    QLabel* password;
    QLineEdit* password_edit;
    QMessageBox msgBox;
    Custom_Button* login;
    Custom_Button* signup;
    Database db;
};
#endif // SIGN_SCREEN_H
