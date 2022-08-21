//
// Created by alessio on 25/07/22.
//
#include "Movement.h"

#include <utility>

void Movement::moveLeft() {
    velocity.x=velocity.x-speed;
    collisionBox.move(velocity.x*dt,0.f);
}
void Movement::moveRight() {
    velocity.x=velocity.x+speed;
    collisionBox.move(velocity.x*dt,0.f);
}


Movement::Movement(float velocity, sf::Vector2f startPosition, sf::Vector2f size,char type,std::vector<std::shared_ptr<LevelTile>>  walls)
:speed(velocity),dt(0.01f),typeOfMovement(type),barriers(std::move(walls)){

    collisionBox=sf::RectangleShape(size);
    collisionBox.setPosition(startPosition);
    collisionBox.setFillColor(sf::Color::Black);


}


void Movement::checkCollisions() {

    float lateralTolerance=speed*dt*5;



    for (auto &o: barriers) {

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
                playerBounds.left < objectBounds.left + objectBounds.width - lateralTolerance &&
                playerBounds.left + playerBounds.width > objectBounds.left + lateralTolerance) {
                velocity.y = 0.f;
                isOnGround = true;
                collisionBox.setPosition(playerBounds.left, objectBounds.top - playerBounds.height);
            }

                //Top
            else if (playerBounds.top > objectBounds.top &&
                     playerBounds.top + playerBounds.height > objectBounds.top + objectBounds.height &&
                     playerBounds.left < objectBounds.left + objectBounds.width - lateralTolerance &&
                     playerBounds.left + playerBounds.width > objectBounds.left + lateralTolerance) {
                velocity.y = 0.f;
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
                collisionBox.setPosition(objectBounds.left + objectBounds.width, playerBounds.top);
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


void Movement::update( sf::RenderWindow *window, float deltaTime) {

    dt=deltaTime;

    if(collisionBox.getPosition().y + collisionBox.getSize().y < (float)(*window).getSize().y and typeOfMovement=='W')

        velocity.y+=981.f*dt;

    checkCollisions();

    collisionBox.move(0,velocity.y*dt);

    //MAP COLLISIONS

    if(collisionBox.getPosition().y + collisionBox.getSize().y >= 600.f) {
        collisionBox.setPosition(collisionBox.getPosition().x, 600.f - collisionBox.getSize().y);
        if(typeOfMovement=='W') {
            isOnGround=true;
        }
    }

    if(collisionBox.getPosition().x < 0.f)
        collisionBox.setPosition(0, collisionBox.getPosition().y);

    if(collisionBox.getPosition().x + collisionBox.getSize().x >= 800.f)
        collisionBox.setPosition(800.f - collisionBox.getSize().x, collisionBox.getPosition().y);

    if(collisionBox.getGlobalBounds().top < 0.f)
        collisionBox.setPosition(collisionBox.getGlobalBounds().left, 0.f);
}

sf::Vector2f Movement::getPosition() const {
    return collisionBox.getPosition();
}

Movement::~Movement() = default;






