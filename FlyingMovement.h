//
// Created by alessio on 26/07/22.
//

#ifndef PLATFORMGAME_FLYINGMOVEMENT_H
#define PLATFORMGAME_FLYINGMOVEMENT_H

#include "Movement.h"

class FlyingMovement : public Movement{

public:
    FlyingMovement(float velocity, sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>>& walls);
    void moveUp() override;
    void moveDown() override;
};


#endif //PLATFORMGAME_FLYINGMOVEMENT_H
