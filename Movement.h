//
// Created by alessio on 25/07/22.
//

#ifndef PLATFORMGAME_MOVEMENT_H
#define PLATFORMGAME_MOVEMENT_H


#include "LevelTile.h"


class Movement{

public:
    Movement(float velocity, sf::Vector2f startPosition, sf::Vector2f size,char type,const std::vector<std::shared_ptr<LevelTile>>  &walls);
    virtual ~Movement();

    virtual void moveLeft();
    virtual void moveRight();
    virtual void moveUp()=0;
    virtual void moveDown()=0;

    virtual void checkCollisions();

    void setVelocity(float x, float y);
    virtual void update(sf::RenderWindow *window,const float &deltaTime, sf::Vector2f playerPosition);
    sf::Vector2f getVelocity() const;
    sf::RectangleShape& getCollisions();
    sf::Vector2f getPosition() const;


    const std::vector<std::shared_ptr<LevelTile>> &getBarriers() const;

    void setBarriers(const std::vector<std::shared_ptr<LevelTile>>& newWalls){

        barriers.clear();

        for(auto &nw : newWalls){
            barriers.push_back(nw);
        }

    }


protected:
    char typeOfMovement;
    //can be F for flying or W for walking
    float speed;
    float dt;
    sf::Vector2f velocity;
    sf::RectangleShape collisionBox;
    std::vector<std::shared_ptr<LevelTile>> barriers;
    bool isOnGround=true;
};


#endif //PLATFORMGAME_MOVEMENT_H
