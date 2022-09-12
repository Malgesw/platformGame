//
// Created by seren on 19/07/2022.
//

#include "TileMap.h"


void TileMap::setInipos() {
    //player and exit update ini pos-temporary arbitrary coordinates and subject to change
    exitxy = sf::Vector2i(1,0);
    playerxy = sf::Vector2i(gridLength-1,gridLength-1);
}

TileMap::TileMap(sf::RenderWindow* window) {
    gridLength = 8;
    gridWidth = 8;
    initMap(window);
    //setInipos();
}

void TileMap::initMap(sf::RenderWindow* window) {

    float dimX=800.f/gridWidth;
    tileSize.x=dimX;
    std::cout<<"dimx vale "<<dimX<<std::endl;
    float dimY=600.f/gridLength;
    tileSize.y=dimY;
    std::cout<<"dimy vale "<<dimY<<std::endl;

    sf::Vector2f size(dimX,dimY);

    tiles.clear();
    std::vector<std::shared_ptr<LevelTile>> Row1;
    Row1.push_back(std::make_unique<LevelTile>(GROUND, 0 , 0,  size));
    Row1.push_back(std::make_unique<LevelTile>(DOOR, 1*dimX , 0, size));
    Row1.push_back(std::make_unique<LevelTile>(GROUND,2*dimX , 0,  size));
    Row1.push_back(std::make_unique<LevelTile>(WALL, 3*dimX , 0, size));
    Row1.push_back(std::make_unique<LevelTile>(WALL, 4*dimX, 0, size));
    Row1.push_back(std::make_unique<LevelTile>(WALL, 5*dimX , 0, size));
    Row1.push_back(std::make_unique<LevelTile>(WALL, 6*dimX , 0, size));
    Row1.push_back(std::make_unique<LevelTile>(WALL, 7*dimX , 0, size));
    tiles.push_back(Row1);



    std::vector<std::shared_ptr<LevelTile>> Row2;
    Row2.push_back(std::make_unique<LevelTile>(WALL, 0, 1*dimY, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND, 1*dimX , 1*dimY, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND,2*dimX,1*dimY, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND, 3*dimX, 1*dimY, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND,4*dimX, 1*dimY, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND, 5*dimX,1*dimY, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND,6*dimX, 1*dimY, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND,7*dimX,1*dimY, size));
    tiles.push_back(Row2);

    std::vector<std::shared_ptr<LevelTile>> Row3;
    Row3.push_back(std::make_unique<LevelTile>(GROUND, 0 ,2*dimY, size));
    Row3.push_back(std::make_unique<LevelTile>(GROUND, 1*dimX ,2*dimY, size));
    Row3.push_back(std::make_unique<LevelTile>(GROUND, 2*dimX, 2*dimY, size));
    Row3.push_back(std::make_unique<LevelTile>(GROUND,3*dimX , 2*dimY, size));
    Row3.push_back(std::make_unique<LevelTile>(GROUND, 4*dimX, 2*dimY, size));
    Row3.push_back(std::make_unique<LevelTile>(WALL, 5*dimX,2*dimY, size));
    Row3.push_back(std::make_unique<LevelTile>(WALL, 6*dimX, 2*dimY, size));
    Row3.push_back(std::make_unique<LevelTile>(WALL,7*dimX, 2*dimY, size));
    tiles.push_back(Row3);

    std::vector<std::shared_ptr<LevelTile>> Row4;
    Row4.push_back(std::make_unique<LevelTile>(WALL, 0 , 3*dimY, size));
    Row4.push_back(std::make_unique<LevelTile>(GROUND, 1*dimX , 3*dimY, size));
    Row4.push_back(std::make_unique<LevelTile>(GROUND, 2*dimX , 3*dimY, size));
    Row4.push_back(std::make_unique<LevelTile>(GROUND, 3*dimX , 3*dimY, size));
    Row4.push_back(std::make_unique<LevelTile>(GROUND, 4*dimX , 3*dimY, size));
    Row4.push_back(std::make_unique<LevelTile>(GROUND, 5*dimX , 3*dimY, size));
    Row4.push_back(std::make_unique<LevelTile>(WALL, 6*dimX , 3*dimY, size));
    Row4.push_back(std::make_unique<LevelTile>(WALL,7*dimX, 3*dimY, size));
    tiles.push_back(Row4);

    std::vector<std::shared_ptr<LevelTile>> Row5;
    Row5.push_back(std::make_unique<LevelTile>(WALL, 0 , 4*dimY, size));
    Row5.push_back(std::make_unique<LevelTile>(GROUND, 1*dimX , 4*dimY, size));
    Row5.push_back(std::make_unique<LevelTile>(GROUND, 2*dimX , 4*dimY, size));
    Row5.push_back(std::make_unique<LevelTile>(GROUND, 3*dimX , 4*dimY, size));
    Row5.push_back(std::make_unique<LevelTile>(WALL, 4*dimX, 4*dimY, size));
    Row5.push_back(std::make_unique<LevelTile>(WALL, 5*dimX , 4*dimY, size));
    Row5.push_back(std::make_unique<LevelTile>(WALL, 6*dimX, 4*dimY, size));
    Row5.push_back(std::make_unique<LevelTile>(WALL, 7*dimX , 4*dimY, size));
    tiles.push_back(Row5);

    std::vector<std::shared_ptr<LevelTile>> Row6;
    Row6.push_back(std::make_unique<LevelTile>(WALL, 0 , 5*dimY, size));
    Row6.push_back(std::make_unique<LevelTile>(WALL, 1*dimX , 5*dimY, size));
    Row6.push_back(std::make_unique<LevelTile>(WALL, 2*dimX, 5*dimY, size));
    Row6.push_back(std::make_unique<LevelTile>(GROUND, 3*dimX , 5*dimY, size));
    Row6.push_back(std::make_unique<LevelTile>(GROUND, 4*dimX , 5*dimY, size));
    Row6.push_back(std::make_unique<LevelTile>(WALL, 5*dimX , 5*dimY, size));
    Row6.push_back(std::make_unique<LevelTile>(GROUND, 6*dimX, 5*dimY, size));
    Row6.push_back(std::make_unique<LevelTile>(GROUND,7*dimX, 5*dimY, size));
    tiles.push_back(Row6);

    std::vector<std::shared_ptr<LevelTile>> Row7;
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 0 , 6*dimY, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 1*dimX , 6*dimY, size));
    Row7.push_back(std::make_unique<LevelTile>(WALL, 2*dimX , 6*dimY, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 3*dimX , 6*dimY, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 4*dimX, 6*dimY, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 5*dimX, 6*dimY, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 6*dimX , 6*dimY, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 7*dimX, 6*dimY, size));
    tiles.push_back(Row7);

    std::vector<std::shared_ptr<LevelTile>> Row8;
    Row8.push_back(std::make_unique<LevelTile>(WALL, 0 , 7*dimY, size));
    Row8.push_back(std::make_unique<LevelTile>(WALL, 1*dimX , 7*dimY, size));
    Row8.push_back(std::make_unique<LevelTile>(WALL, 2*dimX , 7*dimY, size));
    Row8.push_back(std::make_unique<LevelTile>(GROUND, 3*dimX , 7*dimY, size));
    Row8.push_back(std::make_unique<LevelTile>(WALL, 4*dimX, 7*dimY, size));
    Row8.push_back(std::make_unique<LevelTile>(GROUND, 5*dimX , 7*dimY, size));
    Row8.push_back(std::make_unique<LevelTile>(GROUND, 6*dimX , 7*dimY, size));
    Row8.push_back(std::make_unique<LevelTile>(GROUND, 7*dimX , 7*dimY, size));
    tiles.push_back(Row8);

    for(int i=0;i<gridWidth;i++){
        for(int j=0;j<gridLength;j++){
           if(!tiles[i][j]->getViable()){
               walls.push_back(tiles[i][j]);
           }
        }
    }

}

void TileMap::renderMap(sf::RenderTarget &target) {
    for(int i=0;i<gridWidth;i++){
        for(int j=0;j<gridLength;j++){
              tiles[i][j]->render(target);
        }
    }

}

void TileMap::addEnemy(std::shared_ptr<GameCharacter>& enemy, std::string& id) {
    enemies.insert({id,enemy});
}

void TileMap::removeEnemy(std::string &id) {
    enemies.erase(id);
}

void
TileMap::update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,
                sf::RenderWindow* window, sf::Vector2f mainCharacterPos) {
for(auto &e : enemies){
    e.second->update(dt,objects,window,mainCharacterPos);
}
}

void TileMap::renderEnemies(sf::RenderTarget &target) {
    for(auto &e : enemies){
        e.second->render(target);
    }
}

const sf::Vector2f &TileMap::getTileSize() const {
    return tileSize;
}










