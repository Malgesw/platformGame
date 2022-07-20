//
// Created by kaneki on 20/07/22.
//

#include "TextField.h"

TextField::TextField(sf::Vector2f size, sf::Vector2f position, int textSize, sf::Vector2f textPosition,
                     const std::string& description, sf::Vector2f descrPosition, sf::Font *font, sf::Color color,
                     sf::Color textColor, sf::Color descrColor) : textString("") {

    body.setSize(size);
    body.setPosition(position);
    body.setFillColor(color);

    text.setCharacterSize(textSize);
    text.setPosition(textPosition);
    text.setFillColor(textColor);
    text.setFont(*font);

    descriptionText.setCharacterSize(textSize);
    descriptionText.setFont(*font);
    descriptionText.setString(description);
    descriptionText.setPosition(descrPosition);
    descriptionText.setFillColor(descrColor);

}

bool TextField::contains(sf::Vector2f mousePos) {

    if(body.getGlobalBounds().contains(mousePos))
        return true;
    else
        return false;

}

void TextField::setString(const sf::String &string) {

    textString = string;
    text.setString(textString);

}

void TextField::clear() {

    textString.clear();

}

void TextField::render(sf::RenderTarget &target) {

    target.draw(body);
    target.draw(text);
    target.draw(descriptionText);

}
