#ifndef LEVELTILE_H
#define LEVELTILE_H
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "headers.h"

enum TILES {
    GROUND = 0,
    WALL = 1,
    DOOR = 2,
    WALL2 = 3,
    WALL3 = 4,
    BUMPDX = 5,
    SPIKEDX = 6,
    WALL4 = 7,
    BUMPSX = 8,
    SPIKESX = 9,
    WALLOUT_VERT1 = 10,
    WALLOUT_VERT2 = 11,
    WALLOUT_HOR = 12,
    INT_UL = 13,
    INT_OUT_NE = 14,
    INT_OUT_NW = 15,
    DEC_PODUP = 16,
    DEC_PODDOWN = 17,
    INT_UR = 18,
    WALL_HOR = 19,
    INT_OUT_SE = 20,
    INT_OUT_SW = 21,
    BG = 22,
    ANGLE_NW = 23,
    ANGLE_NE = 24,
    ANGLE_SW = 25,
    ANGLE_SE = 26,
    INT_UPTOLEFT = 27,
    WALL_OUT_FLOOR = 28,
    BLACK_STONE = 29

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
