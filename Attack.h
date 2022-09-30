//
// Created by alessio on 19/08/22.
//

#ifndef PLATFORMGAME_ATTACK_H
#define PLATFORMGAME_ATTACK_H



#include "headers.h"
#include "AttackTarget.h"


class Attack {

public:

    Attack(sf::Vector2f size, float speed, int hitDamage, float knockback);
    virtual ~Attack()=default;
    virtual void hit()=0;
    sf::RectangleShape& getHitBox();
    void addTargets(const std::vector<AttackTarget>& newTargets);
    void clearTargets();
    virtual void update(sf::Vector2f centerPosition, bool orientation)=0;


protected:
    sf::Clock cooldown;
    float attackSpeed;
    int damage;
    float knockbackDistance;
    sf::RectangleShape hitBox;
    std::list<AttackTarget> targets;
};


#endif //PLATFORMGAME_ATTACK_H
