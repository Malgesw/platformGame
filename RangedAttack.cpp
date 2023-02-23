//
// Created by alessio on 01/12/22.
//

#include "RangedAttack.h"


RangedAttack::RangedAttack(sf::Vector2f newBulletSize,float newBulletSpeed, float attackSpeed, int hitDamage, float newKnockback) :
Attack(sf::Vector2f (50.f,50.f), attackSpeed,hitDamage,newKnockback),bulletSize(newBulletSize),bulletSpeed(newBulletSpeed) {

    bullets.emplace_back(bulletSize,bulletSpeed,damage,knockback);
    bullets.emplace_back(bulletSize,bulletSpeed,damage,knockback);
    bullets.emplace_back(bulletSize,bulletSpeed,damage,knockback);
}

void RangedAttack::hit() {

    if (cooldown.getElapsedTime().asSeconds()>attackSpeed) {
        cooldown.restart();
        auto i = bullets.begin();
        while (i != bullets.end() and (*i).isActive()) i++;
        if (i != bullets.end()) (*i).shoot(nextBulletStartPosition, nextBulletDirection);
        bullets.emplace_back(bulletSize, bulletSpeed, damage, knockback);
    }
}


void RangedAttack::update(const float &dt, sf::Vector2f centerPosition, bool facingRight,const std::vector<std::shared_ptr<LevelTile>> &walls) {

    hitBox.setPosition(facingRight?centerPosition.x-hitBox.getSize().x/2-attackoffset:centerPosition.x-hitBox.getSize().x/2+attackoffset,
                       centerPosition.y-hitBox.getSize().y/2);


    for(auto &b : bullets){

        auto i=b.update(dt,targets,walls);
        if (i!=targets.end()){
            targets.erase(i);
        }
    }

    auto j=bullets.begin();
    while (j!=bullets.end()){
        if((*j).isCollided())
            bullets.erase(j++);
        else
            j++;
    }

    nextBulletDirection=sf::Vector2f(facingRight?1.f:-1.f,0.f);
    nextBulletStartPosition=centerPosition;

}

void RangedAttack::render(sf::RenderTarget &target) {

    for(auto &b : bullets){

        b.render(target);
    }
}

