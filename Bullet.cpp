#include "Bullet.h"

Bullet::Bullet(sf::Vector2f size, int speed, int damage,int knockback,sf::Texture* texture)
:speed(speed),damage(damage),knockback(knockback) {


    body=sf::RectangleShape(size);
    animation= std::make_unique<Animation>(texture,sf::Vector2i(4,1),0.15f,size);
}



std::list<AttackTarget *>::const_iterator Bullet::update(const float &dt, const std::list<AttackTarget *> &targets,
                                                         const std::vector<std::shared_ptr<LevelTile>> &walls) {

    animation->update(body.getGlobalBounds(), dt);
    auto enemyDestroyed = targets.end();

    if (active) {

        body.move(direction * dt * static_cast<float>(speed));

        auto i = targets.begin();

        while (i!=targets.end()) {
            auto &currentTarget = *i;
            if (body.getGlobalBounds().intersects((currentTarget->getCollisionbox().getGlobalBounds()))) {

                if (currentTarget->getHp() <= damage) {
                    enemyDestroyed = i;
                    //currentTarget.kill(damage);
                    currentTarget->receiveDamage(static_cast<float>(knockback) * direction, damage);
                }
                collided = true;
                currentTarget->receiveDamage(static_cast<float>(knockback) * direction, damage);
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
    animation->render(target);
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

