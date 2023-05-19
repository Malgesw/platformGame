#include "GameCharacter.h"


GameCharacter::GameCharacter(float healthPoints, float mana)
        : hp(healthPoints), energy(mana), startHp(healthPoints), typeOfSprite(IDLERIGHT),
          previousTypeOfSprite(IDLERIGHT) {
    specialAbility = std::make_unique<NoSpecialAbility>();
}

void GameCharacter::setMovement(std::unique_ptr<Movement> newMovement) {
    if (newMovement== nullptr) throw std::runtime_error("Movement passed is not valid");
    movement = std::move(newMovement);
}


void GameCharacter::setAttack(std::unique_ptr<Attack> newAttack) {
    if (newAttack == nullptr) throw std::runtime_error("Attack passed is not valid");
    attack = std::move(newAttack);
}

void GameCharacter::setAnimation(std::unique_ptr<Animation> newAnimation) {
    if (newAnimation == nullptr) throw std::runtime_error("Animation passed is not valid");
    animation = std::move(newAnimation);
}

void GameCharacter::setSpecialAbility(std::unique_ptr<SpecialAbility> newSpecialAbility) {
    if (newSpecialAbility == nullptr) throw std::runtime_error("Special ability passed is not valid");
    specialAbility = std::move(newSpecialAbility);
}


void GameCharacter::render(sf::RenderTarget &target) {

#if DEBUG
    target.draw(attack->getHitBox());
    target.draw(movement->getCollisions());
#endif
    if (hp > 0) {
        animation->render(target);
        attack->render(target);
    }
}

void GameCharacter::update(const float &dt, const std::vector<std::shared_ptr<LevelTile>> &objects, sf::Vector2f mainCharacterPos) {

    if (movement == nullptr or attack == nullptr or animation == nullptr) {
        throw std::runtime_error("character's components not valid");
    }

    selfTarget.update(&movement->getCollisions(), &attack->getHitBox(), &movement->getKnockback(), &hp,
                      specialAbility->getStatus());

    previousTypeOfSprite = typeOfSprite;

    //sf::Vector2f hitboxCenter(
    //        isFacingRight() ? movement->getCollisions().getPosition().x + movement->getCollisions().getSize().x
    //                        : movement->getPosition().x,
    //        movement->getCollisions().getPosition().y + movement->getCollisions().getSize().y / 2);
    sf::Vector2f hitboxCenter(movement->getCollisions().getPosition() + movement->getCollisions().getSize() / 2.f);

    movement->update(dt, mainCharacterPos);
    attack->update(dt, hitboxCenter, isFacingRight(), objects);
    specialAbility->update();

    animation->update(*movement, dt, previousTypeOfSprite);

    if (isDroidActivated) {
        if (firstActivated) {
            notify(DROIDACTIVATED);
            firstActivated = false;
        }
        if (energy > 0) {
            energy -= energyConsuption * dt;
        } else {
            restoreOldComponents();
            isDroidActivated = false;
            firstActivated = true;
        }
    }

}

/* OLD IMPLEMENTATION, FOR TESTING PURPOSES ONLY
Movement& GameCharacter::getMovement(){
    return *movement;
}

Attack& GameCharacter::getAttack(){
    return *attack;
}

Animation& GameCharacter::getAnimation(){
    return *animation;
}
*/

float GameCharacter::getHp() const {
    return hp;
}

void GameCharacter::setHp(float healthPoints) {
    GameCharacter::hp = healthPoints;
}

float GameCharacter::getEnergy() const {
    return energy;
}

void GameCharacter::setEnergy(float mana) {
    GameCharacter::energy = mana;
}


AttackTarget *GameCharacter::generateTarget() {

    return &selfTarget;
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

sf::Vector2f GameCharacter::getVelocity() const {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else return movement->getVelocity();
}

void GameCharacter::setVelocity(float x, float y) {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else movement->setVelocity(x, y);

}

sf::Vector2f GameCharacter::getPosition() const {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else return movement->getPosition();
}

void GameCharacter::setPosition(float x, float y) {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else movement->getCollisions().setPosition(x, y);
}

sf::Vector2f GameCharacter::getSize() const {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else return {movement->getCollisions().getGlobalBounds().width, movement->getCollisions().getGlobalBounds().height};
}

sf::FloatRect GameCharacter::getGlobalBounds() const {
    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else return movement->getCollisions().getGlobalBounds();
}


bool GameCharacter::isOnGround() const {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else return movement->onGround();
}


bool GameCharacter::isColliding() const {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else return movement->checkCollisions();
}


void GameCharacter::addWalls(const std::vector<std::shared_ptr<LevelTile>> &newWalls) {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else movement->addWalls(newWalls);
    if (backupMovement != nullptr) backupMovement->addWalls(newWalls);
}

void GameCharacter::clearWalls() {

    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else movement->clearWalls();
    if (backupMovement != nullptr) backupMovement->clearWalls();
}

void GameCharacter::addTargets(const std::vector<AttackTarget *> &newTargets) {

    if (attack == nullptr)throw InvalidComponent(*this, ATTACK);
    else attack->addTargets(newTargets);
    if (backupAttack != nullptr) backupAttack->addTargets(newTargets);
}

void GameCharacter::clearTargets() {

    if (attack == nullptr)throw InvalidComponent(*this, ATTACK);
    else attack->clearTargets();
    if (backupAttack != nullptr) backupAttack->clearTargets();
}

void GameCharacter::saveOldComponents() {
    if (movement == nullptr)throw InvalidComponent(*this, MOVEMENT);
    else if (attack == nullptr)throw InvalidComponent(*this, ATTACK);
    else if (animation == nullptr)throw InvalidComponent(*this, ANIMATION);
    backupAnimation = std::move(animation);
    backupMovement = std::move(movement);
    backupAttack = std::move(attack);
}

bool GameCharacter::savedComponentsPresent() {
    if (backupMovement != nullptr and backupAttack != nullptr and backupAnimation != nullptr)
        return true;
    else
        return false;
}

void GameCharacter::restoreOldComponents() {

    backupMovement->getCollisions().setPosition(movement->getPosition());
    animation = std::move(backupAnimation);
    movement = std::move(backupMovement);
    attack = std::move(backupAttack);
}


void GameCharacter::clearRelatedObjects() {
    if (attack == nullptr)throw InvalidComponent(*this, ATTACK);
    else attack->clearRelatedObjects();
}

void GameCharacter::attach(Observer *o) {
    observers.push_back(o);
}

void GameCharacter::detach(Observer *o) {
    observers.remove(o);
}

void GameCharacter::notify(unsigned short category) const {
    for (auto &o: observers) {
        o->getNews(category);
    }
}
