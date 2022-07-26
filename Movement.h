//
// Created by alessio on 25/07/22.
//

#ifndef PLATFORMGAME_MOVEMENT_H
#define PLATFORMGAME_MOVEMENT_H

#include "headers.h"
#include "Observer.h"

class Movement: public Observer{

public:
    Movement(float velocity, sf::Vector2f startPosition, sf::Vector2f size);
    virtual void moveLeft();
    virtual void moveRight();
    virtual void moveUp()=0;
    virtual void moveDown()=0;
    virtual float getSpeed();
    virtual void checkCollision();
    void updateDt(float deltaTime)override;


private:
    float speed;
    float dt;
    sf::RectangleShape collisionBox;
};


#endif //PLATFORMGAME_MOVEMENT_H
