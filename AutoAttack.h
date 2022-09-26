//
// Created by alessio on 13/09/22.
//

#ifndef PLATFORMGAME_AUTOATTACK_H
#define PLATFORMGAME_AUTOATTACK_H
#include "Attack.h"

class AutoAttack{
public:

    virtual ~AutoAttack()=default;
    virtual void attackPlayer(sf::Vector2f centerPosition)=0;
};


#endif //PLATFORMGAME_AUTOATTACK_H
