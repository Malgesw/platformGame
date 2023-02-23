//
// Created by alessio on 26/09/22.
//

#ifndef PLATFORMGAME_AUTOMELEE_H
#define PLATFORMGAME_AUTOMELEE_H

#include "MeleeAttack.h"
#include"AutoAttack.h"

class AutoMelee: public MeleeAttack,AutoAttack{

public:
    AutoMelee(sf::Vector2f size, float speed, int hitDamage, float knockback);
    void update(const float &dt, sf::Vector2f centerPosition, bool facingRight,const std::vector<std::shared_ptr<LevelTile>> &walls) override;
    void render(sf::RenderTarget &target)override{};

private:
    void attackPlayer(sf::Vector2f centerPosition) override;
};


#endif //PLATFORMGAME_AUTOMELEE_H
