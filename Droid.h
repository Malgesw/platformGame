#ifndef PLATFORMGAME_DROID_H
#define PLATFORMGAME_DROID_H

#include "Item.h"


class Droid : public Item {

public:

    Droid(std::unique_ptr<Animation> animation, std::unique_ptr<Movement> movement,
          sf::Vector2f size, sf::Vector2f position, std::unique_ptr<Animation> itemAnimation) :
            movement(std::move(movement)), Item(size, position, std::move(itemAnimation)) {
    }

    void use(GameCharacter &player) override;

private:
    std::unique_ptr<Movement> movement;
};


#endif //PLATFORMGAME_DROID_H
