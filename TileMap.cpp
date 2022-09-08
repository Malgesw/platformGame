#include "TileMap.h"

TileMap::TileMap(sf::RenderWindow *window) {

    addRoom(window, "room1.ini");
    addRoom(window, "room2.ini");
    addRoom(window, "room3.ini");

    currentRoom = 0;

}

void TileMap::update(const sf::RectangleShape &playerBody) {

    rooms[currentRoom]->update(playerBody, currentRoom);

}

void TileMap::render(sf::RenderTarget &target) {

    rooms[currentRoom]->render(target);

}

void TileMap::addRoom(sf::RenderWindow *window, const std::string& roomName) {

    rooms.push_back(std::make_unique<Room>(window, roomName));

}
