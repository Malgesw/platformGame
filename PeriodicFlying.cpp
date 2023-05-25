//
// Created by nicco on 23/05/2023.
//

#include "PeriodicFlying.h"

PeriodicFlying::PeriodicFlying(float movementSpeed, sf::Vector2f startPosition, sf::Vector2f size,
                               const std::vector<std::shared_ptr<LevelTile>> &walls, float turnTime,
                               unsigned short *typeOfSprite) : FlyingMovement(movementSpeed, startPosition, size,
                                                                              typeOfSprite,
                                                                              false), turnbackTime(turnTime) {
    timeCounter.restart();
    *typeOfSprite = IDLELEFT;
}

void PeriodicFlying::rest() {

    if (timeCounter.getElapsedTime().asSeconds() < (turnbackTime / 2) && *typeOfSprite != ATTACKRIGHT &&
        *typeOfSprite != ATTACKLEFT) {
        moveUp();
    } else if (timeCounter.getElapsedTime().asSeconds() < turnbackTime && *typeOfSprite != ATTACKLEFT &&
               *typeOfSprite != ATTACKRIGHT) {
        FlyingMovement::moveDown();
    } else {
        timeCounter.restart();
    }
}

void PeriodicFlying::aggro(const float &dt, sf::Vector2f playerPosition) {

}

void PeriodicFlying::update(const float &deltaTime, sf::Vector2f playerPosition) {
    rest();
    Movement::update(deltaTime, playerPosition);
}
