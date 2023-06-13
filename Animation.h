#ifndef PLATFORMGAME_ANIMATION_H
#define PLATFORMGAME_ANIMATION_H

#include "headers.h"
#include "Movement.h"

class Animation {

public:

    Animation( sf::Texture* texture, sf::Vector2i imageCount, float switchTime, sf::Vector2f size, bool isplayer, unsigned short* typeOfSprite);
    Animation(sf::Texture *texture, sf::Vector2i imageCount, float switchTime, sf::Vector2f size);


    ~Animation() = default;

    void update(Movement &playerMovement, const float &dt, unsigned short prevTypeOfSprite);
    void update(sf::FloatRect body, const float &dt);

    void render(sf::RenderTarget &target);

    sf::IntRect &getSprite() {
        return sprite;
    }
    sf::RectangleShape &getAnimationBox() {
        return animationBox;
    }

    bool isFacingRight() const {
        return faceRight;
    }

    void setCurrentImage(sf::Vector2i newCurrentImage) {
        currentImage.x = newCurrentImage.x;
        currentImage.y = newCurrentImage.y;
    }

    int &getCurrentRow() {
        return currentImage.y;
    }


private:

    sf::Vector2i imageCount;
    sf::Vector2i currentImage;
    sf::IntRect sprite;
    float totalTime;
    float switchTime;
    sf::Texture *texture;
    bool faceRight;
    sf::RectangleShape animationBox;
    sf::Vector2f positionCorrection;
    float animationLeftOffset = 0.f;
    float animationRightOffset = 0.f;
    unsigned short int lastNonAttackSprite = JUMPRIGHT;
    int attackAnimationFinished;
    unsigned short *typeOfSprite;
    bool isRepeatable;
    bool isPlayer;
};


#endif //PLATFORMGAME_ANIMATION_H
