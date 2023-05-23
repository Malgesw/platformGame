#include "AutoFlying.h"

AutoFlying::AutoFlying(float movementSpeed, sf::Vector2f startPosition, sf::Vector2f size,
                       const std::vector<std::shared_ptr<LevelTile>> &walls, sf::Vector2f wallSize,
                       unsigned short *typeOfSprite) :
        FlyingMovement(movementSpeed, startPosition, size, typeOfSprite, false) {


    collisionBox.setFillColor(sf::Color::Red);
    pathfinder = std::make_unique<Pathfinder>(walls, wallSize, 2.0f, startPosition, startPosition, 0.1f);
    pathfinder->setWorldSize(sf::Vector2f(16, 16));
    pathfinder->setHeuristic(AStar::Heuristic::manhattan);
    pathfinder->setDiagonalMovement(true);

    if (!inertia) {
        speed = speed * 10;
    }
}

void AutoFlying::rest() {

}

void AutoFlying::aggro(const float &dt, sf::Vector2f playerPosition) {

    sf::Vector2f movement= pathfinder->getMovement(playerPosition,sf::Vector2f (collisionBox.getPosition().x+collisionBox.getSize().x/2,collisionBox.getPosition().y+collisionBox.getSize().y/2),dt);
    if (movement.x>1.f)
        moveRight();
    else if(movement.x<-1.f)
        moveLeft();
    if (movement.y>1.f)
        FlyingMovement::moveDown();
    else if(movement.y<-1.f)
        FlyingMovement::moveUp();

    velocity.x=velocity.x/1.01f;
    velocity.y=velocity.y/1.05f;

    if (!inertia){
        velocity.x=0;
        velocity.y=0;

    }
}

void AutoFlying::update(const float &deltaTime, sf::Vector2f playerPosition) {

    aggro(deltaTime,playerPosition);
    Movement::update(deltaTime,playerPosition);

}

