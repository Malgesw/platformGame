//
// Created by alessio on 12/09/22.
//

#ifndef PLATFORMGAME_ATTACKTARGET_H
#define PLATFORMGAME_ATTACKTARGET_H

#include "headers.h"

class AttackTarget {
public:

    AttackTarget(sf::RectangleShape& newCollisionbox,sf::RectangleShape& newHitbox,sf::Vector2f& newKnockback, int& newHp);
    sf::RectangleShape &getHitbox() const;
    sf::RectangleShape &getCollisionbox() const;
    void receiveDamage(sf::Vector2f newKnockback,int lifeRemoved) const;


private:
      sf::RectangleShape& hitbox;
      sf::RectangleShape& collisionbox;
      sf::Vector2f &knockback;
      int &hp;

};


#endif //PLATFORMGAME_ATTACKTARGET_H
