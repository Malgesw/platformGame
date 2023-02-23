//
// Created by alessio on 26/09/22.
//

#ifndef PLATFORMGAME_MELEEATTACK_H
#define PLATFORMGAME_MELEEATTACK_H

#include "Attack.h"
#include "LevelTile.h"


class MeleeAttack :public Attack{

public:
    MeleeAttack(sf::Vector2f size, float speed, int hitDamage, float knockback);
    void hit() override;
    void update(const float &dt, sf::Vector2f centerPosition, bool orientation,const std::vector<std::shared_ptr<LevelTile>> &walls) override;
    void render(sf::RenderTarget &target)override{};

protected:
    float attackoffset=0.f;

};


#endif //PLATFORMGAME_MELEEATTACK_H
