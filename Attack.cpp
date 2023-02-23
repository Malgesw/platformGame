//
// Created by alessio on 19/08/22.
//

#include "Attack.h"
#include <utility>

Attack::Attack(sf::Vector2f size, float speed, int hitDamage, float knockback):
        attackSpeed(speed), damage(hitDamage), knockback(knockback){

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

bool Attack::checkDeath(const AttackTarget &target) const{

    if(target.getHp()<=damage){

        notify('k');
        return true;
    }
    else{
        return false;
    }
}


void Attack::attach(Observer *o) {
    observers.push_back(o);
}

void Attack::detach(Observer *o) {
    observers.remove(o);
}

void Attack::notify(char category) const {
    for(auto &o : observers){
        o->getNews(category);
    }
}

