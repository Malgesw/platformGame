#include "AutoMelee.h"

AutoMelee::AutoMelee(sf::Vector2f size, float speed, float hitDamage, float knockback, float delay, float attackOffset,
                     unsigned short *typeOfSprite) : MeleeAttack(size, speed,
                                                                 hitDamage,
                                                                 knockback, delay, attackOffset, typeOfSprite) {
    attackoffset = 96.f;

}

void AutoMelee::attackPlayer(sf::Vector2f centerPosition) {
    if (not targets.empty()) {
        if (hitBox.getGlobalBounds().intersects(targets.front()->getCollisionbox().getGlobalBounds())) {
            hit();
        }
    }
}

void AutoMelee::update(const float &dt, sf::Vector2f centerPosition, bool facingRight,const std::vector<std::shared_ptr<LevelTile>> &walls) {
    MeleeAttack::update(dt,centerPosition,facingRight,walls);
    attackPlayer(centerPosition);
}


