
#ifndef PLATFORMGAME_GLIDINGMOVEMENT_H
#define PLATFORMGAME_GLIDINGMOVEMENT_H


#include "Movement.h"

class GlidingMovement : public Movement {

public:
    GlidingMovement(float velocity, sf::Vector2f startPosition, sf::Vector2f size, float height,
                    unsigned short *typeOfSprite, bool isPlayer);

    void moveUp() override;

    void moveDown() override;

    void moveLeft() override;

    void moveRight() override;

    float getJumpHeight() const;


private:
    float jumpHeight;

};


#endif //PLATFORMGAME_GLIDINGMOVEMENT_H
