//
// Created by alessio on 29/11/22.
//

#ifndef PLATFORMGAME_BULLET_H
#define PLATFORMGAME_BULLET_H

#include "headers.h"
#include "AttackTarget.h"
#include "LevelTile.h"


class Bullet {

public:
    Bullet(sf::Vector2f size,sf::Vector2f startPosition, int speed,  int damage, sf::Texture* texture);

    void update(const float &dt, const std::vector<AttackTarget> &targets, const std::vector<std::shared_ptr<LevelTile>> &walls);
    void render(sf::RenderTarget &target);

private:
    int speed;
    int damage;
    bool isActive=true;
    sf::RectangleShape body;

};


#endif //PLATFORMGAME_BULLET_H
