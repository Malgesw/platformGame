#include "Animation.h"

Animation::Animation(sf::Texture &texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, sf::Vector2f size) :
imageCount(imageCount), switchTime(switchTime), texture(texture) {

    totalTime = 0.f;
    currentImage.x = 0;

    sprite.width = texture.getSize().x / (float)imageCount.x;
    sprite.height = texture.getSize().y / (float)imageCount.y;

    animationBox.setSize(sf::Vector2f(size.x * 1.8f, size.y * 1.1f));
    animationBox.setPosition(position);
    animationBox.setTexture(&texture);

    positionCorrection.x = -11.f;
    positionCorrection.y = -6.f;

}

void Animation::update(int row, const float &dt) {

    currentImage.y = row;
    totalTime += dt;
    float t = switchTime;
    if(row > 0) {
        switchTime -= 0.2f;
    }

    if(totalTime >= switchTime){

        totalTime -= switchTime;
        currentImage.x++;

        if(currentImage.x >= imageCount.x)
            currentImage.x = 0;

    }

    sprite.top = currentImage.y * sprite.height;
    sprite.left = (currentImage.x) * sprite.width;

    switchTime = t;

}

void Animation::render(sf::RenderTarget &target) {

    target.draw(animationBox);

}

