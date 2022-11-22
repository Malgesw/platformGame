//
// Created by alessio on 25/07/22.
//
#include "Movement.h"
#include <cmath>
#include <utility>

void Movement::moveLeft() {
    if(isOnGround)
        typeOfSprite = MOVELEFT;
    else
        typeOfSprite = JUMPLEFT;
    velocity.x=velocity.x-speed;
    if (velocity.x<=-10*speed)
        velocity.x=-10*speed;
    collisionBox.move(velocity.x*dt,0.f);
}
void Movement::moveRight() {
    if(isOnGround)
        typeOfSprite = MOVERIGHT;
    else
        typeOfSprite = JUMPRIGHT;
    velocity.x=velocity.x+speed;
    if (velocity.x>=10*speed)
        velocity.x=10*speed;
    collisionBox.move(velocity.x*dt,0.f);
}


Movement::Movement(float velocity, sf::Vector2f startPosition, sf::Vector2f size,char type)
:speed(velocity),dt(0.01f),typeOfMovement(type){

    collisionBox=sf::RectangleShape(size);
    collisionBox.setPosition(startPosition);
    collisionBox.setFillColor(sf::Color::White);
    typeOfSprite = IDLERIGHT;
    knockback=sf::Vector2f (0,0);
}


bool Movement::checkCollisions() {

    float Tolerance=std::sqrt(speed)*dt*100;
    bool collided = false;
    for (auto &o: barriers) {

        if (std::abs(o->getGlobalBounds().top-collisionBox.getGlobalBounds().top)<400 and
        std::abs(o->getGlobalBounds().left-collisionBox.getGlobalBounds().left)<600) {

            sf::FloatRect playerBounds = collisionBox.getGlobalBounds();
            sf::FloatRect objectBounds;
            sf::FloatRect nextPlayerPos = playerBounds;
            nextPlayerPos.left += velocity.x * dt;
            nextPlayerPos.top += velocity.y * dt;


        objectBounds = o->getGlobalBounds();
        if (objectBounds.intersects(nextPlayerPos)) {


            //Bottom
            if (playerBounds.top < objectBounds.top &&
                playerBounds.top + playerBounds.height < objectBounds.top + objectBounds.height &&
                playerBounds.left < objectBounds.left + objectBounds.width - Tolerance &&
                playerBounds.left + playerBounds.width > objectBounds.left + Tolerance) {
                velocity.y = 0.f;
                isOnGround = true;
                collisionBox.setPosition(playerBounds.left, objectBounds.top - playerBounds.height);
                collided= true;
            }

                //Top
            else if (playerBounds.top > objectBounds.top &&
                     playerBounds.top + playerBounds.height > objectBounds.top + objectBounds.height &&
                     playerBounds.left < objectBounds.left + objectBounds.width - Tolerance &&
                     playerBounds.left + playerBounds.width > objectBounds.left + Tolerance) {
                velocity.y = 0.f;
                collisionBox.setPosition(playerBounds.left, objectBounds.top + objectBounds.height);
                collided= true;
            }


                //Right
            else if (playerBounds.left < objectBounds.left &&
                     playerBounds.left + playerBounds.width < objectBounds.left + objectBounds.width &&
                     playerBounds.top < objectBounds.top + objectBounds.height -Tolerance &&
                     playerBounds.top + playerBounds.height > objectBounds.top +Tolerance) {
                velocity.x = 0.f;
                collisionBox.setPosition(objectBounds.left - playerBounds.width, playerBounds.top);
                collided= true;
            }

                //Left
            else if (playerBounds.left > objectBounds.left &&
                     playerBounds.left + playerBounds.width > objectBounds.left + objectBounds.width &&
                     playerBounds.top < objectBounds.top + objectBounds.height -Tolerance&&
                     playerBounds.top + playerBounds.height > objectBounds.top +Tolerance) {
                velocity.x = 0.f;
                collisionBox.setPosition(objectBounds.left + objectBounds.width, playerBounds.top);
                collided= true;
            }

            else
                isOnGround = false;

        }
        else
            collided= false;


    }
     return collided;
    }

    }


void Movement::setVelocity(float x, float y){
    velocity.x=x;
    velocity.y=y;
}

sf::Vector2f Movement::getVelocity() const{
    return velocity;
}

sf::RectangleShape& Movement::getCollisions() {
    return collisionBox;
}


void Movement::update(const float &deltaTime, sf::Vector2f playerPosition) {


    dt=deltaTime;
    applyKnockback();
    if(typeOfMovement=='W')

        velocity.y+=981.f*dt;

    checkCollisions();
    collisionBox.move(0,velocity.y*dt);

}

bool Movement::onGround() const {
    return isOnGround;
}

sf::Vector2f Movement::getPosition() const {
    return collisionBox.getPosition();
}

Movement::~Movement() = default;

const std::vector<std::shared_ptr<LevelTile>> &Movement::getBarriers() const {
    return barriers;
}

void Movement::addWalls(const std::vector<std::shared_ptr<LevelTile>>& newWalls) {

    for(auto &w : newWalls){
        barriers.push_back(w);
    }
}

void Movement::clearWalls() {

        barriers.clear();
}

void Movement::applyKnockback() {

    collisionBox.move(knockback*dt*7.f);
    knockback=knockback-knockback*dt*7.f;

}

sf::Vector2f &Movement::getKnockback() {
    return knockback;
}









