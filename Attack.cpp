//
// Created by alessio on 19/08/22.
//

#include "Attack.h"

#include <utility>

Attack::Attack(sf::Vector2f size, float speed, float hitDamage, float knockback, std::vector<AttackTarget> enemies):
attackSpeed(speed),damage(hitDamage),targets(std::move(enemies)),knockbackMultiplier(knockback) {

hitBox=sf::RectangleShape(size);
hitBox.setFillColor(sf::Color::Blue);

}

sf::RectangleShape& Attack::getHitBox(){
    return hitBox;
}

void Attack::hit() {
    if (cooldown.getElapsedTime().asSeconds()>attackSpeed) {
        cooldown.restart();
        for (auto &t: targets) {
            if (hitBox.getGlobalBounds().intersects(t.getHitbox().getGlobalBounds())) {

                sf::Vector2f knockback((t.getHitbox().getPosition()-hitBox.getPosition())*knockbackMultiplier);

                t.getCollisionbox().move(knockback);

            }
        }
    }
}
