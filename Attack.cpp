//
// Created by alessio on 19/08/22.
//

#include "Attack.h"
#include <utility>

Attack::Attack(sf::Vector2f size, float speed, int hitDamage, float knockback):
        attackSpeed(speed), damage(hitDamage), knockbackDistance(knockback) {

hitBox=sf::RectangleShape(size);
hitBox.setFillColor(sf::Color::Blue);
}

sf::RectangleShape& Attack::getHitBox(){
    return hitBox;
}



void Attack::addTargets(const std::vector<AttackTarget>& newTargets) {

    for(auto &t : newTargets){
        targets.push_back(t);
    }
}

void Attack::clearTargets() {
    targets.clear();
}

