//
// Created by alessio on 26/09/22.
//

#include "AutoMelee.h"

AutoMelee::AutoMelee(sf::Vector2f size, float speed, int hitDamage, float knockback) : MeleeAttack(size, speed,
                                                                                                   hitDamage,
                                                                                                   knockback) {
    attackoffset=96.f;

}

void AutoMelee::attackPlayer(sf::Vector2f centerPosition) {
    if (hitBox.getGlobalBounds().intersects(targets.front().getCollisionbox().getGlobalBounds())) {
        hit();
    }
}

void AutoMelee::update(sf::Vector2f centerPosition,bool facingRight) {
    MeleeAttack::update(centerPosition,facingRight);
    attackPlayer(centerPosition);
}


