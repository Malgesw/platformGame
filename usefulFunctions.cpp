//
// Created by alessio on 07/03/23.
//
#include "usefulFunctions.h"

float findDistance(sf::Vector2f a, sf::Vector2f b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

sf::Vector2f findDirection(sf::Vector2f start, sf::Vector2f end) {
    float dis = findDistance(start, end);
    return (end - start) / dis;
}