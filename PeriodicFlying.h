//
// Created by nicco on 23/05/2023.
//

#ifndef PLATFORMGAME_PERIODICFLYING_H
#define PLATFORMGAME_PERIODICFLYING_H

#include "FlyingMovement.h"
#include "AutoMovement.h"

class PeriodicFlying : public FlyingMovement, AutoMovement {

public:
    PeriodicFlying(float movementSpeed, sf::Vector2f startPosition, sf::Vector2f size,
                   const std::vector<std::shared_ptr<LevelTile>> &walls, float turnTime, unsigned short *typeOfSprite);

    void rest() override;

    void aggro(const float &dt, sf::Vector2f playerPosition) override;

    void update(const float &deltaTime, sf::Vector2f playerPosition) override;

private:
    float turnbackTime;
    sf::Clock timeCounter;
};


#endif //PLATFORMGAME_PERIODICFLYING_H
