#ifndef LEVELTILE_H
#define LEVELTILE_H
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "headers.h"

enum TILES{GROUND, WALL, DOOR};

class LevelTile {

public:

    LevelTile(char tile, float x, float y, sf::Vector2f size);

    bool setupSprite(char tile);
    void render(sf::RenderTarget &target);
    bool isExit() const;

    sf::FloatRect getGlobalBounds() const;
    unsigned short getTileType() const{
        return tileType;
    }

private:

    sf::Texture texture;
    sf::RectangleShape body;
    bool exit;
    unsigned short tileType;

};


#endif //LEVELTILE_H
