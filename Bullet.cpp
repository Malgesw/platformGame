//
// Created by alessio on 29/11/22.
//

#include "Bullet.h"

Bullet::Bullet(sf::Vector2f size, int speed, int damage,int knockback)
:speed(speed),damage(damage),knockback(knockback) {

    body=sf::RectangleShape(size);
}



std::list<AttackTarget>::const_iterator Bullet::update(const float &dt, std::list<AttackTarget> &targets,
                    const std::vector<std::shared_ptr<LevelTile>> &walls) {

    auto enemyDestroyed= targets.end();

    if(active) {

        body.move(direction*dt*static_cast<float>(speed));

        auto i= targets.begin();

        while (i!=targets.end()) {
            auto &currentTarget = *i;
            if (body.getGlobalBounds().intersects((currentTarget.getCollisionbox().getGlobalBounds()))) {

                if(currentTarget.getHp()<=damage) {
                    enemyDestroyed = i;
                    currentTarget.kill(damage);
                }
                collided=true;
                std::cout<<"la vita del namico prima del colpo: "<<currentTarget.getHp()<<std::endl;
                currentTarget.receiveDamage(static_cast<float>(knockback)*direction,damage,0.f);
                std::cout<<"la vita del namico dopo il colpo: "<<currentTarget.getHp()<<std::endl;
            }
            i++;
        }


        for (const auto &w: walls) {
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

