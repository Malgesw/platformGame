//
// Created by alessio on 12/09/22.
//

#include "AttackTarget.h"

AttackTarget::AttackTarget(sf::RectangleShape* newCollisionbox,sf::RectangleShape* newHitbox,sf::Vector2f *newKnockback,int *newhp):
collisionbox(newCollisionbox),hitbox(newHitbox),knockback(newKnockback),hp(newhp) {}

sf::RectangleShape *AttackTarget::getCollisionbox() const {
    return collisionbox;
}

 sf::RectangleShape *AttackTarget::getHitbox() const {
    return hitbox;
}

void AttackTarget::receiveDamage(sf::Vector2f newKnockback, int lifeRemoved) const{
    *knockback += newKnockback;
    *hp-=lifeRemoved;
}

const int *AttackTarget::getHp() const{
    return hp;
}


