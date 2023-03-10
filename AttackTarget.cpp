#include "AttackTarget.h"

AttackTarget::AttackTarget(sf::RectangleShape *newCollisionbox, sf::RectangleShape *newHitbox,
                           sf::Vector2f *newKnockback, int *newHp) :
        collisionbox(newCollisionbox), hitbox(newHitbox), knockback(newKnockback), hp(newHp), nextHp(0),
        nextDelay(0.f) {
    if (collisionbox == nullptr or hitbox == nullptr or knockback == nullptr or hp == nullptr) {
        throw std::runtime_error("target not valid");
    }
}

const sf::RectangleShape& AttackTarget::getCollisionbox() const {
    return *collisionbox;
}

 const sf::RectangleShape &AttackTarget::getHitbox() const {
     return *hitbox;
 }

void AttackTarget::receiveDamage(sf::Vector2f newKnockback, int lifeRemoved, float delay) {
    nextKnockback = newKnockback;
    nextHp = lifeRemoved;
    timer.restart();
    incomingDamage = true;
    nextDelay = delay;
}

void AttackTarget::kill(int lifeRemoved) {
    *hp -= lifeRemoved;
}

void AttackTarget::update() {

    if (incomingDamage) {

        if (timer.getElapsedTime().asSeconds() > nextDelay) {
            *knockback += nextKnockback;
            *hp -= nextHp;
            incomingDamage = false;

        }
    }
}

int AttackTarget::getHp() const {
    return *hp;
}


