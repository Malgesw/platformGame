#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(sf::Vector2f size, float speed, int hitDamage, float knockback, float delay,
                         unsigned short *typeOfSprite)
        : Attack(size, speed, delay,
                 hitDamage,
                 knockback, typeOfSprite) {
}

void MeleeAttack::doDamage() {


    auto i = targets.begin();

    while (i != targets.end()) {

        auto &currentTarget = *i;
        bool enemyCancelled = false;

        if (hitBox.getGlobalBounds().intersects(currentTarget->getCollisionbox().getGlobalBounds())) {


            sf::Vector2f knockbackDirection;


            if (std::abs(currentTarget->getHitbox().getPosition().x - hitBox.getPosition().x) > 1.f) {

                knockbackDirection.x =
                        (currentTarget->getHitbox().getPosition().x - hitBox.getPosition().x) /
                        std::abs(
                                currentTarget->getHitbox().getPosition().x -
                                hitBox.getPosition().x);
            } else knockbackDirection.x = 0;

            if (std::abs(currentTarget->getHitbox().getPosition().y - hitBox.getPosition().y) > 1.f) {
                knockbackDirection.y =
                        (currentTarget->getHitbox().getPosition().y - hitBox.getPosition().y) /
                        std::abs(
                                currentTarget->getHitbox().getPosition().y -
                                hitBox.getPosition().y);
            } else knockbackDirection.y = 0;

            if (checkDeath(currentTarget)) {
                //currentTarget.kill(damage);
                currentTarget->receiveDamage(knockbackDirection * knockback, damage);
                targets.erase(i++);
                enemyCancelled = true;
            } else
                currentTarget->receiveDamage(knockbackDirection * knockback, damage);

        }
        if (not enemyCancelled) {
            i++;
        }

    }


}

void MeleeAttack::update(const float &dt, sf::Vector2f centerPosition, bool facingRight,const std::vector<std::shared_ptr<LevelTile>> &walls) {

    Attack::update(dt,centerPosition, facingRight,walls);
    hitBox.setPosition(facingRight ? centerPosition.x - hitBox.getSize().x / 2 - attackoffset : centerPosition.x -
                                                                                                hitBox.getSize().x / 2 +
                                                                                                attackoffset,
                       centerPosition.y - hitBox.getSize().y / 2);
}


