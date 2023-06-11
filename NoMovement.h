//
// Created by alessio on 06/03/23.
//

#ifndef PLATFORMGAME_NOMOVEMENT_H
#define PLATFORMGAME_NOMOVEMENT_H

#include "Movement.h"

class NoMovement : public Movement {
public:
    NoMovement(sf::Vector2f startPosition, sf::Vector2f size, unsigned short *typeOfSprite);

    void moveLeft() final {};

    void moveRight() final {};

    void moveUp() final {};

    void moveDown() final {};
protected:
    void applyKnockback() override {};
};


#endif //PLATFORMGAME_NOMOVEMENT_H
