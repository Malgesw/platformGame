//
// Created by alessio on 22/03/23.
//

#include "StarRangedAttack.h"

StarRangedAttack::StarRangedAttack(sf::Vector2f bulletSize, float bulletSpeed, float attackSpeed, float hitDamage,
                                   float knockback, float delay, unsigned short *typeOfSprite, bool isPlayer) :
        RangedAttack(bulletSize, bulletSpeed, attackSpeed, hitDamage, knockback, delay, typeOfSprite, isPlayer) {

}

void StarRangedAttack::doDamage() {

    bullets.emplace_back(bulletSize, bulletSpeed, damage, knockback, texture, 2, 2500.f);
    bullets.emplace_back(bulletSize, bulletSpeed, damage, knockback, texture, 2, 2500.f);
    bullets.emplace_back(bulletSize, bulletSpeed, damage, knockback, texture, 2, 2500.f);
    bullets.emplace_back(bulletSize, bulletSpeed, damage, knockback, texture, 2, 2500.f);
    bullets.emplace_back(bulletSize, bulletSpeed, damage, knockback, texture, 2, 2500.f);
    bullets.emplace_back(bulletSize, bulletSpeed, damage, knockback, texture, 2, 2500.f);
    bullets.emplace_back(bulletSize, bulletSpeed, damage, knockback, texture, 2, 2500.f);
    bullets.emplace_back(bulletSize, bulletSpeed, damage, knockback, texture, 2, 2500.f);

    auto i = bullets.begin();
    while (i != bullets.end() and (*i).isActive()) i++;

    for (int j = 0; j < 8; j++) {
        if (i != bullets.end())
            (*i).shoot(nextBulletStartPosition, sf::Vector2f(cos(j * 3.14f / 4), sin(j * 3.14f / 4)));
        i++;

    }



/*
    RangedAttack::hit(sf::Vector2f(1, 0));
    RangedAttack::hit(sf::Vector2f(sqrtf(2) / 2, sqrtf(2) / 2));
    RangedAttack::hit(sf::Vector2f(0, 1));
    RangedAttack::hit(sf::Vector2f(-sqrtf(2) / 2, sqrtf(2) / 2));
    RangedAttack::hit(sf::Vector2f(-1, 0));
    RangedAttack::hit(sf::Vector2f(-sqrtf(2) / 2, -sqrtf(2) / 2));
    RangedAttack::hit(sf::Vector2f(0, -1));
    RangedAttack::hit(sf::Vector2f(sqrtf(2) / 2, -sqrtf(2) / 2));
    */
}

void StarRangedAttack::update(const float &dt, sf::Vector2f centerPosition, bool orientation,
                              const std::vector<std::shared_ptr<LevelTile>> &walls) {
    RangedAttack::update(dt, centerPosition, orientation, walls);
}
