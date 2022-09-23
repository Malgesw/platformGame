//
// Created by alessio on 24/07/22.
//

#include "GameCharacter.h"
#include "WalkingMovement.h"
#include "FlyingMovement.h"

GameCharacter::GameCharacter(int healthPoints, int mana)
:hp(healthPoints),energy(mana)
{

//___________________________________________DEFAULT PARAMETERS
}

void GameCharacter::setMovement(std::unique_ptr<Movement> newMovement) {
    movement = std::move(newMovement);
}


void GameCharacter::setAttack( std::unique_ptr<Attack> newAttack) {
    attack = std::move(newAttack);
}

void GameCharacter::setAnimation(std::unique_ptr<Animation> newAnimation) {
    animation = std::move(newAnimation);
}


void GameCharacter::render(sf::RenderTarget &target) {

animation->render(target);

}

void GameCharacter::update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,
                           sf::RenderWindow* window, sf::Vector2f mainCharacterPos) {

    if(movement == nullptr or attack == nullptr or animation == nullptr){
        throw std::runtime_error("character's components not valid");
    }

    sf::Vector2f collisionboxCenter(movement->getCollisions().getPosition().x+movement->getCollisions().getSize().x/2,
                                    movement->getCollisions().getPosition().y+movement->getCollisions().getSize().y/2);

    movement->update(window,dt,mainCharacterPos);
    attack->update(collisionboxCenter);
    animation->getAnimationBox().setPosition(movement->getCollisions().getPosition() + animation->getPositionCorrection());

    int row;
    sf::IntRect animationRect(animation->getSprite().left, animation->getSprite().top,
                              animation->getSprite().width, animation->getSprite().height);

    switch (movement->getSpriteType()) {

        case IDLELEFT:
            row = 0;
            animationRect.height -= 50.f;
            //animationRect.width += 20.f;
            faceRight= false;
            break;
        case IDLERIGHT:
            row = 0;
            animationRect.height -= 50.f;
            //animationRect.width += 20.f;
            faceRight= true;
            break;
        case MOVELEFT:
            row = 1;
            animationRect.height -= 170.f;
            //animationRect.width += 200.f;
            faceRight = false;
            break;
        case MOVERIGHT:
            row = 1;
            animationRect.height -= 170.f;
            animationRect.width += 60.f;
            faceRight= true;
            break;
        case JUMPRIGHT:
            row = 2;
            animationRect.height -= 60.f;
            faceRight= true;
            break;
        case JUMPLEFT:
            row = 2;
            animationRect.height -= 60.f;
            faceRight = false;
            break;
        default:
            row = 0;
            break;

    }

    animation->update(row, dt, faceRight);
    animation->getAnimationBox().setTextureRect(animationRect);



}

Movement& GameCharacter::getMovement(){
    return *movement;
}

Attack& GameCharacter::getAttack(){
    return *attack;
}

void GameCharacter::die() {

}

int GameCharacter::getHp() const {
    return hp;
}

void GameCharacter::setHp(int healthPoints) {
    GameCharacter::hp = healthPoints;
}

int GameCharacter::getEnergy() const {
    return energy;
}

void GameCharacter::setEnergy(int mana) {
    GameCharacter::energy = mana;
}



AttackTarget GameCharacter::generateTarget() {

    return AttackTarget(&movement->getCollisions(),&attack->getHitBox(),&movement->getKnockback(),&hp);
}

bool GameCharacter::isFacingRight() const {
    return faceRight;
}

