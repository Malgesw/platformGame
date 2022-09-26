#include "Animation.h"

Animation::Animation(sf::Texture &texture, sf::Vector2i imageCount, float switchTime, sf::Vector2f position, sf::Vector2f size) :
imageCount(imageCount), switchTime(switchTime), texture(texture) {

    totalTime = 0.f;
    currentImage.x = 0;
    sprite.width = texture.getSize().x / (float)imageCount.x;
    sprite.height = texture.getSize().y / (float)imageCount.y;
    animationBox.setSize(sf::Vector2f(size.x*1.5f, size.y*1.5f));
    animationBox.setPosition(position.x, position.y);
    animationBox.setTexture(&texture);
    faceRight = true;

}

void Animation::update(Movement &playerMovement, const float &dt) {

    int row;
    switch (playerMovement.getSpriteType()) {
        case IDLELEFT:
            row = 0;
            faceRight= false;
            break;
        case IDLERIGHT:
            row = 0;
            faceRight= true;
            break;
        case MOVELEFT:
            row = 1;
            faceRight = false;
            break;
        case MOVERIGHT:
            row = 1;
            faceRight= true;
            break;
        case JUMPRIGHT:
            row = 2;
            faceRight= true;
            break;
        case JUMPLEFT:
            row = 2;
            faceRight = false;
            break;
        default:
            row = 0;
            break;
    }

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
    if(faceRight) {
        sprite.left = currentImage.x * sprite.width;
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

