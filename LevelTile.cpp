//
// Created by seren on 19/07/2022.
//

#include "LevelTile.h"


bool LevelTile::setupSprite(std::string textureName) {
    if(!texture.loadFromFile(textureName)){
        return false;
    }
    //TODO-REMOVE SETSMOOTH WITH FINAL ASSETS reminder to avoid fuckups
    texture.setSmooth(true);


    body.setFillColor(sf:: Color::White);
    body.setTexture(&texture);
    //temporary texture cut for testing
    body.setTextureRect(sf::IntRect(0,0,50,50));
    return true;
}



LevelTile::LevelTile(std::string textureName , float x, float y, bool viable, bool exit,sf::Vector2f size) {
    body.setSize(size);
    pos= sf:: Vector2f(x,y);
    if(!setupSprite(textureName)){
        return;
    }

    isViable = viable;
    //collision checking-applies to whole pic instead of cut texture but it works
    if(!isViable){
        body.setOutlineColor(sf::Color::Red);
        body.setOutlineThickness(2.f);
    }
    isExit = exit;
    //exit checking-same thing
    if(isExit){
        body.setOutlineColor(sf::Color::Blue);
        body.setOutlineThickness(2.f);
    }
    body.setPosition(pos);




}

//collision handling for later
const sf::FloatRect LevelTile::getGlobalBounds() const {
    return this->body.getGlobalBounds();
}
