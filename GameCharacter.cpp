#include "GameCharacter.h"


GameCharacter::GameCharacter(int healthPoints, int mana)
:hp(healthPoints),energy(mana)
{

//___________________________________________DEFAULT PARAMETERS
}

void GameCharacter::setMovement(std::unique_ptr<Movement> newMovement) {
    if (newMovement== nullptr) throw std::runtime_error("Movement passed is not valid");
    movement = std::move(newMovement);
}


void GameCharacter::setAttack( std::unique_ptr<Attack> newAttack) {
    if (newAttack== nullptr) throw std::runtime_error("Attack passed is not valid");
    attack = std::move(newAttack);
}

void GameCharacter::setAnimation(std::unique_ptr<Animation> newAnimation) {
    if (newAnimation== nullptr) throw std::runtime_error("Animation passed is not valid");
    animation = std::move(newAnimation);
}


void GameCharacter::render(sf::RenderTarget &target) {


   // target.draw(attack->getHitBox());
  //  target.draw(movement->getCollisions());
    animation->render(target);
    attack->render(target);


}

void GameCharacter::update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects, sf::Vector2f mainCharacterPos) {

    if(movement == nullptr or attack == nullptr or animation == nullptr){
        throw std::runtime_error("character's components not valid");
    }
    previousTypeOfSprite = typeOfSprite;

    sf::Vector2f hitboxCenter(
            isFacingRight() ? movement->getCollisions().getPosition().x + movement->getCollisions().getSize().x
                            : movement->getPosition().x,
            movement->getCollisions().getPosition().y + movement->getCollisions().getSize().y / 2);

    movement->update(dt,mainCharacterPos);
    attack->update(dt,hitboxCenter,isFacingRight(),objects);

    animation->update(*movement, dt, previousTypeOfSprite);

}

Movement& GameCharacter::getMovement(){
    return *movement;
}

Attack& GameCharacter::getAttack(){
    return *attack;
}

Animation& GameCharacter::getAnimation(){
    return *animation;
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


AttackTarget GameCharacter::generateTarget() {

    return AttackTarget(&movement->getCollisions(), &attack->getHitBox(), &movement->getKnockback(), &hp);
}

bool GameCharacter::isFacingRight() const {
    return animation->isFacingRight();
}

void GameCharacter::moveLeft() {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else movement->moveLeft();
}

void GameCharacter::moveRight() {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else movement->moveRight();
}

void GameCharacter::moveUp() {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else movement->moveUp();
}

void GameCharacter::moveDown() {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else movement->moveDown();
}

void GameCharacter::hit() {

    if (attack == nullptr)throw InvalidComponent(*this, ATTACK);
    else attack->hit();
}

sf::Vector2f GameCharacter::getVelocity() {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else return movement->getVelocity();
}

void GameCharacter::setVelocity(float x, float y) {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else movement->setVelocity(x, y);

}

sf::Vector2f GameCharacter::getPosition() {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else return movement->getPosition();
}

void GameCharacter::setPosition(float x, float y) {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else movement->getCollisions().setPosition(x, y);
}


bool GameCharacter::isOnGround() {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else return movement->onGround();
}


