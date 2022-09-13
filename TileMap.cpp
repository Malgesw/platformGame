//
// Created by seren on 19/07/2022.
//

#include "TileMap.h"

TileMap::TileMap(GameCharacter& player) {

    addRoom("room1.ini",player);
    addRoom("room2.ini",player);
    addRoom("room3.ini",player);
    currentRoom = 0;
}

void TileMap::update(const float &dt,GameCharacter &player, sf::RenderWindow *window) {

    unsigned int room = currentRoom;
    rooms[currentRoom]->update(dt,currentRoom,window);
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


void TileMap::addRoom(const std::string& roomName, GameCharacter &player) {

    rooms.push_back(std::make_unique<Room>(roomName,player));
}
