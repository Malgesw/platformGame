//
// Created by alessio on 24/07/22.
//

#include "GameCharacter.h"
#include "WalkingMovement.h"
#include "FlyingMovement.h"

GameCharacter::GameCharacter(sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>>& walls) {

    movement=new WalkingMovement(80,startPosition,size,walls,200);

    texture.loadFromFile("../images/playerSprite.png");
    texture.setSmooth(true);

    movement->getCollisions().setTexture(&texture);

    animation = std::make_unique<Animation>(texture, sf::Vector2u(5, 3), 0.3f, startPosition, size);

}

void GameCharacter::setMovement(Movement *newMovement) {

}

void GameCharacter::render(sf::RenderTarget &target) {

//target.draw(movement->getCollisions());
animation->render(target);

}

void GameCharacter::update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,
                           sf::RenderWindow* window) {

    movement->update(window,dt);
    animation->getAnimationBox().setPosition(movement->getCollisions().getPosition() + animation->getPositionCorrection());

    int row;
    bool jumpRight = true;
    sf::IntRect animationRect(animation->getSprite().left, animation->getSprite().top,
                              animation->getSprite().width, animation->getSprite().height);

    switch (movement->getSpriteType()) {

        case IDLE_SPRITE:
            row = 0;
            animationRect.height -= 50.f;
            //animationRect.width += 20.f;
            break;
        case MOVELEFT:
            row = 1;
            animationRect.height -= 170.f;
            //animationRect.width += 200.f;
            jumpRight = false;
            break;
        case MOVERIGHT:
            row = 1;
            animationRect.height -= 170.f;
            animationRect.width += 60.f;
            break;
        case JUMPRIGHT:
            row = 2;
            animationRect.height -= 60.f;
            break;
        case JUMPLEFT:
            row = 2;
            animationRect.height -= 60.f;
            jumpRight = false;
            break;
        default:
            row = 0;
            break;

    }

    animation->update(row, dt, jumpRight);
    animation->getAnimationBox().setTextureRect(animationRect);



}

Movement *GameCharacter::getMovement() const {
    return movement;
}
