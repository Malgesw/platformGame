//
// Created by alessio on 26/07/22.
//

#include "WalkingMovement.h"

WalkingMovement::WalkingMovement(float velocity, sf::Vector2f startPosition, sf::Vector2f size) : Movement(velocity,
                                                                                                           startPosition,
                                                                                                           size,'W'){

}

void WalkingMovement::moveUp() {

}

void WalkingMovement::moveDown() {

}

void WalkingMovement::setJump(bool jump) {
canJump=jump;
}

float WalkingMovement::getJumpHeight() const{
    return jumpHeight;
}

bool WalkingMovement::getJump() const {
    return canJump;
}
