#ifndef PLATFORMGAME_BUTTON_H
#define PLATFORMGAME_BUTTON_H

#include "headers.h"

enum BUTTON_STATES{IDLE, PRESSED, HOVER};


class Button {

public:

    Button(sf::Vector2f size, sf::Vector2f position, sf::Color idleColor, const std::string& textString, sf::Font &textFont,
           int textSize, sf::Color hoverColor, sf::Color pressedColor, char type = 'B', sf::Color textColor = sf::Color::White);

    ~Button() = default;

    void update(sf::Vector2f mousePos);
    void render(sf::RenderTarget &target);
    bool isPressed() const;

    void setField(const std::string& field){
        text.setString(field);
    }

    std::string getField(){
        return text.getString();
    }

    void setTextPosition(sf::Vector2f pos){
        text.setPosition(pos);
    }

    sf::Vector2f getTextPosition(){
        return text.getPosition();
    }

    void setPosition(sf::Vector2f pos){
        button.setPosition(pos);
        text.setPosition(button.getGlobalBounds().left + button.getGlobalBounds().width/2.f - text.getGlobalBounds().width/2.f,
                         button.getGlobalBounds().top + button.getGlobalBounds().height/2.f - text.getGlobalBounds().height/2.f);
    }


private:

    sf::RectangleShape button;
    sf::Text text;
    unsigned short buttonState;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color pressedColor;
    sf::Texture texture;

};


#endif //PLATFORMGAME_BUTTON_H
