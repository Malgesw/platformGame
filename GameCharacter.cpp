//
// Created by alessio on 24/07/22.
//

#include "GameCharacter.h"
#include "WalkingMovement.h"
#include "FlyingMovement.h"

GameCharacter::GameCharacter(sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>>& walls) {

movement=new WalkingMovement(80,sf::Vector2f(1,1),sf::Vector2f(50,50),walls,200);
}

void GameCharacter::setMovement(Movement *newMovement) {

}

void GameCharacter::render(sf::RenderTarget &target) {

target.draw(movement->getCollisions());
}

void GameCharacter::update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,
                           sf::RenderWindow* window) {

    movement->update(window,dt);
}

Movement *GameCharacter::getMovement() const {
    return movement;
}
