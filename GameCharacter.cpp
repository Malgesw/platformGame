#include "GameCharacter.h"

GameCharacter::GameCharacter(float width, float height, sf::Color color, float posX, float posY) {

    body.setSize(sf::Vector2f(width, height));
    body.setPosition(posX, posY);
    body.setFillColor(color);

    speed = 100.f;
    jumpHeight = 150.f;
    velocity.x = 0.f;
    velocity.y = 0.f;

    canJump = true;

}

void GameCharacter::render(sf::RenderTarget &target) {
    target.draw(body);
}

void GameCharacter::update(const float &dt, const std::vector<LevelTile*> objects,
                           sf::RenderWindow *window) {

    if(body.getPosition().y + body.getSize().y < (float)(*window).getSize().y)
        velocity.y += 981.f * dt;

    checkCollisions(dt, objects);

    body.move(velocity*dt);

    //Collisions
    if(body.getPosition().y + body.getSize().y >= 600.f) {
        body.setPosition(body.getPosition().x, 600.f - body.getSize().y);
        canJump = true;
    }

    if(body.getPosition().x < 0.f)
        body.setPosition(0, body.getPosition().y);

    if(body.getPosition().x + body.getSize().x >= 800.f)
        body.setPosition(800.f - body.getSize().x, body.getPosition().y);

    if(body.getGlobalBounds().top < 0.f)
        body.setPosition(body.getGlobalBounds().left, 0.f);

}

void GameCharacter::checkCollisions(const float &dt, const std::vector<LevelTile*> objects) {

    for(auto &o : objects){

        sf::FloatRect playerBounds = body.getGlobalBounds();
        sf::FloatRect objectBounds;
        sf::FloatRect nextPlayerPos = playerBounds;
        nextPlayerPos.left += velocity.x*dt;
        nextPlayerPos.top += velocity.y*dt;

        objectBounds = o->getGlobalBounds();
        if(objectBounds.intersects(nextPlayerPos)){

            //Bottom
            if(playerBounds.top < objectBounds.top &&
               playerBounds.top + playerBounds.height < objectBounds.top + objectBounds.height &&
               playerBounds.left < objectBounds.left + objectBounds.width &&
               playerBounds.left + playerBounds.width > objectBounds.left){
                velocity.y = 0.f;
                canJump = true;
                body.setPosition(playerBounds.left, objectBounds.top - playerBounds.height);
            }

            //Top
            else if(playerBounds.top > objectBounds.top &&
                    playerBounds.top + playerBounds.height > objectBounds.top + objectBounds.height &&
                    playerBounds.left < objectBounds.left + objectBounds.width &&
                    playerBounds.left + playerBounds.width > objectBounds.left){
                velocity.y = 0.f;
                body.setPosition(playerBounds.left, objectBounds.top + objectBounds.height);
            }


            //Right
            else if(playerBounds.left < objectBounds.left &&
                    playerBounds.left + playerBounds.width < objectBounds.left + objectBounds.width &&
                    playerBounds.top < objectBounds.top + objectBounds.height &&
                    playerBounds.top + playerBounds.height > objectBounds.top){
                velocity.x = 0.f;
                body.setPosition(objectBounds.left - playerBounds.width, playerBounds.top);
            }

            //Left
            else if(playerBounds.left > objectBounds.left &&
                    playerBounds.left + playerBounds.width > objectBounds.left + objectBounds.width &&
                    playerBounds.top < objectBounds.top + objectBounds.height &&
                    playerBounds.top + playerBounds.height > objectBounds.top){
                velocity.x = 0.f;
                body.setPosition(objectBounds.left + playerBounds.width, playerBounds.top);
            }

        }
    }
}
