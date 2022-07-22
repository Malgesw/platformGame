//
// Created by seren on 19/07/2022.
//

#ifndef LEVELMAPSTATE_H
#define LEVELMAPSTATE_H
#include <SFML/Graphics.hpp>
#include "LevelTile.h"
#include <vector>
#include "Item.h"


class TileMap {
private:
    void setTile();
    void setInipos();
    std::map< std:: string, Item*> items;
public:
    std::vector< std:: vector<LevelTile*>> tiles;
    int gridLength;
    int gridWidth;
    sf::Vector2i playerxy;
    sf::Vector2i exitxy;


    TileMap();
};


#endif //LEVELMAPSTATE_H
