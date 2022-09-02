//
// Created by alessio on 19/08/22.
//

#ifndef PLATFORMGAME_ATTACK_H
#define PLATFORMGAME_ATTACK_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>


class Attack {

public:
Attack();



private:
    sf::RectangleShape hitBox;
    sf::Clock cooldown;
    float attackSpeed;
    float damage;



};


#endif //PLATFORMGAME_ATTACK_H
