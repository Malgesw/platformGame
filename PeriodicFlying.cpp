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

    if (timeCounter.getElapsedTime().asSeconds() < (turnbackTime / 2)) {
        moveUp();
    } else if (timeCounter.getElapsedTime().asSeconds() < turnbackTime) {
        FlyingMovement::moveDown();
    } else {
        timeCounter.restart();
    }
}

void PeriodicFlying::aggro(const float &dt, sf::Vector2f playerPosition) {

}

void PeriodicFlying::update(const float &deltaTime, sf::Vector2f playerPosition) {
    *typeOfSprite = IDLELEFT;
    rest();
    Movement::update(deltaTime, playerPosition);
}
