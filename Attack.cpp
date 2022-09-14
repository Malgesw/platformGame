//
// Created by alessio on 19/08/22.
//

#include "Attack.h"

#include <utility>

Attack::Attack(sf::Vector2f size, float speed, float hitDamage, float knockback):
attackSpeed(speed),damage(hitDamage),knockbackMultiplier(knockback) {

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

                //std::cout<<cooldown.getElapsedTime().asSeconds()<<std::endl;
                sf::Vector2f knockback((t.getHitbox().getPosition()-hitBox.getPosition())*knockbackMultiplier);
                t.getCollisionbox().move(knockback);

            }
        }
    }
}

void Attack::addTargets(const std::vector<AttackTarget>& newTargets) {

    for(auto &t : newTargets){
        targets.push_back(t);
    }
}

void Attack::clearTargets() {
    targets.clear();
}

void Attack::update(sf::Vector2f centerPosition) {
hitBox.setPosition(centerPosition.x-hitBox.getSize().x,centerPosition.y-hitBox.getSize().y);
}
