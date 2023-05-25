//
// Created by nicco on 23/05/2023.
//

#include "AutoStarRanged.h"

AutoStarRanged::AutoStarRanged(sf::Vector2f bulletSize, float bulletSpeed, float attackSpeed, float hitDamage,
                               float knockback,
                               float delay,
                               unsigned short *typeOfSprite, float scanRange) : StarRangedAttack(bulletSize,
                                                                                                 bulletSpeed,
                                                                                                 attackSpeed,
                                                                                                 hitDamage, knockback,
                                                                                                 delay,
                                                                                                 typeOfSprite,
                                                                                                 false),
                                                                                scanRange(scanRange) {

}


void AutoStarRanged::update(const float &dt, sf::Vector2f centerPosition, bool orientation,
                            const std::vector<std::shared_ptr<LevelTile>> &walls) {
    StarRangedAttack::update(dt, centerPosition, orientation, walls);
    attackPlayer(centerPosition);
}


void AutoStarRanged::attackPlayer(sf::Vector2f centerPosition) {
    if (not targets.empty()) {
        auto a = hitBox.getPosition();
        auto b = (*targets.begin())->getCollisionbox().getPosition();

        if (findDistance(a, b) < scanRange) {
            Attack::hit();
        }
    }

}