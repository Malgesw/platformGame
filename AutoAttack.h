//
// Created by alessio on 13/09/22.
//

#ifndef PLATFORMGAME_AUTOATTACK_H
#define PLATFORMGAME_AUTOATTACK_H
#include "Attack.h"

class AutoAttack: public Attack{

    AutoAttack(sf::Vector2f size, float speed, float hitDamage, float knockback);


};


#endif //PLATFORMGAME_AUTOATTACK_H
