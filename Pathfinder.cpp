//
// Created by alessio on 01/09/22.
//

#include "Pathfinder.h"

#include <iostream>
#include <vector>


Pathfinder::Pathfinder(const std::vector<sf::Vector2i>& walls, sf::Vector2f size, float time, sf::Vector2f source, sf::Vector2f target, float deltatime) :
        updateTime(time),currentIndex(0), endPosition(target), currentPosition(source), deltaTime(deltatime) {


    for(auto &w:walls){

        addCollision({w.x,w.y},size);
        clock.restart();
    }
    updatePath();
}



sf::Vector2f Pathfinder::getMovement(sf::Vector2f end, sf::Vector2f position, float deltatime){

    endPosition=sf::Vector2f (end.x,end.y);
    currentPosition=sf::Vector2f (position.x,position.y);
    deltaTime=deltatime;

    if(clock.getElapsedTime().asSeconds()>updateTime){

        //std::cout<<"clock restarted"<<std::endl;

        updatePath();
        clock.restart();
    }
    sf::Vector2f movement;
    //std::cout<<"target is "<<stepEndPosition.x<<"  "<<stepEndPosition.y<<std::endl;
    //std::cout<<"position is " <<currentPosition.x<<"  "<<currentPosition.y<<std::endl;
    movement.x= (stepEndPosition.x - stepStartPosition.x);
    movement.y= (stepEndPosition.y - stepStartPosition.y);
    //std::cout<<"movement is " <<movement.x<<"  "<<movement.y<<std::endl;
    if(std::abs(currentPosition.x - stepEndPosition.x) < 10.f && std::abs(currentPosition.y - stepEndPosition.y) < 10.f) {

        stepEndPosition= tilesToPixels(path[currentIndex]);
        stepStartPosition = tilesToPixels(path[currentIndex-1]);
        updateCurrentTarget();
        std::cout << "StepStartPosition : " << stepStartPosition.x << ", " << stepStartPosition.y << std::endl;
        std::cout << "StepEndPosition : " << stepEndPosition.x << ", " << stepEndPosition.y << std::endl;
    }
    if (movement.x<500.f && movement.y <500.f&&path.size()>1&&path.size()<25) {
        return movement;
    }
    else
        return {0,0};
}


void Pathfinder::updatePath(){


    //std::cout<<"current position is "<<currentPosition.x<<"   "<<currentPosition.y<<std::endl;
    //std::cout<<"end position is "<<endPosition.x<<"   "<<endPosition.y<<std::endl;

    path = findPath({pixelToTiles(currentPosition).x, pixelToTiles(currentPosition).y},{pixelToTiles(endPosition).x,
                                                                                        pixelToTiles(endPosition).y});
    std::reverse(path.begin(),path.end());

    stepStartPosition= tilesToPixels(path[0]);
    stepEndPosition= tilesToPixels(path[1]);
    currentIndex=1;

}

void Pathfinder::updateCurrentTarget(){


    std::cout<<"current index is  "<<currentIndex<<std::endl;
    if(currentIndex<path.size()) {
        currentIndex++;
    }
    else {
        updatePath();
    }

}

sf::Vector2f Pathfinder::tilesToPixels(AStar::Vec2i tilePos) {
    float x,y;
    x= static_cast<float>(tilePos.x)*32+16;
    y= static_cast<float>(tilePos.y)*24+12;

    return {x,y};
}

AStar::Vec2i Pathfinder::pixelToTiles(sf::Vector2f pixelPos) {
    int x,y;
    x=static_cast<int>((pixelPos.x/32.f)+0.5f);
    y=static_cast<int>((pixelPos.y/24.f)+0.5f);
    return {x,y};
}

