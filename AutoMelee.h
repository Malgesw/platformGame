#ifndef PLATFORMGAME_AUTOMELEE_H
#define PLATFORMGAME_AUTOMELEE_H

#include "MeleeAttack.h"
#include"AutoAttack.h"

class AutoMelee: public MeleeAttack,AutoAttack{

public:
    AutoMelee(sf::Vector2f size, float speed, int hitDamage, float knockback, unsigned short * typeOfSprite);
    void update(sf::Vector2f centerPosition,bool facingRight) override;

private:
    void attackPlayer(sf::Vector2f centerPosition) override;
};


#endif //PLATFORMGAME_AUTOMELEE_H
