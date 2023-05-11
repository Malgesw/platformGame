#ifndef PLATFORMGAME_ATTACKTARGET_H
#define PLATFORMGAME_ATTACKTARGET_H

#include "headers.h"
#include "SpecialAbility.h"

class AttackTarget {
public:

    AttackTarget();

    const sf::RectangleShape &getHitbox() const;

    const sf::RectangleShape &getCollisionbox() const;

    void receiveDamage(sf::Vector2f newKnockback, float lifeRemoved) noexcept(false);

    //void kill(int lifeRemoved);

    void update(sf::RectangleShape *newCollisionbox, sf::RectangleShape *newHitbox, sf::Vector2f *newKnockback,
                float *newHp, unsigned short int newStatus);

    float getHp() const;

    unsigned short int getStatus() const {
        return status;
    }


private:
    //sf::Clock timer;
    sf::RectangleShape *hitbox;
    sf::RectangleShape *collisionbox;
    sf::Vector2f *knockback;
    //sf::Vector2f nextKnockback;
    //float nextDelay;
    float *hp;
    unsigned short int status;
    //int nextHp;
    //bool incomingDamage = false;

};


#endif //PLATFORMGAME_ATTACKTARGET_H
