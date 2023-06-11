#include "AutoWalking.h"

AutoWalking::AutoWalking(float movementSpeed, sf::Vector2f startPosition, sf::Vector2f size,
                         const std::vector<std::shared_ptr<LevelTile>> &walls, float jHeight, float turnTime,
                         unsigned short *typeOfSprite) :
        WalkingMovement(movementSpeed, startPosition, size, jHeight, typeOfSprite, false), turnbackTime(turnTime) {

    collisionBox.setFillColor(sf::Color::Red);
    timeCounter.restart();

}

void AutoWalking::rest() {

    if (timeCounter.getElapsedTime().asSeconds() < (turnbackTime / 2) && *typeOfSprite != ATTACKRIGHT &&
        *typeOfSprite != ATTACKLEFT) {
        moveRight();
    } else if (timeCounter.getElapsedTime().asSeconds() < turnbackTime && *typeOfSprite != ATTACKLEFT &&
               *typeOfSprite != ATTACKRIGHT) {
        moveLeft();
    } else {
        timeCounter.restart();
    }
}

void AutoWalking::aggro(const float &dt, sf::Vector2f playerPosition) {

}


void AutoWalking::update(const float &deltaTime, sf::Vector2f playerPosition) {
    rest();
    Movement::update(deltaTime, playerPosition);
}

