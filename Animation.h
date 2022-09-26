#ifndef PLATFORMGAME_ANIMATION_H
#define PLATFORMGAME_ANIMATION_H

#include "headers.h"
#include "Movement.h"

class Animation {

public:

    Animation(sf::Texture &texture, sf::Vector2i imageCount, float switchTime, sf::Vector2f position, sf::Vector2f size);
    ~Animation() = default;

    void update(Movement &playerMovement, const float &dt);
    void render(sf::RenderTarget &target);

    sf::IntRect &getSprite() {
        return sprite;
    }
    sf::RectangleShape &getAnimationBox() {
        return animationBox;
    }
    bool isFacingRight() const{
        return faceRight;
    }


private:

    sf::Vector2i imageCount;
    sf::Vector2i currentImage;
    sf::IntRect sprite;
    float totalTime;
    float switchTime;
    bool faceRight;
    sf::Texture texture;
    sf::RectangleShape animationBox;


};


#endif //PLATFORMGAME_ANIMATION_H
