//
// Created by alessio on 25/07/22.
//
#include "Movement.h"

void Movement::moveLeft() {
    collisionBox.move(speed*dt*-1.f,0.f);
}
void Movement::moveRight() {
    collisionBox.move(speed*dt,0.f);
}

float Movement::getSpeed() const{
    return speed;
}



Movement::Movement(float velocity, sf::Vector2f startPosition, sf::Vector2f size,char type):speed(velocity),dt(0.01f),typeOfMovement(type){
    collisionBox=sf::RectangleShape(size);
    collisionBox.setPosition(startPosition);
}

void Movement::updateDt(float deltaTime){
dt=deltaTime;
}





void Movement::checkCollisions(const std::vector<std::shared_ptr<LevelTile>> &objects) {

    for (auto &o: objects) {

        sf::FloatRect playerBounds = collisionBox.getGlobalBounds();
        sf::FloatRect objectBounds;
        sf::FloatRect nextPlayerPos = playerBounds;
        nextPlayerPos.left += speed * dt;
        nextPlayerPos.top += speed * dt;

        objectBounds = o->getGlobalBounds();
        if (objectBounds.intersects(nextPlayerPos)) {

            //Bottom
            if (playerBounds.top < objectBounds.top &&
                playerBounds.top + playerBounds.height < objectBounds.top + objectBounds.height &&
                playerBounds.left < objectBounds.left + objectBounds.width &&
                playerBounds.left + playerBounds.width > objectBounds.left) {
                velocity.x = 0.f;
                collisionBox.setPosition(playerBounds.left, objectBounds.top - playerBounds.height);
            }

                //Top
            else if (playerBounds.top > objectBounds.top &&
                     playerBounds.top + playerBounds.height > objectBounds.top + objectBounds.height &&
                     playerBounds.left < objectBounds.left + objectBounds.width &&
                     playerBounds.left + playerBounds.width > objectBounds.left) {
                velocity.x = 0.f;
                collisionBox.setPosition(playerBounds.left, objectBounds.top + objectBounds.height);
            }


                //Right
            else if (playerBounds.left < objectBounds.left &&
                     playerBounds.left + playerBounds.width < objectBounds.left + objectBounds.width &&
                     playerBounds.top < objectBounds.top + objectBounds.height &&
                     playerBounds.top + playerBounds.height > objectBounds.top) {
                velocity.x = 0.f;
                collisionBox.setPosition(objectBounds.left - playerBounds.width, playerBounds.top);
            }

                //Left
            else if (playerBounds.left > objectBounds.left &&
                     playerBounds.left + playerBounds.width > objectBounds.left + objectBounds.width &&
                     playerBounds.top < objectBounds.top + objectBounds.height &&
                     playerBounds.top + playerBounds.height > objectBounds.top) {
                velocity.x = 0.f;
                collisionBox.setPosition(objectBounds.left + playerBounds.width, playerBounds.top);
            }

        }
    }
}


void Movement::setVelocity(float x, float y){
    velocity.x=x;
    velocity.y=y;
}

sf::Vector2f Movement::getVelocity() const{
    return velocity;
}

sf::RectangleShape Movement::getCollisions() const {
    return collisionBox;
}

char Movement::getTypeOfMovement() const {
    return typeOfMovement;
}


