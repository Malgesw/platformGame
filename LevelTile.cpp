//
// Created by seren on 19/07/2022.
//

#include "LevelTile.h"


bool LevelTile::setupSprite(std::string textureName) {
    if(!texture.loadFromFile(textureName)){
        return false;
    }
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
    //collision checking
    if(!isViable){
        body.setOutlineColor(sf::Color::Red);
        body.setOutlineThickness(2.f);
    }
    isExit = exit;
    //exit checking
    if(isExit){
        body.setOutlineColor(sf::Color::Blue);
        body.setOutlineThickness(2.f);
    }
    body.setPosition(pos);

}

void LevelTile::render(sf::RenderTarget &target) {
    target.draw(body);

}

const sf::RectangleShape &LevelTile::getBody() const {
    return body;
}

void LevelTile::setBody(const sf::RectangleShape &body) {
    LevelTile::body = body;
}

//collision handling for later
const sf::FloatRect LevelTile::getGlobalBounds() const {
    return this->body.getGlobalBounds();
}
