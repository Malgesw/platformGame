#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2i imageCount, float switchTime, sf::Vector2f size, bool isplayer,unsigned short *typeOfSprite) :
imageCount(imageCount), switchTime(switchTime), texture(texture), typeOfSprite(typeOfSprite) {

    totalTime = 0.f;
    currentImage.x = 0;
    positionCorrection.x=25.f;
    positionCorrection.y=0.f;

        sprite.width = texture->getSize().x / (float) imageCount.x;
        sprite.height = texture->getSize().y / (float) imageCount.y;

    animationBox.setSize(sf::Vector2f(size.x*1.5f, size.y*1.5f));
    animationBox.setTexture(texture);
    faceRight = true;
    isRepeatable = true;
    if(isplayer) {
        animationLeftOffset = -57.6f;
        animationRightOffset=-19.2f;
    }

}

void Animation::update(Movement &playerMovement, const float &dt, unsigned short prevTypeOfSprite) {

    animationBox.setPosition(faceRight ? playerMovement.getCollisions().getPosition().x -
                                         playerMovement.getCollisions().getSize().x / 4.f + animationLeftOffset :
                             playerMovement.getCollisions().getPosition().x -
                             playerMovement.getCollisions().getSize().x / 4.f + animationRightOffset,
                             playerMovement.getCollisions().getPosition().y -
                             playerMovement.getCollisions().getSize().y / 4.f);

    int row;
    switch (*typeOfSprite) {
        case IDLELEFT:
            row = 0;
            faceRight = false;
            isRepeatable = true;
            break;
        case IDLERIGHT:
            row = 0;
            faceRight= true;
            isRepeatable = true;
            break;
        case MOVELEFT:
            row = 1;
            faceRight = false;
            isRepeatable = true;
            break;
        case MOVERIGHT:
            row = 1;
            faceRight= true;
            isRepeatable = true;
            break;
        case JUMPRIGHT:
            row = 2;
            faceRight= true;
            isRepeatable = false;
            break;
        case JUMPLEFT:
            row = 2;
            faceRight = false;
            isRepeatable = false;
            break;
        case ATTACKRIGHT:
            row = 3;
            faceRight = true;
            isRepeatable = false;
            break;
        case ATTACKLEFT:
            row = 3;
            faceRight = false;
            isRepeatable = false;
            break;
        default:
            row = 0;
            break;
    }

    /*if(currentImage.x == imageCount.x-1 && row == 3){
        currentImage.x = 0;
        isRepeatable = true;
        row = 1;
    }*/

    currentImage.y = row;
    totalTime += dt;
    float t = switchTime;
    if(row > 0) {
        //if(row == 3)
            //switchTime += 0.10f;
        //else
            switchTime -= 0.15f;
    }

    if(totalTime >= switchTime){
        totalTime -= switchTime;
        if (isRepeatable) {
            currentImage.x++;
            if (currentImage.x == imageCount.x)
                currentImage.x = 0;
        } else if (currentImage.x < imageCount.x - 1)
            currentImage.x++;
        else
            *typeOfSprite = IDLERIGHT;
    }

    if ((*typeOfSprite == ATTACKRIGHT or *typeOfSprite == ATTACKLEFT) and
        (prevTypeOfSprite != ATTACKRIGHT and prevTypeOfSprite != ATTACKLEFT))
        currentImage.x = 0;

    sprite.top = currentImage.y * sprite.height;
    if (faceRight) {
        sprite.left = currentImage.x * sprite.width;
        sprite.width = std::abs(sprite.width);
    } else {
        sprite.left = (currentImage.x + 1) * std::abs(sprite.width);
        sprite.width = -std::abs(sprite.width);
    }
    switchTime = t;

}

void Animation::render(sf::RenderTarget &target) {
    target.draw(animationBox);
}

