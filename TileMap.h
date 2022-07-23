//
// Created by seren on 19/07/2022.
//

#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>
#include "LevelTile.h"
#include <vector>
#include "Item.h"


class TileMap {
private:
    void setTile();
    void setInipos();
    std::map< std:: string, Item*> items;
    int gridLength;
    int gridWidth;

public:
    std::vector< std:: vector<LevelTile*>> tiles;
    sf::Vector2i playerxy;
    sf::Vector2i exitxy;
    void renderMap(sf::RenderTarget target);
    TileMap();
};


#endif //TILEMAP_H
