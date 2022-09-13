//
// Created by alessio on 26/07/22.
//

#include "WalkingMovement.h"

WalkingMovement::WalkingMovement(float velocity, sf::Vector2f startPosition, sf::Vector2f size,float height)
: Movement(velocity,startPosition,size,'W'),jumpHeight(height){


}

void WalkingMovement::moveUp() {
    if(isOnGround) {
        isOnGround = false;
        velocity.y = -sqrtf(2.f * 981.f * jumpHeight);
        collisionBox.move(0.f, velocity.y * dt);
    }
}

void WalkingMovement::moveDown() {

}


float WalkingMovement::getJumpHeight() const{
    return jumpHeight;
}
