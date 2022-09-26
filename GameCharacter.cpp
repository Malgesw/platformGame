//
// Created by alessio on 24/07/22.
//

#include "GameCharacter.h"
#include "WalkingMovement.h"
#include "FlyingMovement.h"

GameCharacter::GameCharacter(sf::Vector2f startPosition, sf::Vector2f size, int healthPoints, int mana)
:hp(healthPoints),energy(mana)
{

//___________________________________________DEFAULT PARAMETERS
if(healthPoints == 30)
    texture.loadFromFile("../images/enemysheet.png");
else
    texture.loadFromFile("../images/playersheet.png");
texture.setSmooth(true);
movement= std::make_shared<WalkingMovement>(80,startPosition,size,200);
attack= std::make_shared<Attack>(size*2.5f,0.5f,40.f,55.f);
animation = std::make_unique<Animation>(texture, sf::Vector2i(5, 3), 0.3f, startPosition, size);
}


void GameCharacter::setMovement(std::shared_ptr<Movement>& newMovement) {
    movement = newMovement;
}


void GameCharacter::setAttack( std::shared_ptr<Attack> &newAttack) {
    attack = newAttack;
}

void GameCharacter::render(sf::RenderTarget &target) {

//target.draw(movement->getCollisions());
animation->render(target);

}

void GameCharacter::update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects,
                           sf::RenderWindow* window, sf::Vector2f mainCharacterPos) {

    sf::Vector2f collisionboxCenter(movement->getCollisions().getPosition().x+movement->getCollisions().getSize().x/2,
                                    movement->getCollisions().getPosition().y+movement->getCollisions().getSize().y/2);

    movement->update(window,dt,mainCharacterPos);
    attack->update(collisionboxCenter);
    animation->getAnimationBox().setPosition(movement->getCollisions().getPosition().x-movement->getCollisions().getSize().x/4.f,
                                             movement->getCollisions().getPosition().y-movement->getCollisions().getSize().y/4.f);

    sf::IntRect animationRect(animation->getSprite().left, animation->getSprite().top,
                              animation->getSprite().width, animation->getSprite().height);

    animation->update(*movement, dt);
    animation->getAnimationBox().setTextureRect(animationRect);

}

std::shared_ptr<Movement> GameCharacter::getMovement() const {
    return movement;
}

void GameCharacter::die() {

}

int GameCharacter::getHp() const {
    return hp;
}

void GameCharacter::setHp(int healthPoints) {
    GameCharacter::hp = healthPoints;
}

int GameCharacter::getEnergy() const {
    return energy;
}

void GameCharacter::setEnergy(int mana) {
    GameCharacter::energy = mana;
}

const std::shared_ptr<Attack> &GameCharacter::getAttack() const {
    return attack;
}


AttackTarget GameCharacter::generateTarget() {

    return AttackTarget(movement->getCollisions(),attack->getHitBox(),movement->getKnockback(),hp);
}

bool GameCharacter::isFacingRight() const {
    return animation->isFacingRight();
}

const std::unique_ptr<Animation> &GameCharacter::getAnimation() const {
    return animation;
}

void GameCharacter::setAnimation(std::unique_ptr<Animation> &anim) {
    animation = std::move(anim);
}
