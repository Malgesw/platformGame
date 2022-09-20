//
// Created by alessio on 25/07/22.
//

#ifndef PLATFORMGAME_MOVEMENT_H
#define PLATFORMGAME_MOVEMENT_H


#include "LevelTile.h"


class Movement{

public:
    Movement(float velocity, sf::Vector2f startPosition, sf::Vector2f size,char type,const std::vector<std::shared_ptr<LevelTile>>& walls);

    virtual void moveLeft();
    virtual void moveRight();
    virtual void moveUp()=0;
    virtual void moveDown()=0;

    virtual bool checkCollisions();

    void setVelocity(float x, float y);
    void update(sf::RenderWindow *window, float deltaTime);
    sf::Vector2f getVelocity() const;
    sf::RectangleShape &getCollisions();



protected:
    char typeOfMovement;
    //can be F for flying or W for walking
    float speed;
    float dt;
    sf::Vector2f velocity;
    sf::RectangleShape collisionBox;

protected:
    const std::vector<std::shared_ptr<LevelTile>> barriers;
    bool isOnGround=true;
public:
    bool getisOnGround() const;
};


#endif //PLATFORMGAME_MOVEMENT_H
