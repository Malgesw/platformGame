//
// Created by alessio on 12/09/22.
//

#ifndef PLATFORMGAME_ATTACKTARGET_H
#define PLATFORMGAME_ATTACKTARGET_H

#include "headers.h"

class AttackTarget {
public:

    AttackTarget(sf::RectangleShape& newCollisionbox,sf::RectangleShape& newHitbox);
     sf::RectangleShape &getCollisionbox() const;
     sf::RectangleShape &getHitbox() const;

private:

      sf::RectangleShape& collisionbox;
      sf::RectangleShape& hitbox;



};


#endif //PLATFORMGAME_ATTACKTARGET_H
