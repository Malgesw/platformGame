//
// Created by alessio on 16/08/22.
//

#include "AutoWalking.h"

AutoWalking::AutoWalking(float movementSpeed, sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>>& walls,float jHeight,float turnTime):
WalkingMovement(movementSpeed,startPosition,size,walls,jHeight),turnbackTime(turnTime) {

    collisionBox.setFillColor(sf::Color::Red);
    timeCounter.restart();

}

void AutoWalking::wander() {

if (timeCounter.getElapsedTime().asSeconds()<(turnbackTime/2)) {
    moveRight();
    velocity.x=0;


}
else if ( timeCounter.getElapsedTime().asSeconds()<turnbackTime){
    moveLeft();
    velocity.x=0;
}
else{
    timeCounter.restart();
}
}

void AutoWalking::update(sf::RenderWindow *window, float deltaTime) {


    wander();
    Movement::update(window, deltaTime);


}
