#ifndef PLATFORMGAME_DROPDOWNLIST_H
#define PLATFORMGAME_DROPDOWNLIST_H

#include "Button.h"

class DropDownList {

public:

    DropDownList(sf::Vector2f size, sf::Vector2f position, sf::Color color, sf::Font &textFont,
    int textSize, std::vector<std::string> fields, const std::string& description, sf::Vector2f descrPosition,
                 sf::Color hoverColor, sf::Color pressedColor, sf::Color textColor = sf::Color::White);

    ~DropDownList() = default;

    void update(sf::Vector2f mousePos, sf::RenderWindow *window);
    void render(sf::RenderTarget &target);
    void setFirstElement(const std::string& first) {
        firstElement->setField(first);
    }

    bool isReady();

private:

    std::vector<std::unique_ptr<Button>> buttonList;
    std::unique_ptr<Button> firstElement;
    sf::Clock keyClock;
    sf::Text descriptionText;
    float maxKeyTime;
    bool isOpen;

};


#endif //PLATFORMGAME_DROPDOWNLIST_H
