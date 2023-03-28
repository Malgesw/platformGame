#ifndef PLATFORMGAME_RANGEDATTACK_H
#define PLATFORMGAME_RANGEDATTACK_H

#include "Attack.h"
#include "Bullet.h"

class RangedAttack :public Attack{

public:

    RangedAttack(sf::Vector2f bulletSize, float bulletSpeed, float attackSpeed, int hitDamage, float knockback,
                 unsigned short *typeOfSprite, bool isPlayer);


    void hit(sf::Vector2f direction);

    void update(const float &dt, sf::Vector2f centerPosition, bool orientation,
                const std::vector<std::shared_ptr<LevelTile>> &walls) override;

    void render(sf::RenderTarget &target) override;


protected:
    sf::Texture *texture;
    sf::Vector2f bulletSize;
    float bulletSpeed;
    std::vector<Bullet> bullets;
    sf::Vector2f nextBulletDirection;
    sf::Vector2f nextBulletStartPosition;
    float attackoffset = 0.f;

    void doDamage() override;

};


#endif //PLATFORMGAME_RANGEDATTACK_H
