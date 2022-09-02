//
// Created by alessio on 02/09/22.
//

#ifndef PLATFORMGAME_AUTOMOVEMENT_H
#define PLATFORMGAME_AUTOMOVEMENT_H

#include "Pathfinder.h"

class AutoMovement {

public:

    virtual void rest()=0;
    virtual void aggro()=0;

private:

    bool isTriggered;
    std::unique_ptr<Pathfinder> pathfinder;


};


#endif //PLATFORMGAME_AUTOMOVEMENT_H
