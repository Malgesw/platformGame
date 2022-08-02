//
// Created by alessio on 25/07/22.
//

#ifndef PLATFORMGAME_MOVEMENT_H
#define PLATFORMGAME_MOVEMENT_H

#include "headers.h"
#include "Observer.h"
#include "LevelTile.h"


class Movement: public Observer{

public:
    Movement(float velocity, sf::Vector2f startPosition, sf::Vector2f size,char type);

    virtual void moveLeft();
    virtual void moveRight();
    virtual void moveUp()=0;
    virtual void moveDown()=0;
    float getSpeed() const;
    virtual void checkCollisions(const std::vector<std::shared_ptr<LevelTile>> &objects);
    void updateDt(float deltaTime)override;
    void setVelocity(float x, float y);
    sf::Vector2f getVelocity() const;
    sf::RectangleShape getCollisions() const;



private:
    char typeOfMovement;
public:
    char getTypeOfMovement() const;

private:
    //can be F for flying or W for walking
    float speed;
    float dt;
    sf::Vector2f velocity;
    sf::RectangleShape collisionBox;
};


#endif //PLATFORMGAME_MOVEMENT_H
