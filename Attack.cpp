#include "Attack.h"
#include <utility>

Attack::Attack(sf::Vector2f size, float speed, int hitDamage, float knockback, unsigned short* typeOfSprite):
        attackSpeed(speed), damage(hitDamage), knockbackDistance(knockback),typeOfSprite(typeOfSprite) {

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

void Attack::hit() {
    if (*typeOfSprite == MOVERIGHT or *typeOfSprite == JUMPRIGHT or *typeOfSprite == IDLERIGHT) {
        *typeOfSprite = ATTACKRIGHT;
    } else {
        *typeOfSprite = ATTACKLEFT;
    }
}

void Attack::update(sf::Vector2f centerPosition, bool orientation) {
    for (auto &t: targets) {
        t.update();
    }
}

