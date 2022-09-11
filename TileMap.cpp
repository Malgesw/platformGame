#include "TileMap.h"

TileMap::TileMap() {

    addRoom("room1.ini");
    addRoom("room2.ini");
    addRoom("room3.ini");

    currentRoom = 0;

}

void TileMap::update(GameCharacter &player) {

    rooms[currentRoom]->update(player, currentRoom);

}

void TileMap::render(sf::RenderTarget &target) {

    rooms[currentRoom]->render(target);

}

void TileMap::addRoom(const std::string& roomName) {

    rooms.push_back(std::make_unique<Room>(roomName));

}
