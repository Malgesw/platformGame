#ifndef ITEM_H
#define ITEM_H

#include "GameCharacter.h"

class Item {

public:
    Item(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position, std::unique_ptr<Animation> animation);

    void render(sf::RenderTarget &target);

    void update(const float &dt);

    virtual void use(GameCharacter &player);

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
    sf::RectangleShape body;
    sf::Vector2f position;
    bool onMap;
    std::unique_ptr<Animation> animation;
};


#endif //ITEM_H
