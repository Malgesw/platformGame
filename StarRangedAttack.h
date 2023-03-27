//
// Created by alessio on 22/03/23.
//

#ifndef PLATFORMGAME_STARRANGEDATTACK_H
#define PLATFORMGAME_STARRANGEDATTACK_H

#include "RangedAttack.h"

class StarRangedAttack : public RangedAttack {
    StarRangedAttack(sf::Vector2f bulletSize, float bulletSpeed, float attackSpeed, int hitDamage, float knockback,
                     unsigned short *typeOfSprite, bool isPlayer);

    void hit() override;

    void update(const float &dt, sf::Vector2f centerPosition, bool orientation,
                const std::vector<std::shared_ptr<LevelTile>> &walls) override;

};


#endif //PLATFORMGAME_STARRANGEDATTACK_H
