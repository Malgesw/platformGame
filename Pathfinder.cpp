//
// Created by alessio on 01/09/22.
//

#include "Pathfinder.h"





Pathfinder::Pathfinder(const std::vector<std::shared_ptr<LevelTile>> &walls, sf::Vector2f size, float time, sf::Vector2f source, sf::Vector2f target, float deltatime) :
        updateTime(time),currentIndex(0), endPosition(target), currentPosition(source), deltaTime(deltatime),tileSize(size) {




    for(auto &w:walls){

        AStar::Vec2i tmp= pixelToTiles(sf::Vector2f (w->getGlobalBounds().left,w->getGlobalBounds().top),tileSize);
        addCollision({tmp.x,tmp.y},tileSize);
        clock.restart();
    }
    updatePath();
}



sf::Vector2f Pathfinder::getMovement(sf::Vector2f end, sf::Vector2f position,float deltatime){

    endPosition=sf::Vector2f (end.x,end.y);
    currentPosition=sf::Vector2f (position.x,position.y);
    deltaTime=deltatime;

    if (firstCall){
        updatePath();
        clock.restart();
        firstCall=false;
    }



    sf::Vector2f movement;
    //std::cout<<"target is "<<stepEndPosition.x<<"  "<<stepEndPosition.y<<std::endl;
    //std::cout<<"position is " <<currentPosition.x<<"  "<<currentPosition.y<<std::endl;
    movement.x= (stepStartPosition.x - currentPosition.x);
    movement.y= (stepStartPosition.y - currentPosition.y);
    //std::cout<<"movement is " <<movement.x<<"  "<<movement.y<<std::endl;

    if(std::abs(currentPosition.x - stepStartPosition.x) < 1.f && std::abs(currentPosition.y - stepStartPosition.y) < 1.f) {

        if(clock.getElapsedTime().asSeconds()>updateTime){

            //std::cout<<"clock restarted"<<std::endl;

            updatePath();
            clock.restart();
        }


        stepEndPosition= tilesToPixels(path[currentIndex],tileSize);
        stepStartPosition = tilesToPixels(path[currentIndex],tileSize);
        updateCurrentTarget();
        //std::cout << "StepStartPosition : " << stepStartPosition.x << ", " << stepStartPosition.y << std::endl;
        //std::cout << "StepEndPosition : " << stepEndPosition.x << ", " << stepEndPosition.y << std::endl;
    }
    if (movement.x<500.f && movement.y <500.f&&path.size()<12) {
        return movement;
    }

    else {
        firstCall=true;
        return {0, 0};
    }
}


void Pathfinder::updatePath(){


    path = findPath({pixelToTiles(currentPosition,tileSize).x, pixelToTiles(currentPosition,tileSize).y},{pixelToTiles(endPosition,tileSize).x,
                                                                                        pixelToTiles(endPosition,tileSize).y});
    std::reverse(path.begin(),path.end());

    /*for( auto &step :path){
        std::cout<<step.x<<"  "<<step.y<<std::endl;
    std::cout<<"path ended"<<std::endl;
     */
    stepStartPosition= tilesToPixels(path[0],tileSize);
    stepEndPosition= tilesToPixels(path[1],tileSize);
    //std::cout<<stepEndPosition.x<<"   "<<stepEndPosition.y<<std::endl;
    currentIndex=1;

}

void Pathfinder::updateCurrentTarget(){


    //std::cout<<"current index is  "<<currentIndex<<std::endl;
    if(currentIndex<path.size()) {
        currentIndex++;
    }
    else {
        updatePath();
    }

}

 sf::Vector2f Pathfinder::tilesToPixels(AStar::Vec2i tilePos,sf::Vector2f tileSize) {
    float x,y;
    x= static_cast<float>(tilePos.x)*tileSize.x+tileSize.x/2;
    y= static_cast<float>(tilePos.y)*tileSize.y+tileSize.y/2;

    return {x,y};
}

 AStar::Vec2i Pathfinder::pixelToTiles(sf::Vector2f pixelPos ,sf::Vector2f tileSize) {
    int x,y;
    x=static_cast<int>((pixelPos.x/tileSize.x));
    y=static_cast<int>((pixelPos.y/tileSize.y));
    return {x,y};
}

