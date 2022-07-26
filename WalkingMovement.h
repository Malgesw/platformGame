//
// Created by alessio on 26/07/22.
//

#ifndef PLATFORMGAME_WALKINGMOVEMENT_H
#define PLATFORMGAME_WALKINGMOVEMENT_H

#include "Movement.h"

class WalkingMovement : public Movement{

public:
    WalkingMovement(float velocity, sf::Vector2f startPosition, sf::Vector2f size);

private:
    bool canJump= true;
};


#endif //PLATFORMGAME_WALKINGMOVEMENT_H
