#include "Room.h"

Room::Room(const std::string& roomName) {
    heightTiles = 8;
    widthTiles = 8;
    dimX = 800.f/widthTiles;
    dimY = 600.f/heightTiles;
    initFloor(roomName);
}

void Room::initFloor(const std::string& roomName) {

    sf::Vector2f size(dimX, dimY);
    tiles.clear();

    std::ifstream ifs;
    std::string n;

    ifs.open("../Levels/"+roomName);

    for(int i = 0; i < heightTiles; i++) {

        while(ifs >> n){
            numbers.push_back(n);
        }

    }

    ifs.close();

    for(int i=0;i<heightTiles;i++){
        std::vector<std::shared_ptr<LevelTile>> row;
        for(int j=0;j<widthTiles;j++){
            row.push_back(std::make_unique<LevelTile>(numbers[j][i], i*dimX , j*dimY,  size));
        }
        tiles.push_back(row);
    }

    for(int i=0;i<heightTiles;i++){
        for(int j=0;j<widthTiles;j++){
            if(tiles[i][j]->getTileType() == WALL)
                walls.push_back(tiles[i][j]);
        }
    }

}


void Room::render(sf::RenderTarget &target) {
    for(int i=0;i<heightTiles;i++){
        for(int j=0;j<widthTiles;j++){
            tiles[i][j]->render(target);
        }
    }

}

void Room::update(GameCharacter &player, unsigned int &currentRoom) {

    for(int i=0;i<heightTiles;i++){
        for(int j=0;j<widthTiles;j++){

            if(tiles[i][j]->isExit() && tiles[i][j]->getGlobalBounds().intersects(player.getMovement()->getCollisions().getGlobalBounds())){
                std::cout << "exit found" << std::endl;
                currentRoom++;
                player.getMovement()->getCollisions().setPosition(0.f, 0.f);
            }

        }
    }

}
