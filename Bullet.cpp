//
// Created by alessio on 29/11/22.
//

#include "Bullet.h"

Bullet::Bullet(sf::Vector2f size, sf::Vector2f startPosition, int speed, int damage, sf::Texture *texture):speed(speed),damage(damage) {

    body=sf::RectangleShape(size);
    body.setPosition(startPosition);
    body.setTexture(texture);
}

void Bullet::update(const float &dt, const std::vector<AttackTarget> &targets,
                    const std::vector<std::shared_ptr<LevelTile>> &walls) {

    if(isActive){
        for (auto &t:targets){

        }
    }


    for (auto &w:walls) {
        if (body.getGlobalBounds().intersects(w->getGlobalBounds()))
            isActive= false;
    }

}

void Bullet::render(sf::RenderTarget &target) {
    if (isActive)
        target.draw(body);
}

