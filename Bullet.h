#ifndef PLATFORMGAME_BULLET_H
#define PLATFORMGAME_BULLET_H

#include "headers.h"
#include "AttackTarget.h"
#include "LevelTile.h"
#include "Animation.h"


class Bullet {

public:
    Bullet(sf::Vector2f size, float speed, float damage, float knockback, sf::Texture *texture, int maxCollisions);

    virtual std::list<AttackTarget *>::const_iterator update(const float &dt, const std::list<AttackTarget *> &targets,
                                                             const std::vector<std::shared_ptr<LevelTile>> &walls);

    void render(sf::RenderTarget &target);

    void shoot(sf::Vector2f startposition, sf::Vector2f direction);

    void setDirection(sf::Vector2f newDirection);

    bool isActive() const;

    virtual bool isCollided() const;

protected:

    float speed;
    sf::Vector2f direction;
    float damage;
    float knockback;
    bool active = false;
    bool collided = false;
    sf::RectangleShape body;
    std::unique_ptr<Animation> animation;
    int maxCollisions;
    int collisionsCounter = 0;


};


#endif //PLATFORMGAME_BULLET_H
