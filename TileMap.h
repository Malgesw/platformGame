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
    void setTile(sf::RenderWindow* window);
    void setInipos();
    std::map< std:: string, Item*> items;
    int gridLength;
    int gridWidth;
    std::vector< std:: vector<LevelTile*>> tiles;
    sf::Vector2i playerxy;
    sf::Vector2i exitxy;
public:
     std::vector<LevelTile *> getWalls() const{
        return walls;
    }

private:
    std::vector<LevelTile*> walls;

public:

    void renderMap(sf::RenderTarget &target);
    TileMap(sf::RenderWindow* window);
};


#endif //TILEMAP_H
