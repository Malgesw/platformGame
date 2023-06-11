//
// Created by alessio on 26/07/22.
//

#include "WalkingMovement.h"

WalkingMovement::WalkingMovement(float velocity, sf::Vector2f startPosition, sf::Vector2f size, float height,
                                 unsigned short *typeOfSprite, bool isPlayer)
        : Movement(velocity, startPosition, size, 'W', typeOfSprite, isPlayer), jumpHeight(height) {


}

void WalkingMovement::moveUp() {
    if(isOnGround) {
        isOnGround = false;
        isMoving = true;
        velocity.y = -sqrtf(2.f * 981.f * jumpHeight);
        collisionBox.move(0.f, velocity.y * dt);
    }
}

void WalkingMovement::moveDown() {

}


float WalkingMovement::getJumpHeight() const{
    return jumpHeight;
}

void WalkingMovement::moveLeft() {
Movement::moveLeft();
}

void WalkingMovement::moveRight() {
Movement::moveRight();
}
