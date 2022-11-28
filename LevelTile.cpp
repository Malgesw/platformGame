#include "LevelTile.h"

/*
bool LevelTile::setupSprite(char tile) {

    std::string textureName;

    switch(tile){

        case '2':
            textureName = "./images/door.png";
            exit = true;
            tileType = DOOR;
            break;
        case '0':
            textureName = "./images/Ground.jpg";
            tileType = GROUND;
            break;
        case '1':
            textureName = "./images/wall.png";
            tileType = WALL;
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
 */

LevelTile::LevelTile(sf::Texture* text  , float x, float y, sf::Vector2f size, unsigned short type) {

    body.setSize(size);
    exit = type==DOOR;
    tileType =type;

    /*if(!setupSprite(tile)){
        std::cout << "Sprite not loaded" << std::endl;
    }
     */
    body.setTexture(text);
    body.setTextureRect(sf::IntRect(0,0,50,50));
    body.setPosition( sf:: Vector2f(x,y));

}

void LevelTile::render(sf::RenderTarget &target) {
    target.draw(body);

}

//collision handling for later
 sf::FloatRect LevelTile::getGlobalBounds() const {
    return body.getGlobalBounds();
}

bool LevelTile::isExit() const {
    return exit;
}
