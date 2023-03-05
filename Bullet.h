//
// Created by alessio on 29/11/22.
//

#ifndef PLATFORMGAME_BULLET_H
#define PLATFORMGAME_BULLET_H

#include "headers.h"
#include "AttackTarget.h"
#include "LevelTile.h"
#include "Animation.h"


class Bullet {

public:
    Bullet(sf::Vector2f size, int speed,  int damage, int knockback,sf::Texture* texture);

    std::list<AttackTarget>::const_iterator update(const float &dt, std::list<AttackTarget> &targets, const std::vector<std::shared_ptr<LevelTile>> &walls);

    void render(sf::RenderTarget &target);
    void shoot(sf::Vector2f startposition,sf::Vector2f direction);
    void setDirection(sf::Vector2f newDirection);
    bool isActive();
    bool isCollided();

private:
    int speed;
    sf::Vector2f direction;
    int damage;
    int knockback;
    bool active=false;
    bool collided=false;
    sf::RectangleShape body;
    std::unique_ptr<Animation> animation;


};


#endif //PLATFORMGAME_BULLET_H
