//
// Created by alessio on 06/03/23.
//

#ifndef PLATFORMGAME_USEFULFUNCTIONS_H
#define PLATFORMGAME_USEFULFUNCTIONS_H

#include "headers.h"

float distance(sf::Vector2f a,sf::Vector2f b){
    return sqrt(pow(a.x-b.x,2)+ pow(a.y-b.y,2));
}

sf::Vector2f direction(sf::Vector2f start, sf::Vector2f end){
    float dis = distance(start,end);
    return (end-start)/dis;
}

#endif //PLATFORMGAME_USEFULFUNCTIONS_H
