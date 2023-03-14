#ifndef ITEM_H
#define ITEM_H
#include <SFML/Graphics.hpp>

class Item {

public:
    Item(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position);

    void render(sf::RenderTarget &target);

    bool isOnMap() const {
        return onMap;
    }

    sf::Vector2f getPosition() {
        return position;
    }

    sf::RectangleShape getBody() const {
        return body;
    }

    void setState(bool state) {
        onMap = state;
    }

protected:
    sf::Texture *texture;
    sf::RectangleShape body;
    sf::Vector2f position;
    bool onMap;
};


#endif //ITEM_H
