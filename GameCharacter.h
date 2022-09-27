//
// Created by alessio on 24/07/22.
//

#ifndef PLATFORMGAME_GAMECHARACTER_H
#define PLATFORMGAME_GAMECHARACTER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <utility>
#include "Movement.h"
#include "Attack.h"
#include "AttackTarget.h"
#include "Animation.h"

class GameCharacter {

public:
    GameCharacter(int healthPoints, int mana);
    void setMovement(std::unique_ptr<Movement> newMovement);
    void setAnimation(std::unique_ptr<Animation> animation);
    void setAttack(std::unique_ptr<Attack> attack);
    void render(sf::RenderTarget &target);
    void update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,sf::RenderWindow* window, sf::Vector2f mainCharacterPos);
    Movement& getMovement();
    Attack& getAttack();
    int getHp() const;
    void setHp(int hp);
    int getEnergy() const;
    void setEnergy(int energy);
    AttackTarget generateTarget();

    bool isFacingRight() const;
    sf::Vector2f getCenter(){
        return {movement->getPosition().x+movement->getCollisions().getGlobalBounds().width/2.f,
                movement->getPosition().y+ movement->getCollisions().getGlobalBounds().height/2.f};
    }


private:


    void die();
    int hp;
    int energy;
    std::unique_ptr<Movement> movement;
    std::unique_ptr<Attack> attack;
    std::unique_ptr<Animation> animation;


};


#endif //PLATFORMGAME_GAMECHARACTER_H
