//
// Created by alessio on 25/07/22.
//

#ifndef PLATFORMGAME_MOVEMENT_H
#define PLATFORMGAME_MOVEMENT_H

#include "headers.h"


class Movement {

public:
    Movement(float velocity, sf::Vector2f startPosition, sf::Vector2f size);
    virtual void moveX();
    virtual void moveY()=0;
    virtual float getSpeed();
    virtual void checkCollision();


private:
    float speed;
    sf::RectangleShape collisionBox;
};


#endif //PLATFORMGAME_MOVEMENT_H
