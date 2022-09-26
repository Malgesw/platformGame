//
// Created by alessio on 26/09/22.
//

#ifndef PLATFORMGAME_AUTOMELEE_H
#define PLATFORMGAME_AUTOMELEE_H

#include "MeleeAttack.h"
#include"AutoAttack.h"

class AutoMelee: public MeleeAttack,AutoAttack{

public:
    AutoMelee(sf::Vector2f size, float speed, int hitDamage, float knockback);
    void update(sf::Vector2f centerPosition) override;

private:
    void attackPlayer(sf::Vector2f centerPosition) override;
};


#endif //PLATFORMGAME_AUTOMELEE_H
