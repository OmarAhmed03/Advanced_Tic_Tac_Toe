#include "CellButtonR.h"
#include "replayscreen.h"



CellButtonR::CellButtonR(ReplayScreen *parent) : QPushButton(parent), mainWindow(parent) {
    setText("");
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFixedSize(120, 120); // Set fixed size for the button
    setFocusPolicy(Qt::NoFocus);
    setStyleSheet("background-color: black; border: 2px solid white; color: white; font-size: 80px"); // Set button style and font size
    // connect(this, &QPushButton::clicked, this, &CellButton::onClicked);
    // currentPlayer_ = 1;
}



// void CellButton::setCurrentPlayer(int player) {
//     currentPlayer_ = player;
// }

// int CellButton::getCurrentPlayer() {
//     return currentPlayer_;
// }
