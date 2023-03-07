//
// Created by alessio on 06/03/23.
//

#include "AutoRanged.h"



void AutoRanged::update(const float &dt, sf::Vector2f centerPosition, bool orientation,
                        const std::vector<std::shared_ptr<LevelTile>> &walls) {
    RangedAttack::update(dt, centerPosition, orientation, walls);
}

AutoRanged::AutoRanged(sf::Vector2f bulletSize, float bulletSpeed, float attackSpeed, int hitDamage, float knockback,
                       unsigned short *typeOfSprite, float scanRange) : RangedAttack(bulletSize, bulletSpeed, attackSpeed,
                                                                                   hitDamage, knockback, typeOfSprite,
                                                                                   false), scanRange(scanRange) {

}

void AutoRanged::attackPlayer(sf::Vector2f centerPosition) {
if(distance(hitBox.getPosition(),targets.begin()->getCollisionbox().getPosition())<scanRange){

}
}