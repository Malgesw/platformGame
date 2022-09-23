//
// Created by alessio on 19/08/22.
//

#include "Attack.h"

#include <utility>

Attack::Attack(sf::Vector2f size, float speed, float hitDamage, float knockback):
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
        for (auto &t: targets) {
            if (hitBox.getGlobalBounds().intersects(t.getHitbox()->getGlobalBounds())) {

                sf::Vector2f knockbackDirection;
                knockbackDirection.x=(t.getHitbox()->getPosition().x-hitBox.getPosition().x)/std::abs(t.getHitbox()->getPosition().x-hitBox.getPosition().x);
                knockbackDirection.y=(t.getHitbox()->getPosition().y-hitBox.getPosition().y)/std::abs(t.getHitbox()->getPosition().y-hitBox.getPosition().y);
                if(*(t.getHp())<=1){
                    targets.erase(i);
                }
                else{
                    i++;
                }
                //std::cout<<targets.size()<<std::endl;
                t.receiveDamage(knockbackDirection * knockbackDistance, 1);
                //std::cout<<"hp is"<<t.getHp()<<std::endl;

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
