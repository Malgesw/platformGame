#ifndef PLATFORMGAME_FLYINGMOVEMENT_H
#define PLATFORMGAME_FLYINGMOVEMENT_H

#include "Movement.h"

class FlyingMovement : public Movement{

public:
    FlyingMovement(float velocity, sf::Vector2f startPosition, sf::Vector2f size, unsigned short * typeOfSprite);
    void moveUp() override;
    void moveDown() override;
    void moveLeft() override;
    void moveRight() override;
};


#endif //PLATFORMGAME_FLYINGMOVEMENT_H
