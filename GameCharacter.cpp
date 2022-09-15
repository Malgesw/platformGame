//
// Created by alessio on 24/07/22.
//

#include "GameCharacter.h"

#include "WalkingMovement.h"
#
#include "FlyingMovement.h"

GameCharacter::GameCharacter(sf::Vector2f startPosition, sf::Vector2f size, int healthPoints, int mana)
:hp(healthPoints),energy(mana)
{
//___________________________________________DEFAULT PARAMETERS
movement= std::make_shared<WalkingMovement>(80,startPosition,size,200);
attack= std::make_shared<Attack>(size*2.5f,0.5f,40.f,0.5f);
}

void GameCharacter::setMovement(std::shared_ptr<Movement>& newMovement) {
    movement=newMovement;
}

void GameCharacter::setAttack( std::shared_ptr<Attack> &newAttack) {
    attack = newAttack;
}


void GameCharacter::render(sf::RenderTarget &target) {

target.draw(movement->getCollisions());
}

void GameCharacter::update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,
                           sf::RenderWindow* window, sf::Vector2f mainCharacterPos) {

    sf::Vector2f collisionboxCenter(movement->getCollisions().getPosition().x+movement->getCollisions().getSize().x/2,
                                    movement->getCollisions().getPosition().y+movement->getCollisions().getSize().y/2);

    movement->update(window,dt,mainCharacterPos);
    attack->update(collisionboxCenter);

}

std::shared_ptr<Movement> GameCharacter::getMovement() const {
    return movement;
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

const std::shared_ptr<Attack> &GameCharacter::getAttack() const {
    return attack;
}


AttackTarget GameCharacter::generateTarget() {

    return AttackTarget(movement->getCollisions(),attack->getHitBox());
}
