//
// Created by seren on 19/07/2022.
//

#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>
#include "LevelTile.h"
#include "GameCharacter.h"
#include "headers.h"
#include "Item.h"
#include "Room.h"

class TileMap {

public:

    explicit TileMap(sf::RenderWindow* window);
    void render(sf::RenderTarget &target);
    void addEnemy(std::shared_ptr<GameCharacter>& enemy, std::string& id);
    void removeEnemy(std::string& id);
    void update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,
                sf::RenderWindow* window, sf::Vector2f mainCharacterPos,GameCharacter &player);
    void renderEnemies(sf::RenderTarget &target);


    const std::vector<std::shared_ptr<LevelTile>>& getWalls() const {
        return rooms[currentRoom]->getWalls();
    }

    unsigned int getCurrentRoom() const {
        return currentRoom;
    }

    const std::unique_ptr<Room> &getRoom() const {
        return rooms[currentRoom];
    }

private:
    std::vector<std::unique_ptr<Room>> rooms;
    unsigned int currentRoom;

    void addRoom(const std::string& roomName);

};


#endif //TILEMAP_H
