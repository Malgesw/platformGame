#include "AttackTarget.h"

AttackTarget::AttackTarget() :
        collisionbox(nullptr), hitbox(nullptr), knockback(nullptr), hp(nullptr), status(0) {

}


const sf::RectangleShape &AttackTarget::getCollisionbox() const {
    return *collisionbox;
}

const sf::RectangleShape &AttackTarget::getHitbox() const {
    return *hitbox;
}

void AttackTarget::receiveDamage(sf::Vector2f newKnockback, float lifeRemoved) {

    if (collisionbox == nullptr or hitbox == nullptr or knockback == nullptr or hp == nullptr) {
        throw std::runtime_error("target not valid");
    }
    if (status != INVINCIBLE) {
        if (status != UNMOVABLE)
            *knockback += newKnockback;
        *hp -= lifeRemoved;
    }

    /* nextKnockback = newKnockback;
     nextHp = lifeRemoved;
     timer.restart();
     incomingDamage = true;
     nextDelay = delay;*/
}

/*
void AttackTarget::kill(int lifeRemoved) {
    *hp -= lifeRemoved;
}
*/

void
AttackTarget::update(sf::RectangleShape *newCollisionbox, sf::RectangleShape *newHitbox, sf::Vector2f *newKnockback,
                     float *newHp, unsigned short int newStatus) {
    collisionbox = newCollisionbox;
    hitbox = newHitbox;
    knockback = newKnockback;
    hp = newHp;
    status = newStatus;

    /*
    if (incomingDamage) {

        if (timer.getElapsedTime().asSeconds() > nextDelay) {
            *knockback += nextKnockback;
            *hp -= nextHp;
            incomingDamage = false;
        }
    }
     */
}

float AttackTarget::getHp() const {
    return *hp;
}


