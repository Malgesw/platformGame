#include "LevelTile.h"


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
            body.setTextureRect(sf::IntRect(3000, 980, 1000, 975));
            break;
        case (1):
            body.setTextureRect(sf::IntRect(1000, 1960, 1000, 975));
            break;
        case (0): //outmap
            // body.setFillColor(sf::Color::Black);
            body.setTextureRect(sf::IntRect(4000, 6860, 1000, 975));
            break;
        case (2):
            body.setTextureRect(sf::IntRect(2000, 0, 1000, 975));
            break;
        case (4): //decwalldx
            body.setTextureRect(sf::IntRect(0, 2940, 1000, 975));
            break;
        case (5): //bumpdx
            body.setTextureRect(sf::IntRect(1000, 2940, 1000, 975));
            break;
        case (6): //spikedx
            body.setTextureRect(sf::IntRect(0, 3920, 1000, 975));
            break;
        case (7): //decwallsx
            body.setTextureRect(sf::IntRect(3000, 3920, 1000, 975));
            break;
        case (8): //bumpsx
            body.setTextureRect(sf::IntRect(2000, 3920, 1000, 975));
            break;
        case (9): //spikesx
            body.setTextureRect(sf::IntRect(3000, 4900, 1000, 975));
            break;
        case (10): //wall_outvertdx
            body.setTextureRect(sf::IntRect(7000, 980, 995, 975));
            break;
        case (11): //wall_outvertsx
            body.setTextureRect(sf::IntRect(0, 980, 995, 975));
            break;
        case (12): //outwall_hor
            body.setTextureRect(sf::IntRect(1000, 0, 995, 975));
            break;
        case (13): //intersect_uptoleft
            body.setTextureRect(sf::IntRect(5000, 1960, 1000, 975));
            break;
        case (14): //intersect_outwall_northeast
            body.setTextureRect(sf::IntRect(7000, 0, 1000, 975));
            break;
        case (15): //intersect_outwall_northwest
            body.setTextureRect(sf::IntRect(0, 0, 1000, 975));
            break;
        case (16): //pod_dec_up
            body.setTextureRect(sf::IntRect(1000, 980, 1000, 975));
            break;
        case (17): //pod_dec_down
            body.setTextureRect(sf::IntRect(5000, 3920, 1000, 975));
            break;
        case (18): //int_ur
            break;
        case (19): //wall_hor without light
            body.setTextureRect(sf::IntRect(2000, 1960, 1000, 975));
            break;
        case (20): //intersect_outwall_southeast
            body.setTextureRect(sf::IntRect(7000, 6860, 1000, 975));
            break;
        case (21): //intersect_outwall_southwest
            body.setTextureRect(sf::IntRect(0, 6860, 1000, 975));
            break;
        case (22): //intersect_outwall_southwest
            body.setTextureRect(sf::IntRect(3000, 0, 1000, 975));
            break;
        case (23): //angle_nw
            body.setTextureRect(sf::IntRect(6000, 1960, 1000, 975));
            break;
        case (24): //angle_ne
            body.setTextureRect(sf::IntRect(7000, 1960, 1000, 975));
            break;
        case (25): //angle_sw
            body.setTextureRect(sf::IntRect(6000, 2940, 1000, 975));
            break;
        case (26): //angle_se
            body.setTextureRect(sf::IntRect(7000, 2940, 1000, 975));
            break;
        case (27): //intersect up to left-to be done yet
            body.setTextureRect(sf::IntRect(0, 0, 0, 0));
            break;
        case (28):
            body.setTextureRect(sf::IntRect(1000, 6824, 1000, 975));
            break;
        case (29):
            body.setTextureRect(sf::IntRect(4000, 6860, 1000, 975));
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
