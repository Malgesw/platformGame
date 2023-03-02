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
    exit = type == DOOR;
    tileType = type;

    /*if(!setupSprite(tile)){
        std::cout << "Sprite not loaded" << std::endl;
    }
     */
    body.setTexture(text);
    switch (type) {
        case (3):
            body.setTextureRect(sf::IntRect(0, 0, 1000, 975));
            break;
        case (1):
            body.setTextureRect(sf::IntRect(1000, 0, 1000, 975));
            break;
        case (0):
            body.setTextureRect(sf::IntRect(2000, 0, 1000, 975));
            break;
        case (4): //decwalldx
            body.setTextureRect(sf::IntRect(0, 980, 1000, 975));
            break;
        case (5): //bumpdx
            body.setTextureRect(sf::IntRect(1000, 980, 1000, 975));
            break;
        case (6): //spikedx
            body.setTextureRect(sf::IntRect(0, 1960, 1000, 975));
            break;
        case (7): //decwallsx
            body.setTextureRect(sf::IntRect(3000, 980, 1000, 975));
            break;
        case (8): //bumpsx
            body.setTextureRect(sf::IntRect(2000, 980, 1000, 975));
            break;
        case (9): //spikesx
            body.setTextureRect(sf::IntRect(3000, 1960, 1000, 975));
            break;
        default:
            body.setTextureRect(sf::IntRect(3000, 0, 1000, 975));
            break;
    }


    //body.setTextureRect(sf::IntRect(0,0,50,50));
    body.setPosition(sf::Vector2f(x, y));

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
