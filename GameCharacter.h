#ifndef PLATFORMGAME_GAMECHARACTER_H
#define PLATFORMGAME_GAMECHARACTER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <utility>
#include "Movement.h"
#include "Attack.h"
#include "AttackTarget.h"
#include "Animation.h"
#include "WalkingMovement.h"
#include "FlyingMovement.h"
#include "exceptions.h"
#include "Shell.h"

class GameCharacter {

public:
    GameCharacter(float healthPoints, float mana);

    void setMovement(std::unique_ptr<Movement> newMovement);

    void setAnimation(std::unique_ptr<Animation> animation);

    void setAttack(std::unique_ptr<Attack> attack);

    void render(sf::RenderTarget &target);

    void update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects, sf::Vector2f mainCharacterPos);

    /* OLD IMPLEMENTATION, USE ONLY FOR TESTING
    Movement &getMovement();

    Attack &getAttack();

    Animation &getAnimation();
    */

    float getHp() const;

    void setHp(float hp);

    float getEnergy() const;

    void setEnergy(float energy);

    AttackTarget *generateTarget();

    void moveLeft();

    void moveRight();

    void moveUp();

    void moveDown();

    void hit();

    sf::Vector2f getVelocity() const;

    void setVelocity(float x, float y);

    sf::Vector2f getPosition() const;

    void setPosition(float x, float y);

    sf::Vector2f getSize() const;

    sf::FloatRect getGlobalBounds() const;

    bool isOnGround() const;

    bool isFacingRight() const;

    bool isColliding() const;

    void addWalls(const std::vector<std::shared_ptr<LevelTile>> &newWalls);

    void clearWalls();

    void addTargets(const std::vector<AttackTarget *> &newTargets);

    void clearTargets();


    sf::Vector2f getCenter() {
        return {movement->getPosition().x + movement->getCollisions().getGlobalBounds().width / 2.f,
                movement->getPosition().y + movement->getCollisions().getGlobalBounds().height / 2.f};
    }

    unsigned short &getSpriteType() {
        return typeOfSprite;
    }

    unsigned short *spritePointer() {
        return &typeOfSprite;
    }

    void setSpriteType(unsigned short type) {
        typeOfSprite = type;
    }

    float getStartHp() const {
        return startHp;
    }

    float getStartEnergy() const {
        return startEnergy;
    }


private:

    float hp;
    float energy;
    float startHp;
    float startEnergy;
    std::unique_ptr<Movement> movement;
    std::unique_ptr<Attack> attack;
    std::unique_ptr<Animation> animation;
    std::unique_ptr<SpecialAbility> specialAbility;
    std::unique_ptr<Movement> backupMovement;
    std::unique_ptr<Attack> backupAttack;
    std::unique_ptr<Animation> backupAnimation;
    std::unique_ptr<SpecialAbility> backupSpecialAbility;
    AttackTarget selfTarget;
    unsigned short typeOfSprite;
    unsigned short previousTypeOfSprite;


};


#endif //PLATFORMGAME_GAMECHARACTER_H
