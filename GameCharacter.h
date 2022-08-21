//
// Created by alessio on 24/07/22.
//

#ifndef PLATFORMGAME_GAMECHARACTER_H
#define PLATFORMGAME_GAMECHARACTER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "Movement.h"
#include "Attack.h"

class GameCharacter {

public:
    GameCharacter(sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>>& walls, int healthPoints, int mana);
    void setMovement(std::shared_ptr<Movement>& newMovement);
    void render(sf::RenderTarget &target);
    void update(const float &dt, const std::vector<std::shared_ptr<LevelTile>>& objects, sf::RenderWindow *window);
    std::shared_ptr<Movement> getMovement() const;
    int getHp() const;
    void setHp(int hp);
    int getEnergy() const;
    void setEnergy(int energy);

private:

    void die();
    int hp;
    int energy;

    std::shared_ptr<Movement> movement;
    std::shared_ptr<Attack> attack;
public:
    const std::shared_ptr<Attack> &getAttack() const;

    void setAttack(const std::shared_ptr<Attack> &attack);

};


#endif //PLATFORMGAME_GAMECHARACTER_H
