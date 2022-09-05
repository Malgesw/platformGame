//
// Created by seren on 19/07/2022.
//

#include "TileMap.h"


void TileMap::setInipos() {
    exitxy = sf::Vector2i(1,0);
    playerxy = sf::Vector2i(gridLength-1,gridLength-1);
}
TileMap::TileMap(sf::RenderWindow* window) {
    gridLength = 8;
    gridWidth = 8;
    setTile(window);
}

void TileMap::setTile(sf::RenderWindow* window) {

    sf::Vector2f size(window->getSize().x/gridWidth,window->getSize().y/gridLength);

    tiles.clear();
    std::vector<std::shared_ptr<LevelTile>> Row1;
    Row1.push_back(std::make_unique<LevelTile>(GROUND, 0 , 0,  size));
    Row1.push_back(std::make_unique<LevelTile>(WALL, 100 , 0, size));
    Row1.push_back(std::make_unique<LevelTile>(WALL, 200 , 0,  size));
    Row1.push_back(std::make_unique<LevelTile>(WALL, 300 , 0, size));
    Row1.push_back(std::make_unique<LevelTile>(WALL, 400, 0, size));
    Row1.push_back(std::make_unique<LevelTile>(WALL, 500 , 0, size));
    Row1.push_back(std::make_unique<LevelTile>(WALL, 600 , 0, size));
    Row1.push_back(std::make_unique<LevelTile>(WALL, 700 , 0, size));
    tiles.push_back(Row1);



    std::vector<std::shared_ptr<LevelTile>> Row2;
    Row2.push_back(std::make_unique<LevelTile>(GROUND, 0 , 75, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND, 100 , 75, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND,200 ,75, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND, 300 , 75, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND,400, 75, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND, 500 ,75, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND,600, 75, size));
    Row2.push_back(std::make_unique<LevelTile>(GROUND,700 ,75, size));
    tiles.push_back(Row2);

    std::vector<std::shared_ptr<LevelTile>> Row3;
    Row3.push_back(std::make_unique<LevelTile>(GROUND, 0 ,150, size));
    Row3.push_back(std::make_unique<LevelTile>(GROUND, 100 ,150, size));
    Row3.push_back(std::make_unique<LevelTile>(GROUND, 200 , 150, size));
    Row3.push_back(std::make_unique<LevelTile>(GROUND,300 , 150, size));
    Row3.push_back(std::make_unique<LevelTile>(GROUND, 400 , 150, size));
    Row3.push_back(std::make_unique<LevelTile>(WALL, 500 ,150, size));
    Row3.push_back(std::make_unique<LevelTile>(WALL, 600 , 150, size));
    Row3.push_back(std::make_unique<LevelTile>(WALL,700 , 150, size));
    tiles.push_back(Row3);

    std::vector<std::shared_ptr<LevelTile>> Row4;
    Row4.push_back(std::make_unique<LevelTile>(GROUND, 0 , 225, size));
    Row4.push_back(std::make_unique<LevelTile>(WALL, 100 , 225, size));
    Row4.push_back(std::make_unique<LevelTile>(GROUND, 200 , 225, size));
    Row4.push_back(std::make_unique<LevelTile>(GROUND, 300 , 225, size));
    Row4.push_back(std::make_unique<LevelTile>(GROUND, 400 , 225, size));
    Row4.push_back(std::make_unique<LevelTile>(GROUND, 500 , 225, size));
    Row4.push_back(std::make_unique<LevelTile>(WALL, 600 , 225, size));
    Row4.push_back(std::make_unique<LevelTile>(WALL,700 , 225, size));
    tiles.push_back(Row4);

    std::vector<std::shared_ptr<LevelTile>> Row5;
    Row5.push_back(std::make_unique<LevelTile>(WALL, 0 , 300, size));
    Row5.push_back(std::make_unique<LevelTile>(WALL, 100 , 300, size));
    Row5.push_back(std::make_unique<LevelTile>(GROUND, 200 , 300, size));
    Row5.push_back(std::make_unique<LevelTile>(GROUND, 300 , 300, size));
    Row5.push_back(std::make_unique<LevelTile>(WALL, 400 , 300, size));
    Row5.push_back(std::make_unique<LevelTile>(WALL, 500 , 300, size));
    Row5.push_back(std::make_unique<LevelTile>(WALL, 600 , 300, size));
    Row5.push_back(std::make_unique<LevelTile>(WALL, 700 , 300, size));
    tiles.push_back(Row5);

    std::vector<std::shared_ptr<LevelTile>> Row6;
    Row6.push_back(std::make_unique<LevelTile>(WALL, 0 , 375, size));
    Row6.push_back(std::make_unique<LevelTile>(WALL, 100 , 375, size));
    Row6.push_back(std::make_unique<LevelTile>(WALL, 200 , 375, size));
    Row6.push_back(std::make_unique<LevelTile>(GROUND, 300 , 375, size));
    Row6.push_back(std::make_unique<LevelTile>(GROUND, 400 , 375, size));
    Row6.push_back(std::make_unique<LevelTile>(WALL, 500 , 375, size));
    Row6.push_back(std::make_unique<LevelTile>(GROUND, 600 , 375, size));
    Row6.push_back(std::make_unique<LevelTile>(GROUND,700, 375, size));
    tiles.push_back(Row6);

    std::vector<std::shared_ptr<LevelTile>> Row7;
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 0 , 450, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 100 , 450, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 200 , 450, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 300 , 450, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 400 , 450, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 500 , 450, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 600 , 450, size));
    Row7.push_back(std::make_unique<LevelTile>(GROUND, 700 , 450, size));
    tiles.push_back(Row7);

    std::vector<std::shared_ptr<LevelTile>> Row8;
    Row8.push_back(std::make_unique<LevelTile>(WALL, 0 , 525, size));
    Row8.push_back(std::make_unique<LevelTile>(WALL, 100 , 525, size));
    Row8.push_back(std::make_unique<LevelTile>(WALL, 200 , 525, size));
    Row8.push_back(std::make_unique<LevelTile>(GROUND, 300 , 525, size));
    Row8.push_back(std::make_unique<LevelTile>(WALL, 400 , 525, size));
    Row8.push_back(std::make_unique<LevelTile>(GROUND, 500 , 525, size));
    Row8.push_back(std::make_unique<LevelTile>(GROUND, 600 , 525, size));
    Row8.push_back(std::make_unique<LevelTile>(GROUND, 700 , 525, size));
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








