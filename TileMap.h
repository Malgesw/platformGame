//
// Created by seren on 19/07/2022.
//

#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>
#include "LevelTile.h"
#include "GameCharacter.h"
#include <vector>
#include <list>
#include "Item.h"



class TileMap {

public:

    explicit TileMap(sf::RenderWindow* window);
    void renderMap(sf::RenderTarget &target);
    void addEnemy(std::shared_ptr<GameCharacter>& enemy, std::string& id);
    void removeEnemy(std::string& id);
    void update(const float &dt, const std::vector<std::shared_ptr<LevelTile>>& objects, sf::RenderWindow *window);
    void renderEnemies(sf::RenderTarget &target);


    std::vector<std::shared_ptr<LevelTile>> getWalls() const {
        return walls;
    }



private:

    std::map< std:: string, std::unique_ptr<Item>> items;
    std::vector< std:: vector<std::shared_ptr<LevelTile>>> tiles;
    std::vector<std::shared_ptr<LevelTile>> walls;
    std::map<std:: string, std::shared_ptr<GameCharacter>> enemies;

    int gridLength;
    int gridWidth;
    sf::Vector2i playerxy;
    sf::Vector2i exitxy;

    void setTile(sf::RenderWindow* window);
    void setInipos();

};


#endif //TILEMAP_H
