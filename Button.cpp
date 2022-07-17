#include "Button.h"


Button::Button(sf::Vector2f size, sf::Vector2f position, sf::Color idleColor, const std::string& textString, sf::Font &textFont,
               int textSize, sf::Color hoverColor, sf::Color pressedColor, sf::Color textColor) :
               idleColor(idleColor), hoverColor(hoverColor), pressedColor(pressedColor) {

    button.setSize(size);
    button.setPosition(position);
    button.setFillColor(this->idleColor);

    text.setString(textString);
    text.setFont(textFont);
    text.setFillColor(textColor);
    text.setCharacterSize(textSize);
    text.setPosition(button.getGlobalBounds().left + button.getGlobalBounds().width/3.f,
                     button.getGlobalBounds().top + button.getGlobalBounds().height/3.f);

    buttonState = IDLE;

}

void Button::update(sf::Vector2f mousePos) {

    buttonState = IDLE;

    if(button.getGlobalBounds().contains(mousePos)){

        buttonState = HOVER;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            buttonState = PRESSED;

    }

    //Handle button states
    switch(buttonState){

        case IDLE:
            button.setFillColor(idleColor);
            break;

        case HOVER:
            button.setFillColor(hoverColor);
            break;

        case PRESSED:
            button.setFillColor(pressedColor);
            break;

        default:
            button.setFillColor(sf::Color::White);
            break;

    }

}

void Button::render(sf::RenderTarget &target) {

    target.draw(button);
    target.draw(text);

}

bool Button::isPressed() const {

    if(buttonState == PRESSED)
        return true;
    else
        return false;

}


