#include "TileMap.h"

TileMap::TileMap() {

    addRoom("room1.ini");
    addRoom("room2.ini");
    addRoom("room3.ini");

    currentRoom = 0;

}

void TileMap::update(GameCharacter &player) {

    unsigned int room = currentRoom;
    rooms[currentRoom]->update(player, currentRoom);
    std::vector<std::shared_ptr<LevelTile>> doors = rooms[currentRoom]->getDoors();

    if(currentRoom < room){
        player.getMovement()->getCollisions().setPosition(doors[doors.size()-1]->getPosition().x - rooms[currentRoom]->getDimX(), doors[doors.size()-1]->getPosition().y);
    }
    else if(currentRoom > room && currentRoom < 3){
        player.getMovement()->getCollisions().setPosition(doors[0]->getPosition().x + rooms[currentRoom]->getDimX(), doors[0]->getPosition().y);
    }

}

void TileMap::render(sf::RenderTarget &target) {

    rooms[currentRoom]->render(target);

}

void TileMap::addRoom(const std::string& roomName) {

    rooms.push_back(std::make_unique<Room>(roomName));

}
