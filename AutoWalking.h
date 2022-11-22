//
// Created by alessio on 16/08/22.
//

#ifndef PLATFORMGAME_AUTOWALKING_H
#define PLATFORMGAME_AUTOWALKING_H
#include "WalkingMovement.h"
#include "AutoMovement.h"

class AutoWalking : public WalkingMovement, AutoMovement{
public:
    AutoWalking(float movementSpeed, sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>>& walls,float jHeight,float turnTime);
    void rest() override;
    void aggro(const float &dt, sf::Vector2f playerPosition) override;
    void update(const float &deltaTime, sf::Vector2f playerPosition) override;



private:
    float turnbackTime;
    sf::Clock timeCounter;
};


#endif //PLATFORMGAME_AUTOWALKING_H
