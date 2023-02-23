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
    void update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects, sf::Vector2f mainCharacterPos);
    Movement& getMovement();
    Attack& getAttack();
    Animation& getAnimation();
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

    unsigned short &getSpriteType(){
        return typeOfSprite;
    }

    unsigned short *spritePointer(){
        return &typeOfSprite;
    }

    void setSpriteType(unsigned short type){
        typeOfSprite = type;
    }


private:

    int hp;
    int energy;
    std::unique_ptr<Movement> movement;
    std::unique_ptr<Attack> attack;
    std::unique_ptr<Animation> animation;
    unsigned short typeOfSprite;
    unsigned short previousTypeOfSprite;


};


#endif //PLATFORMGAME_GAMECHARACTER_H
