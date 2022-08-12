//
// Created by seren on 19/07/2022.
//

#include "LevelTile.h"


bool LevelTile::setupSprite(unsigned short tile) {

    std::string textureName;

    switch(tile){

        case TILES::DOOR:
            textureName = "../images/door.png";
            isExit = true;
            break;
        case TILES::GROUND:
            textureName = "../images/Ground.jpg";
            break;
        case TILES::WALL:
            textureName = "../images/wall.png";
            isViable = false;
            break;
        default:
            textureName = "";

    }

    if(!texture.loadFromFile(textureName))
        return false;

    texture.setSmooth(true);
    body.setFillColor(sf:: Color::White);
    body.setTexture(&texture);
    //temporary texture cut for testing
    body.setTextureRect(sf::IntRect(0,0,50,50));
    return true;

}

LevelTile::LevelTile(unsigned short tile , float x, float y, sf::Vector2f size) {

    body.setSize(size);
    isViable = true;
    isExit = false;

    if(!setupSprite(tile)){
        std::cout << "Sprite not loaded" << std::endl;
    }

    body.setPosition( sf:: Vector2f(x,y));

}

void LevelTile::render(sf::RenderTarget &target) {
    target.draw(body);

}

//collision handling for later
 sf::FloatRect LevelTile::getGlobalBounds() const {
    return body.getGlobalBounds();
}

bool LevelTile::getViable() const {
    return isViable;
}
