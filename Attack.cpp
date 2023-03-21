#include "Attack.h"
#include <utility>

Attack::Attack(sf::Vector2f size, float speed, int hitDamage, float knockback, unsigned short* typeOfSprite):
        attackSpeed(speed), damage(hitDamage), knockback(knockback),typeOfSprite(typeOfSprite) {

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
        notify(ENEMYKILLED);
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

void Attack::notify(unsigned short category) const {
    for (auto &o: observers) {
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

void Attack::applyCollisionDamage() {

    auto i = targets.begin();

    while (i != targets.end()) {

        auto &currentTarget = *i;
        bool enemyCancelled = false;

        if (hitBox.getGlobalBounds().intersects(currentTarget.getCollisionbox().getGlobalBounds())) {


            sf::Vector2f knockbackDirection;

            if (std::abs(currentTarget.getHitbox().getPosition().x - hitBox.getPosition().x) > 1.f) {

                knockbackDirection.x = (currentTarget.getHitbox().getPosition().x - hitBox.getPosition().x) /
                                       std::abs(currentTarget.getHitbox().getPosition().x - hitBox.getPosition().x);
            } else knockbackDirection.x = 0;

            if (std::abs(currentTarget.getHitbox().getPosition().y - hitBox.getPosition().y) > 1.f) {
                knockbackDirection.y = (currentTarget.getHitbox().getPosition().y - hitBox.getPosition().y) /
                                       std::abs(currentTarget.getHitbox().getPosition().y - hitBox.getPosition().y);
            } else knockbackDirection.y = 0;

            if (checkDeath(currentTarget)) {
                currentTarget.kill(damage);
                targets.erase(i++);
                enemyCancelled = true;
            }

            currentTarget.receiveDamage(knockbackDirection * knockback, damage, 0.0f);

        }
        if (not enemyCancelled) {
            i++;
        }

    }
}


void Attack::update(const float &dt, sf::Vector2f centerPosition, bool orientation,
                    const std::vector<std::shared_ptr<LevelTile>> &walls) {
    for (auto &t: targets) {
        t.update();
    }
}

