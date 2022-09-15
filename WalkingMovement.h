//
// Created by alessio on 26/07/22.
//

#ifndef PLATFORMGAME_WALKINGMOVEMENT_H
#define PLATFORMGAME_WALKINGMOVEMENT_H

#include "Movement.h"

class WalkingMovement : public Movement{

public:
    WalkingMovement(float velocity, sf::Vector2f startPosition, sf::Vector2f size,float height);
    void moveUp() override;
    void moveDown() override;
    float getJumpHeight() const;



private:
    float jumpHeight;

};


#endif //PLATFORMGAME_WALKINGMOVEMENT_H
