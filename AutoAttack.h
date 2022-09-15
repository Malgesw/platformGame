//
// Created by alessio on 13/09/22.
//

#ifndef PLATFORMGAME_AUTOATTACK_H
#define PLATFORMGAME_AUTOATTACK_H
#include "Attack.h"

class AutoAttack: public Attack{
public:

    AutoAttack(sf::Vector2f size, float speed, float hitDamage, float knockback);
    void update(sf::Vector2f centerPosition) override;
};


#endif //PLATFORMGAME_AUTOATTACK_H
