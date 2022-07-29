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

public:

    explicit TileMap(sf::RenderWindow* window);
    void renderMap(sf::RenderTarget &target);

    std::vector<std::shared_ptr<LevelTile>> getWalls() const {
        return walls;
    }

private:

    std::map< std:: string, std::unique_ptr<Item>> items;
    std::vector< std:: vector<std::shared_ptr<LevelTile>>> tiles;
    std::vector<std::shared_ptr<LevelTile>> walls;
    int gridLength;
    int gridWidth;
    sf::Vector2i playerxy;
    sf::Vector2i exitxy;

    void setTile(sf::RenderWindow* window);
    void setInipos();

};


#endif //TILEMAP_H
