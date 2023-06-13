//
// Created by nicco on 23/05/2023.
//

#ifndef PLATFORMGAME_AUTOSTARRANGED_H
#define PLATFORMGAME_AUTOSTARRANGED_H

#include"StarRangedAttack.h"
#include"AutoAttack.h"
#include "usefulFunctions.h"

class AutoStarRanged : public StarRangedAttack, AutoAttack {
public:
    AutoStarRanged(sf::Vector2f bulletSize, float bulletSpeed, float attackSpeed, float hitDamage, float knockback,
                   float delay,
                   unsigned short *typeOfSprite, float ScanRange);

    void update(const float &dt, sf::Vector2f centerPosition, bool orientation,
                const std::vector<std::shared_ptr<LevelTile>> &walls) override;

private:
    float scanRange;

    void attackPlayer(sf::Vector2f centerPosition) override;
};


#endif //PLATFORMGAME_AUTOSTARRANGED_H
