#include "Bullet.h"

Bullet::Bullet(sf::Vector2f size, int speed, int damage, int knockback, sf::Texture *texture, int maxCollisions)
        : speed(speed), damage(damage), knockback(knockback), maxCollisions(maxCollisions) {


    body = sf::RectangleShape(size);
    animation = std::make_unique<Animation>(texture, sf::Vector2i(4, 1), 0.15f, size);
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


        for (auto &o: walls) {

            if (std::abs(o->getGlobalBounds().top - body.getGlobalBounds().top) < 400 and
                std::abs(o->getGlobalBounds().left - body.getGlobalBounds().left) < 600) {

                sf::FloatRect Bounds = body.getGlobalBounds();
                sf::FloatRect objectBounds;
                sf::FloatRect bulletpos = Bounds;


                objectBounds = o->getGlobalBounds();
                if (objectBounds.intersects(bulletpos)) {


                    //Bottom
                    if (Bounds.top < objectBounds.top &&
                        Bounds.top + Bounds.height < objectBounds.top + objectBounds.height &&
                        Bounds.left < objectBounds.left + objectBounds.width &&
                        Bounds.left + Bounds.width > objectBounds.left) {

                        direction.y = -direction.y;
                        collisionsCounter++;
                    }

                        //Top
                    else if (Bounds.top > objectBounds.top &&
                             Bounds.top + Bounds.height > objectBounds.top + objectBounds.height &&
                             Bounds.left < objectBounds.left + objectBounds.width &&
                             Bounds.left + Bounds.width > objectBounds.left) {

                        direction.y = -direction.y;
                        collisionsCounter++;
                    }


                        //Right
                    else if (Bounds.left < objectBounds.left &&
                             Bounds.left + Bounds.width < objectBounds.left + objectBounds.width &&
                             Bounds.top < objectBounds.top + objectBounds.height &&
                             Bounds.top + Bounds.height > objectBounds.top) {

                        direction.x = -direction.x;
                        collisionsCounter++;
                    }

                        //Left
                    else if (Bounds.left > objectBounds.left &&
                             Bounds.left + Bounds.width > objectBounds.left + objectBounds.width &&
                             Bounds.top < objectBounds.top + objectBounds.height &&
                             Bounds.top + Bounds.height > objectBounds.top) {

                        direction.x = -direction.x;
                        collisionsCounter++;
                    }


                }


            }
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

bool Bullet::isActive() const {
    return active;
}

bool Bullet::isCollided() const {
    if (collisionsCounter >= maxCollisions) return true;
    else return false;
}

