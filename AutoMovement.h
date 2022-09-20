//
// Created by alessio on 02/09/22.
//

#ifndef PLATFORMGAME_AUTOMOVEMENT_H
#define PLATFORMGAME_AUTOMOVEMENT_H

#include "Pathfinder.h"

class AutoMovement {

public:

    virtual void rest()=0;
    virtual void aggro(const float &dt, sf::Vector2f playerPosition)=0;

protected:

    bool isTriggered;
    std::unique_ptr<Pathfinder> pathfinder;


};


#endif //PLATFORMGAME_AUTOMOVEMENT_H
