#ifndef PLATFORMGAME_ANIMATION_H
#define PLATFORMGAME_ANIMATION_H

#include "headers.h"

class Animation {

public:

    Animation( sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, sf::Vector2f size);
    ~Animation() = default;

    void update(int row, const float &dt, bool jumpRight);
    void render(sf::RenderTarget &target);

    sf::IntRect &getSprite() {
        return sprite;
    }

    sf::RectangleShape &getAnimationBox() {
        return animationBox;
    }

    const sf::Vector2f &getPositionCorrection() const{
        return positionCorrection;
    }

    void setPositionCorrection(sf::Vector2f(newPos)){
        positionCorrection = newPos;
    }


private:

    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    sf::IntRect sprite;

    float totalTime;
    float switchTime;

    sf::Texture* texture;
    sf::RectangleShape animationBox;

    sf::Vector2f positionCorrection;


};


#endif //PLATFORMGAME_ANIMATION_H
