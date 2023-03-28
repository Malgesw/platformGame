//
// Created by alessio on 22/03/23.
//

#include "StarRangedAttack.h"

StarRangedAttack::StarRangedAttack(sf::Vector2f bulletSize, float bulletSpeed, float attackSpeed, int hitDamage,
                                   float knockback, unsigned short *typeOfSprite, bool isPlayer) :
        RangedAttack(bulletSize, bulletSpeed, attackSpeed, hitDamage, knockback, typeOfSprite, isPlayer) {

}

void StarRangedAttack::doDamage() {

    RangedAttack::hit(sf::Vector2f(1, 0));
    RangedAttack::hit(sf::Vector2f(sqrtf(2) / 2, sqrtf(2) / 2));
    RangedAttack::hit(sf::Vector2f(0, 1));
    RangedAttack::hit(sf::Vector2f(-sqrtf(2) / 2, sqrtf(2) / 2));
    RangedAttack::hit(sf::Vector2f(-1, 0));
    RangedAttack::hit(sf::Vector2f(-sqrtf(2) / 2, -sqrtf(2) / 2));
    RangedAttack::hit(sf::Vector2f(0, -1));
    RangedAttack::hit(sf::Vector2f(sqrtf(2) / 2, -sqrtf(2) / 2));
}

void StarRangedAttack::update(const float &dt, sf::Vector2f centerPosition, bool orientation,
                              const std::vector<std::shared_ptr<LevelTile>> &walls) {
    RangedAttack::update(dt, centerPosition, orientation, walls);
}
