#include "Item.h"

Item::Item(sf::Vector2f size, sf::Vector2f position, std::unique_ptr<Animation> animation, float lifeGain)
        : lifeGain(lifeGain), animation(std::move(animation)) {
    onMap = true;
    body.setSize(size);
    body.setPosition(position);
}

void Item::update(const float &dt) {
    animation->update(body.getGlobalBounds(), dt);
}

void Item::render(sf::RenderTarget &target) {
    //target.draw(body);
    animation->render(target);
}

void Item::use(GameCharacter &player) {
    if (player.getHp() < player.getStartHp() || lifeGain < 0)
        player.setHp(player.getHp() + lifeGain);
}


