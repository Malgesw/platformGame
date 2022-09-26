//
// Created by alessio on 12/09/22.
//

#include "AttackTarget.h"

AttackTarget::AttackTarget(sf::RectangleShape* newCollisionbox,sf::RectangleShape* newHitbox,sf::Vector2f *newKnockback,int *newhp):
collisionbox(newCollisionbox),hitbox(newHitbox),knockback(newKnockback),hp(newhp) {
    if(collisionbox== nullptr or hitbox== nullptr or knockback== nullptr or hp== nullptr){
        throw std::runtime_error("target not valid");
    }
}

const sf::RectangleShape& AttackTarget::getCollisionbox() const {
    return *collisionbox;
}

 const sf::RectangleShape &AttackTarget::getHitbox() const {
    return *hitbox;
}

void AttackTarget::receiveDamage(sf::Vector2f newKnockback, int lifeRemoved) const{
    *knockback += newKnockback;
    *hp-=lifeRemoved;
}

int AttackTarget::getHp() const{
    return *hp;
}


