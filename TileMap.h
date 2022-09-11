#ifndef TILEMAP_H
#define TILEMAP_H
#include "Room.h"



class TileMap {

public:

    explicit TileMap();

    void update(GameCharacter &player);
    void render(sf::RenderTarget &target);

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
