//
// Created by alessio on 01/09/22.
//

#ifndef PLATFORMGAME_PATHFINDER_H
#define PLATFORMGAME_PATHFINDER_H


#include "AStar.h"
#include <cmath>


class Pathfinder: public AStar::Generator{

public:

    Pathfinder(const std::vector<sf::Vector2i> &walls, sf::Vector2f size, float time, sf::Vector2f source, sf::Vector2f target, float deltatime);

    sf::Vector2f getMovement( sf::Vector2f end, sf::Vector2f currentPosition, float deltatime);

    std::vector<AStar::Vec2i>& getPath(){
        return path;
    }

private:

    sf::Vector2f stepEndPosition;
    sf::Vector2f stepStartPosition;
    int currentIndex;
    sf::Vector2f endPosition;
    std::vector<AStar::Vec2i> path;
    sf::Vector2f currentPosition;



    float updateTime;
    sf::Clock clock;
    float deltaTime;

    void updatePath();
    void updateCurrentTarget();
    static sf::Vector2f tilesToPixels(AStar::Vec2i tilePos);
    static AStar::Vec2i pixelToTiles(sf::Vector2f pixelPos);





};


#endif //PLATFORMGAME_PATHFINDER_H
