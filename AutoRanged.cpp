//
// Created by alessio on 06/03/23.
//

#include "AutoRanged.h"


AutoRanged::AutoRanged(sf::Vector2f bulletSize, float bulletSpeed, float attackSpeed, float hitDamage, float knockback,
                       unsigned short *typeOfSprite, float scanRange) : RangedAttack(bulletSize, bulletSpeed,
                                                                                     attackSpeed,
                                                                                     hitDamage, knockback, typeOfSprite,
                                                                                     false), scanRange(scanRange) {

}


void AutoRanged::update(const float &dt, sf::Vector2f centerPosition, bool orientation,
                        const std::vector<std::shared_ptr<LevelTile>> &walls) {
    RangedAttack::update(dt, centerPosition, orientation, walls);
    attackPlayer(centerPosition);
}


void AutoRanged::attackPlayer(sf::Vector2f centerPosition) {
    if (not targets.empty()) {
        auto a = hitBox.getPosition();
        auto b = (*targets.begin())->getCollisionbox().getPosition();

        if (findDistance(a, b) < scanRange) {
            hit(findDirection(a, b));
        }
    }

}