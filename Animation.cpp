#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2i imageCount, float switchTime, sf::Vector2f size, bool isplayer,unsigned short *typeOfSprite) :
imageCount(imageCount), switchTime(switchTime), texture(texture) {

    totalTime = 0.f;
    currentImage.x = 0;
    positionCorrection.x=25.f;
    positionCorrection.y=0.f;

        sprite.width = texture->getSize().x / (float) imageCount.x;
        sprite.height = texture->getSize().y / (float) imageCount.y;

    animationBox.setSize(sf::Vector2f(size.x*1.5f, size.y*1.5f));
    animationBox.setTexture(texture);
    faceRight = true;
    if(isplayer) {
        animationLeftOffset = -57.6f;
        animationRightOffset=-19.2f;
    }

}

void Animation::update(Movement &playerMovement, const float &dt) {

    animationBox.setPosition(faceRight?playerMovement.getCollisions().getPosition().x-playerMovement.getCollisions().getSize().x/4.f+animationLeftOffset:
                             playerMovement.getCollisions().getPosition().x-playerMovement.getCollisions().getSize().x/4.f+animationRightOffset,
                             playerMovement.getCollisions().getPosition().y-playerMovement.getCollisions().getSize().y/4.f);

    int row;
    switch (*typeOfSprite) {
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

