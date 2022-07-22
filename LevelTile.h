//
// Created by seren on 19/07/2022.
//

#ifndef LEVELTILE_H
#define LEVELTILE_H
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>


class LevelTile {
private:
    sf::Vector2f pos;

public:
    bool setupSprite(std:: string);
    LevelTile(std::string, float, float, bool, bool,sf::Vector2f);
    bool isitViable();
    bool isViable;
    bool isExit;
    sf::Texture texture;
   // sf::Sprite sprite;
   sf::RectangleShape body;
   const sf::FloatRect getGlobalBounds() const;
};


#endif //LEVELTILE_H
