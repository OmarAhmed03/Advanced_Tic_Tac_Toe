#include "custom_button.h"

Custom_Button::Custom_Button(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setStyleSheet("QPushButton {"
                  "    background-color: yellow;"
                  "    border-radius: 20px;"
                  "    border: 2px solid darkyellow;"
                  "    color: black;"
                  "    font-weight: bold;"
                  "    padding: 15px 15px;"
                  "    margin: 0 5px;" // Add 20px margin
                  "}"
                  "QPushButton:pressed {"
                  "    background-color: darkyellow;"
                  "}"
                  "QPushButton:hover {"
                  "    background-color: lightyellow;"
                  "}"
                  "QPushButton:focus {"
                  "    border: 2px solid darkyellow;"
                  "    outline: none;"
                  "}"
                  "QPushButton:disabled {"
                  "    background-color: #c0c0c0;"
                  "    color: #808080;"
                  "}"
                  "QPushButton:disabled:hover {"
                  "    background-color: #c0c0c0;"
                  "}"
                  );

    connect(this, &QPushButton::pressed, this, &Custom_Button::handlePressed);
    connect(this, &QPushButton::released, this, &Custom_Button::handleReleased);
}

Custom_Button::~Custom_Button()
{
}

void Custom_Button::handlePressed()
{
    setPressedEffect(true); // Apply the pressed effect
}

void Custom_Button::handleReleased()
{
    setPressedEffect(false); // Revert back to the normal style
}

void Custom_Button::setPressedEffect(bool enabled)
{
    if (enabled) {
        // Apply the pressed effect
        setStyleSheet("QPushButton {"
                      "    background-color: orange;"
                      "    border-radius: 20px;"
                      "    border: 2px solid darkyellow;"
                      "    color: black;"
                      "    font-weight: bold;"
                      "    padding: 15px 15px;"
                      "    margin: 0 5px;" // Add 20px margin
                      "}"
                      );
    } else {
        // Revert back to the normal style
        setStyleSheet("QPushButton {"
                      "    background-color: yellow;"
                      "    border-radius: 20px;"
                      "    border: 2px solid darkyellow;"
                      "    color: black;"
                      "    font-weight: bold;"
                      "    padding: 15px 15px;"
                      "    margin: 0 5px;" // Add 20px margin
                      "}"
                      "QPushButton:hover {"
                      "    background-color: lightyellow;"
                      "}"
                      "QPushButton:focus {"
                      "    border: 2px solid darkyellow;"
                      "    outline: none;"
                      "}"
                      "QPushButton:disabled {"
                      "    background-color: #c0c0c0;"
                      "    color: #808080;"
                      "}"
                      "QPushButton:disabled:hover {"
                      "    background-color: #c0c0c0;"
                      "}"
                      );
    }
}
