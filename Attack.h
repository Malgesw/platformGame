//
// Created by alessio on 19/08/22.
//

#ifndef PLATFORMGAME_ATTACK_H
#define PLATFORMGAME_ATTACK_H



#include "headers.h"
#include "AttackTarget.h"


class Attack {

public:

    Attack(sf::Vector2f size, float speed, float hitDamage, float knockback, std::vector<AttackTarget> enemies);
    void hit();
    sf::RectangleShape& getHitBox();


private:
    sf::Clock cooldown;
    float attackSpeed;
    float damage;
    float knockbackMultiplier;
    sf::RectangleShape hitBox;
    std::vector<AttackTarget> targets;
};


#endif //PLATFORMGAME_ATTACK_H
