//
// Created by alessio on 26/07/22.
//

#include "FlyingMovement.h"



FlyingMovement::FlyingMovement(float velocity, sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>>& walls) : Movement(velocity,
                                                                                                         startPosition,
                                                                                                         size,'F',walls) {

}

void FlyingMovement::moveUp() {
collisionBox.move(0,speed*dt*-1.f);
}

void FlyingMovement::moveDown() {
    collisionBox.move(0,speed*dt);
}
