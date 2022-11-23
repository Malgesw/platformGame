#include "Room.h"

Room::Room(const std::string& roomName,GameCharacter &mainCharacter,const std::vector<sf::Texture * > & textures ,sf::Vector2i mapSize):player(mainCharacter),mapSize(mapSize){


    dimX=240.f;
    dimY=180.f;
    initFloor(roomName);
    camera.setSize(1920.f, 1080.f);
    if(dimY* static_cast<float>(mapSize.y)<1080.f){
        camera.setSize(3*dimY* static_cast<float>(mapSize.y)/2,dimY* static_cast<float>(mapSize.y));
    }

    if(dimX* static_cast<float>(mapSize.x)<1920.f){
        camera.setSize(dimX* static_cast<float>(mapSize.x),2*dimX* static_cast<float>(mapSize.x)/3);
    }

    camera.setCenter(player.getMovement().getPosition().x+player.getMovement().getCollisions().getGlobalBounds().width/2.f,
                     player.getMovement().getPosition().y+player.getMovement().getCollisions().getGlobalBounds().height/2.f);


    }


void Room::initFloor(const std::string& roomName) {

    sf::Vector2f size(dimX, dimY);
    tiles.clear();
    doors.clear();
    std::ifstream ifs;
    std::string n;
    ifs.open("./Levels/"+roomName);

    for(int i = 0; i < mapSize.x; i++) {
        while(ifs >> n){
            numbers.push_back(n);
        }
    }

    ifs.close();

    for(int i=0;i<mapSize.y;i++){
        std::vector<std::shared_ptr<LevelTile>> row;
        for(int j=0;j<mapSize.x;j++){
            row.push_back(std::make_unique<LevelTile>(numbers[i][j], j*dimX , i*dimY,  size));
        }
        tiles.push_back(row);
    }

    for(int i=0;i<mapSize.y;i++){
        for(int j=0;j<mapSize.x;j++){
            if(tiles[i][j]->getTileType() == WALL)
                walls.push_back(tiles[i][j]);
            else if(tiles[i][j]->getTileType() == DOOR)
                doors.push_back(tiles[i][j]);
        }
    }

}

void Room::render(sf::RenderTarget &target) {

    //________________________________RENDERING MAP
    for(int i=0;i<mapSize.y;i++){
        for(int j=0;j<mapSize.x;j++){
            tiles[i][j]->render(target);
        }
    }
    //________________________________RENDERING ENEMIES
    for(auto &e : enemies){
        e->render(target);
    }

    target.setView(camera);
}

void Room::update(const float &dt, unsigned int &currentRoom,sf::RenderWindow* window) {

    //________________________________UPDATING WIEW


    //________________________________UPDATING MAP
    for (int i = 0; i < mapSize.y; i++) {
        for (int j = 0; j < mapSize.x; j++) {
            if (tiles[i][j]->isExit() &&
                tiles[i][j]->getGlobalBounds().intersects(player.getMovement().getCollisions().getGlobalBounds())) {
                if (player.getMovement().getVelocity().x >= 0.f)

                    currentRoom++;

                else
                    currentRoom--;

            }
        }
    }
    //________________________________UPDATING ENEMIES

    for (auto &e: enemies) {
        e->update(dt, walls, player.getCenter());
    }

    auto i = enemies.begin();

    while (i != enemies.end()) {
        if ((*i)->getHp() <= 0) {
            enemies.erase(i++);
        } else {
            i++;

        }
    }

}

void Room::addEnemy(std::unique_ptr<GameCharacter>& enemy) {
    enemies.push_back(std::move(enemy));
}

std::vector<AttackTarget> Room::getTargets() {
    std::vector<AttackTarget> targets;
    for(auto &e : enemies){
        targets.push_back(e->generateTarget());
    }
    return targets;
}

const sf::Vector2i &Room::getMapSize() const {
    return mapSize;
}
