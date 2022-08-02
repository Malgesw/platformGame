//
// Created by alessio on 24/07/22.
//

#include "GameCharacter.h"
#include "WalkingMovement.h"

GameCharacter::GameCharacter(sf::Vector2f startPosition, sf::Vector2f size) {

}

void GameCharacter::setMovement(Movement *newMovement) {

}

void GameCharacter::render(sf::RenderTarget &target) {


}

void GameCharacter::update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,
                           sf::RenderWindow *window) {

    if(movement->getCollisions().getPosition().y + movement->getCollisions().getSize().y < (float)(*window).getSize().y)
        movement->setVelocity( movement->getVelocity().x,movement->getVelocity().y+981.f * dt);

    movement->checkCollisions(objects);

    movement->getCollisions().move(movement->getVelocity()*dt);

    //Collisions
    if(movement->getCollisions().getPosition().y + movement->getCollisions().getSize().y >= 600.f) {
        movement->getCollisions().setPosition(movement->getCollisions().getPosition().x, 600.f - movement->getCollisions().getSize().y);
        if(movement->getTypeOfMovement()=='W') {
            dynamic_cast<WalkingMovement *>(movement)->setJump(true);
        }
    }

    if(movement->getCollisions().getPosition().x < 0.f)
        movement->getCollisions().setPosition(0, movement->getCollisions().getPosition().y);

    if(movement->getCollisions().getPosition().x + movement->getCollisions().getSize().x >= 800.f)
        movement->getCollisions().setPosition(800.f - movement->getCollisions().getSize().x, movement->getCollisions().getPosition().y);

    if(movement->getCollisions().getGlobalBounds().top < 0.f)
        movement->getCollisions().setPosition(movement->getCollisions().getGlobalBounds().left, 0.f);
}

Movement *GameCharacter::getMovement() const {
    return movement;
}
