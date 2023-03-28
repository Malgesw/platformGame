#ifndef PLATFORMGAME_ATTACKTARGET_H
#define PLATFORMGAME_ATTACKTARGET_H

#include "headers.h"

class AttackTarget {
public:

    AttackTarget();

    const sf::RectangleShape &getHitbox() const;

    const sf::RectangleShape &getCollisionbox() const;

    void receiveDamage(sf::Vector2f newKnockback, int lifeRemoved) noexcept(false);

    //void kill(int lifeRemoved);

    void update(sf::RectangleShape *newCollisionbox, sf::RectangleShape *newHitbox, sf::Vector2f *newKnockback,
                int *newHp);

    int getHp() const;


private:
    //sf::Clock timer;
    sf::RectangleShape *hitbox;
    sf::RectangleShape *collisionbox;
    sf::Vector2f *knockback;
    //sf::Vector2f nextKnockback;
    //float nextDelay;
    int *hp;
    //int nextHp;
    //bool incomingDamage = false;

};


#endif //PLATFORMGAME_ATTACKTARGET_H
