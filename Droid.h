#ifndef PLATFORMGAME_DROID_H
#define PLATFORMGAME_DROID_H

#include "Item.h"


class Droid : public Item {

public:

    Droid(std::unique_ptr<Animation> animation, std::unique_ptr<Movement> movement,
          sf::Texture *texture, sf::Vector2f size, sf::Vector2f position) :
            animation(std::move(animation)), movement(std::move(movement)), Item(texture, size, position) {
    }

    void use(GameCharacter &player) override;

private:
    std::unique_ptr<Animation> animation;
    std::unique_ptr<Movement> movement;
};


#endif //PLATFORMGAME_DROID_H
