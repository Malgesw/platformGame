//
// Created by alessio on 06/03/23.
//

#ifndef PLATFORMGAME_NOATTACK_H
#define PLATFORMGAME_NOATTACK_H

#include "Attack.h"

class NoAttack : public Attack {
public:
    NoAttack();


    void update(const float &dt, sf::Vector2f centerPosition, bool orientation,
                const std::vector<std::shared_ptr<LevelTile>> &walls) override {};

    void render(sf::RenderTarget &target) override {};

    bool hit() override {
        return false;
    };

    void clearRelatedObjects() override {};
private:
    void doDamage() override {};
};


#endif //PLATFORMGAME_NOATTACK_H
