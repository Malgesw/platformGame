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
    void render(sf::RenderTarget &target);
    void update(const float &dt, const std::vector<std::shared_ptr<LevelTile>>& objects, sf::RenderWindow *window);


private:

    Movement* movement;

public:
    Movement *getMovement() const;
};


#endif //PLATFORMGAME_GAMECHARACTER_H
