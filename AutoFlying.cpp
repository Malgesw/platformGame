//
// Created by alessio on 02/09/22.
//

#include "AutoFlying.h"

AutoFlying::AutoFlying(float movementSpeed, sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>> &walls):
        FlyingMovement(movementSpeed,startPosition,size,walls){

    collisionBox.setFillColor(sf::Color::Red);
}

void AutoFlying::rest() {

}

void AutoFlying::aggro() {

}

void AutoFlying::update(sf::RenderWindow *window, float deltaTime) {


    rest();
    Movement::update(window, deltaTime);


}

