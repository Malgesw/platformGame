//
// Created by alessio on 25/07/22.
//

#ifndef PLATFORMGAME_MOVEMENT_H
#define PLATFORMGAME_MOVEMENT_H


#include "LevelTile.h"

enum spriteType {IDLE_SPRITE, MOVERIGHT, MOVELEFT, JUMPRIGHT, JUMPLEFT};

class Movement{

public:
    Movement(float velocity, sf::Vector2f startPosition, sf::Vector2f size,char type);
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

    unsigned short &getSpriteType(){
        return typeOfSprite;
    }

    void setSpriteType(unsigned short type){
        typeOfSprite = type;
    }

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
    sf::RectangleShape collisionBox;
    std::vector<std::shared_ptr<LevelTile>> barriers;
    bool isOnGround=true;
    bool inertia = true;
public:
    bool onGround() const;

protected:
    unsigned short typeOfSprite;

};


#endif //PLATFORMGAME_MOVEMENT_H
