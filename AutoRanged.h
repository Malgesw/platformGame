//
// Created by alessio on 06/03/23.
//

#ifndef PLATFORMGAME_AUTORANGED_H
#define PLATFORMGAME_AUTORANGED_H

#include"RangedAttack.h"
#include"AutoAttack.h"
#include "usefulFunctions.h"

class AutoRanged: public  RangedAttack,AutoAttack{

public:
    AutoRanged(sf::Vector2f bulletSize,float bulletSpeed, float attackSpeed, int hitDamage, float knockback, unsigned short * typeOfSprite, float ScanRange);
    void update(const float &dt, sf::Vector2f centerPosition, bool orientation,const std::vector<std::shared_ptr<LevelTile>> &walls) override;
    void render(sf::RenderTarget &target)override{};

private:
    float scanRange;
    void attackPlayer(sf::Vector2f centerPosition) override;
};


#endif //PLATFORMGAME_AUTORANGED_H
