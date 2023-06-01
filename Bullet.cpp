#include "Bullet.h"

Bullet::Bullet(sf::Vector2f size, float speed, float damage, float knockback, sf::Texture *texture, int maxCollisions)
        : speed(speed), damage(damage), knockback(knockback), maxCollisions(maxCollisions) {


    body = sf::RectangleShape(size);
    animation = std::make_unique<Animation>(texture, sf::Vector2i(4, 1), 0.15f, size);
}



std::list<AttackTarget *>::const_iterator Bullet::update(const float &dt, const std::list<AttackTarget *> &targets,
                                                         const std::vector<std::shared_ptr<LevelTile>> &walls) {

    animation->update(body.getGlobalBounds(), dt);
    auto enemyDestroyed = targets.end();

    if (active) {


        body.move(direction * dt * speed);

        auto i = targets.begin();

        while (i!=targets.end()) {
            auto &currentTarget = *i;
            if (/*currentTarget->isValid() and*/ body.getGlobalBounds().intersects(
                    (currentTarget->getCollisionbox().getGlobalBounds()))) {

                if (currentTarget->getHp() <= damage and currentTarget->getStatus() != INVINCIBLE) {
                    enemyDestroyed = i;
                    //currentTarget.kill(damage);
                    currentTarget->receiveDamage(knockback * direction, damage);
                } else
                    currentTarget->receiveDamage(knockback * direction, damage);
                collided = true;
            }
            i++;
        }

        float Tolerance = std::sqrt(speed) * dt * 100;
        for (auto &o: walls) {

            if (std::abs(o->getGlobalBounds().top - body.getGlobalBounds().top) < 400 and
                std::abs(o->getGlobalBounds().left - body.getGlobalBounds().left) < 600) {

                sf::FloatRect playerBounds = body.getGlobalBounds();
                sf::FloatRect objectBounds;
                sf::FloatRect nextPlayerPos = playerBounds;
                nextPlayerPos.left += speed * direction.x * dt;
                nextPlayerPos.top += speed * direction.y * dt;


                objectBounds = o->getGlobalBounds();
                if (objectBounds.intersects(nextPlayerPos)) {


                    //Bottom
                    if (playerBounds.top < objectBounds.top &&
                        playerBounds.top + playerBounds.height < objectBounds.top + objectBounds.height &&
                        playerBounds.left < objectBounds.left + objectBounds.width - Tolerance &&
                        playerBounds.left + playerBounds.width > objectBounds.left + Tolerance) {
                        direction.y = -direction.y;
                        body.setPosition(playerBounds.left, objectBounds.top - playerBounds.height);
                        collisionsCounter++;

                    }

                        //Top
                    else if (playerBounds.top > objectBounds.top &&
                             playerBounds.top + playerBounds.height > objectBounds.top + objectBounds.height &&
                             playerBounds.left < objectBounds.left + objectBounds.width - Tolerance &&
                             playerBounds.left + playerBounds.width > objectBounds.left + Tolerance) {
                        direction.y = -direction.y;
                        body.setPosition(playerBounds.left, objectBounds.top + objectBounds.height);
                        collisionsCounter++;

                    }


                        //Right
                    else if (playerBounds.left < objectBounds.left &&
                             playerBounds.left + playerBounds.width < objectBounds.left + objectBounds.width &&
                             playerBounds.top < objectBounds.top + objectBounds.height - Tolerance &&
                             playerBounds.top + playerBounds.height > objectBounds.top + Tolerance) {
                        direction.x = -direction.x;
                        body.setPosition(objectBounds.left - playerBounds.width, playerBounds.top);
                        collisionsCounter++;

                    }

                        //Left
                    else if (playerBounds.left > objectBounds.left &&
                             playerBounds.left + playerBounds.width > objectBounds.left + objectBounds.width &&
                             playerBounds.top < objectBounds.top + objectBounds.height - Tolerance &&
                             playerBounds.top + playerBounds.height > objectBounds.top + Tolerance) {
                        direction.x = -direction.x;
                        body.setPosition(objectBounds.left + objectBounds.width, playerBounds.top);
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
    if ((collisionsCounter >= maxCollisions) or collided) return true;
    else return false;
}

