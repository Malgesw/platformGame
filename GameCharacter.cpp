//
// Created by alessio on 24/07/22.
//

#include "GameCharacter.h"
#include "WalkingMovement.h"
#include "FlyingMovement.h"

GameCharacter::GameCharacter(sf::Vector2f startPosition, sf::Vector2f size,const std::vector<std::shared_ptr<LevelTile>>& walls) {

    movement=new WalkingMovement(80,startPosition,size,walls,200);

    texture.loadFromFile("../images/sprite.png");
    texture.setSmooth(true);

    movement->getCollisions().setTexture(&texture);

    animation = std::make_unique<Animation>(texture, sf::Vector2u(5, 6), 0.3f, startPosition, size);

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
    //animation->getAnimationBox().setPosition(sf::Vector2f(movement->getCollisions().getPosition().x - 8.f, movement->getCollisions().getPosition().y));
    animation->getAnimationBox().setPosition(movement->getCollisions().getPosition() + animation->getPositionCorrection());

    int row;
    sf::IntRect animationRect(animation->getSprite().left, animation->getSprite().top,
                              animation->getSprite().width, animation->getSprite().height);

    switch (movement->getSpriteType()) {

        case IDLE_SPRITE:
            row = 0;
            animationRect.height -= 20.f;
            break;
        case MOVELEFT:
            row = 1;
            animationRect.height -= 15.f;
            break;
        case MOVERIGHT:
            row = 2;
            animationRect.height -= 10.f;
            break;
        default:
            row = 0;
            break;

    }

    animation->update(row, dt);
    //movement->getCollisions().setTextureRect(animationRect);
    animation->getAnimationBox().setTextureRect(animationRect);



}

Movement *GameCharacter::getMovement() const {
    return movement;
}
