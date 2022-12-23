//
// Created by alessio on 16/08/22.
//

#include "AutoWalking.h"

AutoWalking::AutoWalking(float movementSpeed, sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>>& walls,float jHeight,float turnTime, unsigned short * typeOfSprite):
WalkingMovement(movementSpeed,startPosition,size,jHeight,typeOfSprite),turnbackTime(turnTime) {

    collisionBox.setFillColor(sf::Color::Red);
    timeCounter.restart();

}

void AutoWalking::rest() {

    if (timeCounter.getElapsedTime().asSeconds()<(turnbackTime/2) && *typeOfSprite != ATTACKRIGHT){
        //moveRight();
    }
    else if (timeCounter.getElapsedTime().asSeconds()<turnbackTime && *typeOfSprite != ATTACKLEFT){
        //moveLeft();
    }
    else{
        timeCounter.restart();
    }
}

void AutoWalking::aggro(const float &dt, sf::Vector2f playerPosition) {

}


void AutoWalking::update(const float &deltaTime, sf::Vector2f playerPosition) {


        //std::cout<<"position is "<<collisionBox.getPosition().x<<"  "<<collisionBox.getPosition().y<<std::endl;
        rest();
        Movement::update(deltaTime, playerPosition);


}

