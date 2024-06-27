#ifndef CELLBUTTONR_H
#define CELLBUTTONR_H

#include <QPushButton>

class ReplayScreen; // Forward declaration of MainWindow class

class CellButtonR : public QPushButton {
    Q_OBJECT

public:
    explicit CellButtonR(ReplayScreen *parent = nullptr);

signals:
    // void cellClicked(int value);

public slots:
    // void setCurrentPlayer(int player);
    // int getCurrentPlayer();
private slots:
    // void onClicked();

private:
    // int currentPlayer_;
    ReplayScreen *mainWindow; // Pointer to MainWindow
};

#endif // CELLBUTTONR_H
