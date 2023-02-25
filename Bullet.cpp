//
// Created by alessio on 29/11/22.
//

#include "Bullet.h"

Bullet::Bullet(sf::Vector2f size, int speed, int damage,int knockback)
:speed(speed),damage(damage),knockback(knockback) {

    body=sf::RectangleShape(size);
}



std::list<AttackTarget>::const_iterator Bullet::update(const float &dt, const std::list<AttackTarget> &targets,
                    const std::vector<std::shared_ptr<LevelTile>> &walls) {

    auto enemyDestroyed= targets.end();

    if(active) {

        body.move(direction*dt*static_cast<float>(speed));

        auto i= targets.begin();

        while (i!=targets.end()) {
            if (body.getGlobalBounds().intersects(((*i).getCollisionbox().getGlobalBounds()))) {

                if((*i).getHp()<=damage) {
                    enemyDestroyed = i;
                }
                collided=true;
                (*i).receiveDamage(static_cast<float>(knockback)*direction,damage);
            }
            i++;
        }


        for (auto &w: walls) {
            if (body.getGlobalBounds().intersects(w->getGlobalBounds()))
                collided = true;
        }
    }
        return enemyDestroyed;

}

void Bullet::render(sf::RenderTarget &target) {
    if (active)
        target.draw(body);
}

void Bullet::shoot(sf::Vector2f startPosition, sf::Vector2f newDirection){
    body.setPosition(startPosition);
    direction=newDirection;
    active=true;
}

void Bullet::setDirection(sf::Vector2f newDirection) {
    direction=newDirection;
}

bool Bullet::isActive() {
    return active;
}

bool Bullet::isCollided() {
    return collided;
}

