//
// Created by alessio on 24/07/22.
//

#include "GameCharacter.h"

#include "WalkingMovement.h"
#
#include "FlyingMovement.h"

GameCharacter::GameCharacter(sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>>& walls, int healthPoints, int mana)
:hp(healthPoints),energy(mana)
{

movement= std::make_shared<WalkingMovement>(80,startPosition,size,walls,200);
//movement= std::make_shared<FlyingMovement>(80,startPosition,size,walls);
attack= std::make_shared<Attack>();
}

void GameCharacter::setMovement(std::shared_ptr<Movement>& newMovement) {
movement=newMovement;
}

void GameCharacter::render(sf::RenderTarget &target) {

target.draw(movement->getCollisions());
}

void GameCharacter::update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,
                           sf::RenderWindow* window, sf::Vector2f mainCharacterPos) {

    movement->update(window,dt,mainCharacterPos);

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

void GameCharacter::setAttack(const std::shared_ptr<Attack> &newAttack) {
    GameCharacter::attack = newAttack;
}
