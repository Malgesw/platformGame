#ifndef LEVELTILE_H
#define LEVELTILE_H
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "headers.h"

enum TILES {
    GROUND = 0, WALL = 1, DOOR = 2, WALL2 = 3, WALL3 = 4, BUMPDX = 5, SPIKEDX = 6, WALL4 = 7, BUMPSX = 8, SPIKESX = 9
};

class LevelTile {

public:

    LevelTile(sf::Texture* text, float x, float y, sf::Vector2f size, unsigned short tiletype);

    //bool setupSprite(char tile);
    void render(sf::RenderTarget &target);
    bool isExit() const;

    sf::FloatRect getGlobalBounds() const;
    unsigned short getTileType() const{
        return tileType;
    }

    sf::Vector2f getPosition() const{
        return body.getPosition();
    }

private:

    sf::Texture texture;
    sf::RectangleShape body;
    bool exit;
    unsigned short tileType;

};


#endif //LEVELTILE_H
