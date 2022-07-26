//
// Created by alessio on 24/07/22.
//

#ifndef PLATFORMGAME_GAMECHARACTER_H
#define PLATFORMGAME_GAMECHARACTER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "Movement.h"

class GameCharacter {

public:
    GameCharacter(sf::Vector2f startPosition, sf::Vector2f size);
    void setMovement(Movement* newMovement);


private:


    Movement* movement;
};


#endif //PLATFORMGAME_GAMECHARACTER_H
