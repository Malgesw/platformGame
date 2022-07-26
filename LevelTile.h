//
// Created by seren on 19/07/2022.
//

#ifndef LEVELTILE_H
#define LEVELTILE_H
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "headers.h"

enum TILES{GROUND, WALL, DOOR};

class LevelTile {

public:

    LevelTile(unsigned short tile, float x, float y, sf::Vector2f size);

    bool getViable() const;
    bool setupSprite(unsigned short tile);
    void render(sf::RenderTarget &target);
    sf::FloatRect getGlobalBounds() const;

private:

    sf::Texture texture;
    sf::RectangleShape body;
    bool isViable;
    bool isExit;

};


#endif //LEVELTILE_H
