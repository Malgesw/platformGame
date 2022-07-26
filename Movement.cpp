//
// Created by alessio on 25/07/22.
//
#include "Movement.h"

void Movement::moveX() {

}

float Movement::getSpeed() {
    return speed;
}

void Movement::checkCollision() {

}

Movement::Movement(float velocity, sf::Vector2f startPosition, sf::Vector2f size):speed(velocity) {
    collisionBox=sf::RectangleShape(size);
    collisionBox.setPosition(startPosition);
}

