#include "Animation.h"

Animation::Animation(sf::Texture &texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, sf::Vector2f size) :
imageCount(imageCount), switchTime(switchTime), texture(texture) {

    totalTime = 0.f;
    currentImage.x = 0;

    sprite.width = texture.getSize().x / (float)imageCount.x;
    sprite.height = texture.getSize().y / (float)imageCount.y;

    animationBox.setSize(sf::Vector2f(size.x * 1.8f, size.y * 1.2f));
    animationBox.setPosition(position);
    animationBox.setTexture(&texture);

    positionCorrection.x = -10.f;
    positionCorrection.y = -6.f;
}

void Animation::update(int row, const float &dt, bool jumpRight) {

    currentImage.y = row;
    totalTime += dt;
    float t = switchTime;
    if(row > 0) {
        switchTime -= 0.15f;
    }

    if(totalTime >= switchTime){

        totalTime -= switchTime;

        if(row != 2) {
            currentImage.x++;
            if (currentImage.x == imageCount.x)
                currentImage.x = 0;
        }
        else if(currentImage.x < imageCount.x-1)
                currentImage.x++;

    }

    sprite.top = currentImage.y * sprite.height;

    if(jumpRight) {
        sprite.left = currentImage.x * sprite.width - 30.f;
        sprite.width = std::abs(sprite.width);
    }
    else{
        sprite.left = (currentImage.x+1) * std::abs(sprite.width);
        sprite.width = -std::abs(sprite.width);
    }

    switchTime = t;

}

void Animation::render(sf::RenderTarget &target) {

    target.draw(animationBox);

}

