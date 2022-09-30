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
    if (newMovement== nullptr) throw std::runtime_error("Movement component not valid");
    movement = std::move(newMovement);
}


void GameCharacter::setAttack( std::unique_ptr<Attack> newAttack) {
    if (newAttack== nullptr) throw std::runtime_error("Attack component not valid");
    attack = std::move(newAttack);
}

void GameCharacter::setAnimation(std::unique_ptr<Animation> newAnimation) {
    if (newAnimation== nullptr) throw std::runtime_error("Animation component not valid");
    animation = std::move(newAnimation);
}


void GameCharacter::render(sf::RenderTarget &target) {


    target.draw(attack->getHitBox());
    //target.draw(movement->getCollisions());
    animation->render(target);


}

void GameCharacter::update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,
                           sf::RenderWindow* window, sf::Vector2f mainCharacterPos) {

    if(movement == nullptr or attack == nullptr or animation == nullptr){
        throw std::runtime_error("character's components not valid");
    }


    sf::Vector2f hitboxCenter(isFacingRight()?movement->getCollisions().getPosition().x+movement->getCollisions().getSize().x:movement->getPosition().x,
                                    movement->getCollisions().getPosition().y+movement->getCollisions().getSize().y/2);

    movement->update(window,dt,mainCharacterPos);
    attack->update(hitboxCenter,isFacingRight());


    sf::IntRect animationRect(animation->getSprite().left, animation->getSprite().top,
                              animation->getSprite().width, animation->getSprite().height);



    animation->update(*movement, dt);
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
    return animation->isFacingRight();
}



