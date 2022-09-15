//
// Created by alessio on 24/07/22.
//

#ifndef PLATFORMGAME_GAMECHARACTER_H
#define PLATFORMGAME_GAMECHARACTER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "Movement.h"
#include "Attack.h"
#include "AttackTarget.h"
#include "Animation.h"

class GameCharacter {

public:
    GameCharacter(sf::Vector2f startPosition, sf::Vector2f size, int healthPoints, int mana);
    void setMovement(std::shared_ptr<Movement>& newMovement);
    void render(sf::RenderTarget &target);
    void update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,sf::RenderWindow* window, sf::Vector2f mainCharacterPos);
    std::shared_ptr<Movement> getMovement() const;
    int getHp() const;
    void setHp(int hp);
    int getEnergy() const;
    void setEnergy(int energy);
    AttackTarget generateTarget();
    const std::shared_ptr<Attack> &getAttack() const;
    void setAttack(std::shared_ptr<Attack> &attack);
    bool isFacingRight() const;


private:

    bool faceRight=true;

    void die();
    int hp;
    int energy;
    std::shared_ptr<Movement> movement;
    std::shared_ptr<Attack> attack;
    std::unique_ptr<Animation> animation;
    sf::Texture texture;


};


#endif //PLATFORMGAME_GAMECHARACTER_H
