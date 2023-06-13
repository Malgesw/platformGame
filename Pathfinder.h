#ifndef PLATFORMGAME_PATHFINDER_H
#define PLATFORMGAME_PATHFINDER_H

#include "AStar.h"
#include "headers.h"
#include "LevelTile.h"

class Pathfinder: public AStar::Generator{

public:

    Pathfinder( const std::vector<std::shared_ptr<LevelTile>> &walls, sf::Vector2f size, float time, sf::Vector2f source, sf::Vector2f target, float deltatime);

    sf::Vector2f getMovement( sf::Vector2f end, sf::Vector2f currentPosition, float deltatime);

    std::vector<AStar::Vec2i>& getPath(){
        return path;
    }

private:

    sf::Vector2f currentDestination;
    int currentIndex;
    sf::Vector2f endPosition;
    std::vector<AStar::Vec2i> path;
    sf::Vector2f currentPosition;
    float updateTime;
    sf::Clock clock;
    float deltaTime;
    sf::Vector2f tileSize;
    bool checkPath=true;

    void updatePath();
    void updateCurrentTarget();
    static sf::Vector2f tilesToPixels(AStar::Vec2i tilePos,sf::Vector2f tileSize);
    static AStar::Vec2i pixelToTiles(sf::Vector2f pixelPos ,sf::Vector2f tileSize);

};


#endif //PLATFORMGAME_PATHFINDER_H
