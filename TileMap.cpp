//
// Created by seren on 19/07/2022.
//

#include "TileMap.h"

TileMap::TileMap(GameCharacter& player) {

    enum enemy{flying=0,walking=1};
    textures.push_back(new sf::Texture);
    textures[flying]->loadFromFile("../images/flyingEnemySheet.png");

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
        player.getMovement().getCollisions().setPosition(doors[doors.size()-1]->getPosition().x - rooms[currentRoom]->getDimX(), doors[doors.size()-1]->getPosition().y);
    }
    else if(currentRoom > room && currentRoom < 3){
        player.getMovement().getCollisions().setPosition(doors[0]->getPosition().x + rooms[currentRoom]->getDimX(), doors[0]->getPosition().y);
    }

    //____________________VIEW COLLISIONS

    rooms[currentRoom]->setCameraCenter(player.getCenter().x, player.getCenter().y);


    //_____RIGHT
    if(rooms[currentRoom]->getCamera().getSize().x/2.f >= 16*rooms[currentRoom]->getDimX() - player.getCenter().x)
        rooms[currentRoom]->setCameraCenter(16*rooms[currentRoom]->getDimX() - rooms[currentRoom]->getCamera().getSize().x/2.f,
                                            rooms[currentRoom]->getCamera().getCenter().y);

    //_____LEFT
    if(rooms[currentRoom]->getCamera().getSize().x/2.f >= player.getCenter().x)
        rooms[currentRoom]->setCameraCenter(rooms[currentRoom]->getCamera().getSize().x/2.f,
                                            rooms[currentRoom]->getCamera().getCenter().y);

    //_____BOTTOM
    if(rooms[currentRoom]->getCamera().getSize().y/2.f >= 16*rooms[currentRoom]->getDimY() - player.getCenter().y)
        rooms[currentRoom]->setCameraCenter(rooms[currentRoom]->getCamera().getCenter().x,
                                            16*rooms[currentRoom]->getDimY() - rooms[currentRoom]->getCamera().getSize().y/2.f);

    //_____TOP
    if(rooms[currentRoom]->getCamera().getSize().y/2.f >= player.getCenter().y)
        rooms[currentRoom]->setCameraCenter(rooms[currentRoom]->getCamera().getCenter().x,
                                            rooms[currentRoom]->getCamera().getSize().y/2.f);

}

void TileMap::render(sf::RenderTarget &target) {
    rooms[currentRoom]->render(target);

}


void TileMap::addRoom(const std::string& roomName, GameCharacter &player) {

    rooms.push_back(std::make_unique<Room>(roomName,player,textures));
}

TileMap::~TileMap() {
for (auto& t: textures){
    delete t;
}
}
