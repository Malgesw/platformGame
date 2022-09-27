#ifndef PLATFORMGAME_ROOM_H
#define PLATFORMGAME_ROOM_H

#include <SFML/Graphics.hpp>
#include "LevelTile.h"
#include <vector>
#include "Item.h"
#include "GameCharacter.h"
#include "AutoWalking.h"
#include "AutoFlying.h"
#include "AutoMelee.h"


class Room {

public:


    Room(const std::string& roomName,GameCharacter &mainCharachter,const std::vector<sf::Texture * > & textures);
    void render(sf::RenderTarget &target);
    void update(const float &dt, unsigned int &currentRoom,sf::RenderWindow* window);


    void addEnemy(std::unique_ptr<GameCharacter>& enemy);


    const std::vector<std::shared_ptr<LevelTile>>& getWalls() const {
        return walls;
    }

    float getDimX() const{
        return dimX;
    }

    float getDimY() const{
        return dimY;
    }

    const std::vector<std::shared_ptr<LevelTile>> &getDoors() const {
        return doors;
    }
    std::map<std::string,std::shared_ptr<GameCharacter>> &getEnemies() {
        return enemies;
    }

    std::vector<AttackTarget> getTargets();
    sf::View &getCamera(){
        return camera;
    }

    void setCameraCenter(float x, float y){
        camera.setCenter(x, y);
    }

private:

    enum enemyType{flying=0, walking=1};
    std::map< std:: string, std::unique_ptr<Item>> items;
    std::vector<std::vector<std::shared_ptr<LevelTile>>> tiles;
    std::vector<std::shared_ptr<LevelTile>> walls;
    std::vector<std::shared_ptr<LevelTile>> doors;
    std::list<std::unique_ptr<GameCharacter>> enemies;
    std::vector<std::string> numbers;
    GameCharacter& player;
    int heightTiles;
    int widthTiles;
    float dimX;
    float dimY;
    sf::View camera;


    void initFloor(const std::string& roomName);

};



#endif //PLATFORMGAME_ROOM_H
