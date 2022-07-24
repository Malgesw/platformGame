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
    setTile(window);
    //setInipos();
}

void TileMap::setTile(sf::RenderWindow* window) {

    sf::Vector2f size(window->getSize().x/gridWidth,window->getSize().y/gridLength);

    tiles.clear();
    std::vector<LevelTile*> Row1;
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 0 , 0, true, false, size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/door.png", 100 , 0, true, true, size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 200 , 0, false,false, size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 300 , 0, false, false,size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 400, 0, false, false, size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 500 , 0, false, false, size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 600 , 0, false, false, size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 700 , 0, false, false, size));
    tiles.push_back(Row1);

    std::vector<LevelTile*> Row2;
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 0 , 75, false, false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 100 , 75, true, false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg",200 ,75, true,false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 300 , 75, true, false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg",400, 75, true, false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 500 ,75, true, false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg",600, 75, true, false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg",700 ,75, true, false, size));
    tiles.push_back(Row2);

    std::vector<LevelTile*> Row3;
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 0 ,150, true, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 100 ,150, true, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 200 , 150, false, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg",300 , 150, true, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 400 , 150, true, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 500 ,150, false, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 600 , 150, false, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png",700 , 150, false, false, size));
    tiles.push_back(Row3);

    std::vector<LevelTile*> Row4;
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 0 , 225, false, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 100 , 225, true, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 200 , 225, false, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 300 , 225, true, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 400 , 225, true, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 500 , 225, true, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 600 , 225, false, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png",700 , 225, false, false, size));
    tiles.push_back(Row4);

    std::vector<LevelTile*> Row5;
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 0 , 300, false, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 100 , 300, true, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 200 , 300, true, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 300 , 300, true, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 400 , 300, false, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 500 , 300, false, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 600 , 300, false, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 700 , 300, false, false, size));
    tiles.push_back(Row5);

    std::vector<LevelTile*> Row6;
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 0 , 375, false, false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 100 , 375, false, false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 200 , 375, false, false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 300 , 375, true, false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 400 , 375, true, false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 500 , 375, false,false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 600 , 375,true, false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg",700, 375,true, false, size));
    tiles.push_back(Row6);

    std::vector<LevelTile*> Row7;
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 0 , 450, true, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 100 , 450, true, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 200 , 450, false, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 300 , 450, true, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 400 , 450, true, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 500 , 450, true, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 600 , 450, true, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 700 , 450, true, false, size));
    tiles.push_back(Row7);

    std::vector<LevelTile*> Row8;
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 0 , 525, false, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 100 , 525, false, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 200 , 525, false, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 300 , 525, true, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 400 , 525, false, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 500 , 525, true, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 600 , 525, true, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 700 , 525, true, false, size));
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








