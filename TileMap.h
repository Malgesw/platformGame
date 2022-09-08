#ifndef TILEMAP_H
#define TILEMAP_H
#include "Room.h"
#include "GameCharacter.h"



class TileMap {

public:

    explicit TileMap(sf::RenderWindow *window);

    void update(const sf::RectangleShape &playerBody);
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

    void addRoom(sf::RenderWindow *window, const std::string& roomName);





};


#endif //TILEMAP_H
