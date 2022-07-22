//
// Created by seren on 19/07/2022.
//

#include "TileMap.h"
void TileMap::setInipos() {
    //player and exit update ini pos-temporary arbitrary coordinates and subject to change
    exitxy = sf::Vector2i(1,0);
    playerxy = sf::Vector2i(gridLength-1,gridLength-1);
}
TileMap::TileMap() {
    gridLength = 8;
    gridWidth = 8;
    setTile();
}

void TileMap::setTile() {
    sf::Vector2f size(50.f,50.f);
    tiles.clear();
    std::vector<LevelTile*> Row1;
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 0 , 0, false, false, size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/door.png", 50 , 0, true, true, size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 100 , 0, false,false, size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 150 , 0, false, false,size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 200, 0, false, false, size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 250 , 0, false, false, size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 300 , 0, false, false, size));
    Row1.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 350 , 0, false, false, size));
    tiles.push_back(Row1);

    std::vector<LevelTile*> Row2;
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 0 , 50, false, false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 50 , 50, true, false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 100 , 50, true,false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 150 , 50, true, false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 200, 50, true, false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 250 , 50, true, false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg",300, 50, true, false, size));
    Row2.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg",350 , 50, true, false, size));
    tiles.push_back(Row2);

    std::vector<LevelTile*> Row3;
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 0 , 100, true, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 50 , 100, true, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 100 , 100, false, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 150 , 100, true, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 200 , 100, true, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 250 , 100, false, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 300 , 100, false, false, size));
    Row3.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png",350 , 100, false, false, size));
    tiles.push_back(Row3);

    std::vector<LevelTile*> Row4;
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 0 , 150, false, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 50 , 150, true, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 100 , 150, false, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 150 , 150, true, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 200 , 150, true, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 250 , 150, true, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 300 , 150, false, false, size));
    Row4.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png",350 , 150, false, false, size));
    tiles.push_back(Row4);

    std::vector<LevelTile*> Row5;
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 0 , 200, false, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 50 , 200, true, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 100 , 200, true, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 150 , 200, true, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 200 , 200, false, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 250 , 200, false, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 300 , 200, false, false, size));
    Row5.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 350 , 200, false, false, size));
    tiles.push_back(Row5);

    std::vector<LevelTile*> Row6;
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 0 , 250, false, false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 50 , 250, false, false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 100 , 250, false, false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 150 , 250, true, false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 200 , 250, true, false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 250 , 250, false,false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 300 , 250,true, false, size));
    Row6.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg",350, 250,true, false, size));
    tiles.push_back(Row6);

    std::vector<LevelTile*> Row7;
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 0 , 300, true, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 50 , 300, true, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 100 , 300, false, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 150 , 300, true, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 200 , 300, true, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 250 , 300, true, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 300 , 300, true, false, size));
    Row7.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 350 , 300, true, false, size));
    tiles.push_back(Row7);

    std::vector<LevelTile*> Row8;
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 0 , 350, false, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 50 , 350, false, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 100 , 350, false, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 150 , 350, true, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/wall.png", 200 , 350, false, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 250 , 350, true, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 300 , 350, true, false, size));
    Row8.push_back(new LevelTile("C:/Users/seren/OneDrive/Documenti/projects/map_attempt/images/Ground.jpg", 350 , 350, true, false, size));
    tiles.push_back(Row8);

}






