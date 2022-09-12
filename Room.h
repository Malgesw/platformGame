#ifndef PLATFORMGAME_ROOM_H
#define PLATFORMGAME_ROOM_H

#include <SFML/Graphics.hpp>
#include "LevelTile.h"
#include <vector>
#include "Item.h"
#include "GameCharacter.h"


class Room {

public:

    explicit Room(const std::string& roomName);
    void render(sf::RenderTarget &target);
    void update(GameCharacter &player, unsigned int &currentRoom);

    const std::vector<std::shared_ptr<LevelTile>>& getWalls() const {
        return walls;
    }

    float getDimX() const{
        return dimX;
    }

    float getDimY() const{
        return dimY;
    }

    const std::vector<std::shared_ptr<LevelTile>> &getDoors() const {
        return doors;
    }

private:

    std::map< std:: string, std::unique_ptr<Item>> items;
    std::vector<std::vector<std::shared_ptr<LevelTile>>> tiles;
    std::vector<std::shared_ptr<LevelTile>> walls;
    std::vector<std::shared_ptr<LevelTile>> doors;
    std::vector<std::string> numbers;
    int heightTiles;
    int widthTiles;
    float dimX;
    float dimY;


    void initFloor(const std::string& roomName);

};



#endif //PLATFORMGAME_ROOM_H
