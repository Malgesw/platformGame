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

float Movement::getSpeed() {
    return speed;
}

void Movement::checkCollision() {

}

Movement::Movement(float velocity, sf::Vector2f startPosition, sf::Vector2f size):speed(velocity),dt(0.01f) {
    collisionBox=sf::RectangleShape(size);
    collisionBox.setPosition(startPosition);
}

void Movement::updateDt(float deltaTime){
dt=deltaTime;
}

