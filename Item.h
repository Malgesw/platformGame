//
// Created by seren on 19/07/2022.
//

#ifndef ITEM_H
#define ITEM_H
#include <SFML/Graphics.hpp>
//add animation


class Item {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f pos;
    bool active;
public:
    void activate();
    bool isActive();
};


#endif //ITEM_H
