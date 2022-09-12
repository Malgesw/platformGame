//
// Created by seren on 19/07/2022.
//

#include "TileMap.h"

TileMap::TileMap() {

    addRoom("room1.ini");
    addRoom("room2.ini");
    addRoom("room3.ini");

    currentRoom = 0;

}

void TileMap::update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,
                     sf::RenderWindow* window, sf::Vector2f mainCharacterPos,GameCharacter &player) {

    unsigned int room = currentRoom;
    rooms[currentRoom]->update(player, currentRoom);
    std::vector<std::shared_ptr<LevelTile>> doors = rooms[currentRoom]->getDoors();

    if(currentRoom < room){
        player.getMovement()->getCollisions().setPosition(doors[doors.size()-1]->getPosition().x - rooms[currentRoom]->getDimX(), doors[doors.size()-1]->getPosition().y);
    }
    else if(currentRoom > room && currentRoom < 3){
        player.getMovement()->getCollisions().setPosition(doors[0]->getPosition().x + rooms[currentRoom]->getDimX(), doors[0]->getPosition().y);
    }
    for(auto &e : enemies){
        e.second->update(dt,objects,window,mainCharacterPos);
    }
}

void TileMap::render(sf::RenderTarget &target) {
    rooms[currentRoom]->render(target);

}

void TileMap::addEnemy(std::shared_ptr<GameCharacter>& enemy, std::string& id) {
    enemies.insert({id,enemy});
}

void TileMap::removeEnemy(std::string &id) {
    enemies.erase(id);
}


void TileMap::renderEnemies(sf::RenderTarget &target) {
    for(auto &e : enemies){
        e.second->render(target);
    }
}



void TileMap::addRoom(const std::string& roomName) {

    rooms.push_back(std::make_unique<Room>(roomName));

}
