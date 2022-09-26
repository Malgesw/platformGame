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

void Attack::hit() {

    if (cooldown.getElapsedTime().asSeconds()>attackSpeed) {

        cooldown.restart();

        auto i= targets.begin();

        while (i!=targets.end()) {
            auto currentTarget=*i;
            bool enemyCancelled=false;

            if (hitBox.getGlobalBounds().intersects(currentTarget.getHitbox().getGlobalBounds())) {


                sf::Vector2f knockbackDirection;
                knockbackDirection.x= (currentTarget.getHitbox().getPosition().x - hitBox.getPosition().x) /
                                      std::abs(currentTarget.getHitbox().getPosition().x - hitBox.getPosition().x);
                knockbackDirection.y= (currentTarget.getHitbox().getPosition().y - hitBox.getPosition().y) /
                                      std::abs(currentTarget.getHitbox().getPosition().y - hitBox.getPosition().y);

                if(currentTarget.getHp()<=damage){

                    targets.erase(i++);
                    enemyCancelled=true;
                }

                currentTarget.receiveDamage(knockbackDirection * knockbackDistance, damage);

            }
            if(not enemyCancelled){
                i++;
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


    hitBox.setPosition(centerPosition.x-hitBox.getSize().x/2,centerPosition.y-hitBox.getSize().y/2);
}
