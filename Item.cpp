#include "Item.h"

Item::Item(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position) : texture(texture) {
    onMap = true;
    body.setSize(size);
    body.setPosition(position);
    body.setFillColor(sf::Color::Cyan);
    //CODE FOR SETTING THE TEXTURE
    //___________
}

void Item::render(sf::RenderTarget &target) {
    target.draw(body);
}


