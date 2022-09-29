//
// Created by alessio on 26/07/22.
//

#include "FlyingMovement.h"



FlyingMovement::FlyingMovement(float velocity, sf::Vector2f startPosition, sf::Vector2f size) : Movement(velocity,startPosition,size,'F') {

}

void FlyingMovement::moveUp() {
    velocity.y=velocity.y-speed;
    if (velocity.y<=-10*speed)
        velocity.y=-10*speed;
    collisionBox.move(0.f,velocity.y*dt);
}

void FlyingMovement::moveDown() {
    velocity.y=velocity.y+speed;
    if (velocity.y>=10*speed)
        velocity.y=10*speed;
    collisionBox.move(0.f,velocity.y*dt);
}

void FlyingMovement::moveLeft() {
    Movement::moveLeft();
}

void FlyingMovement::moveRight() {
    Movement::moveRight();
}

