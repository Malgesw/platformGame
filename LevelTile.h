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
    sf::Texture texture;
    sf::RectangleShape body;
    bool isViable;
public:
    bool getViable() const;

private:
    bool isExit;
public:
    const sf::RectangleShape &getBody() const;
    void setBody(const sf::RectangleShape &body);

public:
    bool setupSprite(std:: string);
    LevelTile(std::string, float, float, bool, bool,sf::Vector2f);

    void render(sf::RenderTarget &target);
    sf::FloatRect getGlobalBounds() const;
};


#endif //LEVELTILE_H
