//
// Created by alessio on 16/08/22.
//

#ifndef PLATFORMGAME_AUTOWALKING_H
#define PLATFORMGAME_AUTOWALKING_H
#include "WalkingMovement.h"

class AutoWalking : public WalkingMovement{
public:
    AutoWalking(float movementSpeed, sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>>& walls,float jHeight,float turnTime);
    void wander();
    void update(sf::RenderWindow *window, float deltaTime) override;



private:
    float turnbackTime;
    sf::Clock timeCounter;
};


#endif //PLATFORMGAME_AUTOWALKING_H
