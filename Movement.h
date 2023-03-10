//
// Created by alessio on 25/07/22.
//

#ifndef PLATFORMGAME_MOVEMENT_H
#define PLATFORMGAME_MOVEMENT_H


#include "LevelTile.h"
#include "spriteType.h"


class Movement{

public:
    Movement(float velocity, sf::Vector2f startPosition, sf::Vector2f size,char type, unsigned short* typeOfSprite);
    virtual ~Movement();
    virtual void moveLeft()=0;
    virtual void moveRight()=0;
    virtual void moveUp()=0;
    virtual void moveDown()=0;
    bool onGround() const;
    virtual bool checkCollisions();
    void setVelocity(float x, float y);
    virtual void update(const float &deltaTime, sf::Vector2f playerPosition);
    sf::Vector2f getVelocity() const;
    sf::RectangleShape& getCollisions();
    sf::Vector2f& getKnockback();




    sf::Vector2f getPosition() const;
    void addWalls(const std::vector<std::shared_ptr<LevelTile>>& newWalls);
    void clearWalls();


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
    sf::Vector2f knockback;
    sf::RectangleShape collisionBox;
    std::vector<std::shared_ptr<LevelTile>> barriers;
    bool isOnGround=true;
    bool inertia = true;
    unsigned short *typeOfSprite;

    virtual void applyKnockback();

};


#endif //PLATFORMGAME_MOVEMENT_H
