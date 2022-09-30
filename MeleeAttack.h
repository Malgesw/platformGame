//
// Created by alessio on 26/09/22.
//

#ifndef PLATFORMGAME_MELEEATTACK_H
#define PLATFORMGAME_MELEEATTACK_H

#include "Attack.h"


class MeleeAttack :public Attack{

public:
    MeleeAttack(sf::Vector2f size, float speed, int hitDamage, float knockback);
    void hit() override;
    void update(sf::Vector2f centerPosition, bool orientation) override;

protected:
    float attackoffset=0.f;
};


#endif //PLATFORMGAME_MELEEATTACK_H
