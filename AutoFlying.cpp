//
// Created by alessio on 02/09/22.
//

#include "AutoFlying.h"

AutoFlying::AutoFlying(float movementSpeed, sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>> &walls, sf::Vector2f wallSize):
        FlyingMovement(movementSpeed,startPosition,size,walls){

    collisionBox.setFillColor(sf::Color::Red);
    pathfinder= std::make_unique<Pathfinder>(walls,wallSize, 0.5f,startPosition,startPosition,0.1f);
    pathfinder->setWorldSize(sf::Vector2f(8, 8));
    pathfinder->setHeuristic(AStar::Heuristic::manhattan);
    pathfinder->setDiagonalMovement(false);
}

void AutoFlying::rest() {

}

void AutoFlying::aggro(const float &dt, sf::Vector2f playerPosition) {

    sf::Vector2f movement= pathfinder->getMovement(playerPosition,collisionBox.getPosition(),dt);
    //std::cout<<"movement is "<<movement.x<<"  "<<movement.y<<std::endl;
    collisionBox.move(movement*dt);

}

void AutoFlying::update(sf::RenderWindow *window,const float &deltaTime, sf::Vector2f playerPosition) {



    aggro(deltaTime,playerPosition);
    Movement::update(window, deltaTime,playerPosition);


}

