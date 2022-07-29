#ifndef PLATFORMGAME_BUTTON_H
#define PLATFORMGAME_BUTTON_H

#include "headers.h"

enum BUTTON_STATES{IDLE, PRESSED, HOVER};


class Button {

public:

    Button(sf::Vector2f size, sf::Vector2f position, sf::Color idleColor, const std::string& textString, sf::Font &textFont,
           int textSize, sf::Color hoverColor, sf::Color pressedColor, sf::Color textColor = sf::Color::Black);
    ~Button() = default;

    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget &target);
    bool isPressed() const;


private:

    sf::RectangleShape button;
    sf::Text text;
    unsigned short buttonState;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color pressedColor;

};


#endif //PLATFORMGAME_BUTTON_H
