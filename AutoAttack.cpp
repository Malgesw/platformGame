//
// Created by alessio on 13/09/22.
//

#include "AutoAttack.h"

AutoAttack::AutoAttack(sf::Vector2f size, float speed, float hitDamage, float knockback) : Attack(size, speed,hitDamage,knockback){


}

void AutoAttack::update(sf::Vector2f centerPosition) {
    if (hitBox.getGlobalBounds().intersects(targets.front().getCollisionbox()->getGlobalBounds())){
        hit();
    }
    Attack::update(centerPosition);
}
