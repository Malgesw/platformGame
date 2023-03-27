#include "Item.h"

Item::Item(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position) {
    onMap = true;
    body.setSize(size);
    body.setPosition(position);
    //body.setFillColor(sf::Color::Cyan);
    body.setTexture(texture);
}

void Item::render(sf::RenderTarget &target) {
    target.draw(body);
}

void Item::use(GameCharacter &player) {
    if (player.getHp() < player.getStartHp())
        player.setHp(player.getHp() + 1);
}


