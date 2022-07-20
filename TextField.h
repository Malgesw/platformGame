#ifndef PLATFORMGAME_TEXTFIELD_H
#define PLATFORMGAME_TEXTFIELD_H

#include "SFML/Graphics.hpp"

class TextField {

public:

    TextField(sf::Vector2f size, sf::Vector2f position, int textSize, sf::Vector2f textPosition, const std::string& description,
              sf::Vector2f descrPosition, sf::Font *font, sf::Color color, sf::Color textColor = sf::Color::Black,
              sf::Color descrColor = sf::Color::Black);

    ~TextField() = default;

    bool contains(sf::Vector2f mousePos);
    void setString(const sf::String &string);
    void clear();
    void render(sf::RenderTarget &target);

    sf::String getString() const {
        return textString;
    }

    std::string getDescription() const {
        return descriptionText.getString();
    }

private:

    sf::RectangleShape body;
    sf::Text text;
    sf::Text descriptionText;
    sf::String textString;

};


#endif //PLATFORMGAME_TEXTFIELD_H
