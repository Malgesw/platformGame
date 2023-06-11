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


    if (checkPath){
        updatePath();
        clock.restart();
        checkPath=false;
    }

    sf::Vector2f movement;
    movement.x= (currentDestination.x - currentPosition.x);
    movement.y= (currentDestination.y - currentPosition.y);

    if(std::abs(currentPosition.x - currentDestination.x) < 1.f && std::abs(currentPosition.y - currentDestination.y) < 1.f) {

        if(clock.getElapsedTime().asSeconds()>updateTime){

            updatePath();
            clock.restart();
        }
        currentDestination = tilesToPixels(path[currentIndex],tileSize);
        updateCurrentTarget();
    }
    if (movement.x<500.f && movement.y <500.f&&path.size()<10) {
        return movement;
    }

    else {
        if(clock.getElapsedTime().asSeconds()>updateTime) {
            checkPath = true;
            clock.restart();
        }
        return {0, 0};
    }
}


void Pathfinder::updatePath(){

    path = findPath({pixelToTiles(currentPosition,tileSize).x, pixelToTiles(currentPosition,tileSize).y},
                    {pixelToTiles(endPosition,tileSize).x,pixelToTiles(endPosition,tileSize).y});
    std::reverse(path.begin(),path.end());
    currentDestination= tilesToPixels(path[0],tileSize);
    currentIndex=1;
}

void Pathfinder::updateCurrentTarget(){

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

