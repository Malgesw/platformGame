//
// Created by nicco on 11/05/2023.
//

#include "GlidingMovement.h"


GlidingMovement::GlidingMovement(float velocity, sf::Vector2f startPosition, sf::Vector2f size, float height,
                                 unsigned short *typeOfSprite, bool isPlayer)
        : Movement(velocity, startPosition, size, 'G', typeOfSprite, isPlayer), jumpHeight(height) {


}

void GlidingMovement::moveUp() {
    if (isOnGround) {
        isOnGround = false;
        isMoving = true;
        velocity.y = -sqrtf(2.f * 981.f * jumpHeight);
        collisionBox.move(0.f, velocity.y * dt);
    }
}

void GlidingMovement::moveDown() {

}


float GlidingMovement::getJumpHeight() const {
    return jumpHeight;
}

void GlidingMovement::moveLeft() {
    Movement::moveLeft();
}

void GlidingMovement::moveRight() {
    Movement::moveRight();
}
