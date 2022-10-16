//
// Created by alessio on 02/09/22.
//

#ifndef PLATFORMGAME_AUTOFLYING_H
#define PLATFORMGAME_AUTOFLYING_H

#include "FlyingMovement.h"
#include "AutoMovement.h"

class AutoFlying : public FlyingMovement, public AutoMovement{

public:
    AutoFlying(float movementSpeed, sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>> &walls, sf::Vector2f wallSize);
    void rest() override;
    void aggro(const float &dt, sf::Vector2f playerPosition) override;
    void update( const float &deltaTime, sf::Vector2f playerPosition) override;
};


#endif //PLATFORMGAME_AUTOFLYING_H
