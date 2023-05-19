#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include "LevelTile.h"
#include "GameCharacter.h"
#include "headers.h"
#include "Droid.h"
#include "Room.h"
#include "NoMovement.h"
#include "NoSpecialAbility.h"
#include "NoAttack.h"
#include "Achievement.h"
#include "GlidingMovement.h"
#include <string>

enum ItemType {
    TACO = 0, DEATHZONE = 1, SHELLDROID = 2, GLIDINGDROID = 3
};

class TileMap {

public:

    TileMap(GameCharacter &player, Achievement *achievementCounter);

    ~TileMap();

    void render(sf::RenderTarget &target);

    void update(const float &dt, GameCharacter &player, sf::RenderWindow *window);
    void spawnEnemies(GameCharacter &player);

    void placeItems(GameCharacter &player);

    void clearEnemies();

    void clearItems();
    const std::vector<std::shared_ptr<LevelTile>> &getWalls() const {
        return rooms[currentRoom]->getWalls();
    }

    std::vector<AttackTarget *> getTargets() const {
        return rooms[currentRoom]->getTargets();
    }

    unsigned int getCurrentRoom() const {
        return currentRoom;
    }
    void setCurrentRoom(unsigned int newCurrent) {
        currentRoom = newCurrent;
    }
    const std::unique_ptr<Room> &getRoom() const {
        return rooms[currentRoom];
    }

private:
    std::vector<sf::Texture*> textures;
    std::vector<sf::Texture*> tilesTextures;
    std::vector<std::unique_ptr<Room>> rooms;
    unsigned int currentRoom;
    unsigned int maxRoom = 3;
    Achievement *achievementCounter;

    void addRoom(const std::string& roomName, GameCharacter& mainCharacter,sf::Vector2i roomSize);

    void generateEnemy(int roomNumber, std::string configFile, sf::Vector2i startPosition, GameCharacter &player);

    void generateItem(int roomNumber, sf::Vector2i position, sf::Vector2f size, unsigned short int type,
                      GameCharacter &player);

};


#endif //TILEMAP_H
