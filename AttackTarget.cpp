//
// Created by alessio on 12/09/22.
//

#include "AttackTarget.h"

AttackTarget::AttackTarget(sf::RectangleShape &newCollisionbox,sf::RectangleShape &newHitbox):collisionbox(newCollisionbox),hitbox(newHitbox) {

}

 sf::RectangleShape &AttackTarget::getCollisionbox() const {
    return collisionbox;
}

 sf::RectangleShape &AttackTarget::getHitbox() const {
    return hitbox;
}
