#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>

class GameScreen; // Forward declaration of MainWindow class

class CellButton : public QPushButton {
    Q_OBJECT

public:
    explicit CellButton(GameScreen *parent = nullptr);

signals:
    // void cellClicked(int value);

public slots:
    // void setCurrentPlayer(int player);
    // int getCurrentPlayer();
private slots:
    // void onClicked();

private:
    // int currentPlayer_;
    GameScreen *mainWindow; // Pointer to MainWindow
};

#endif // CELLBUTTON_H
