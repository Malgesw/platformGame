#ifndef GRAVITY_GAMECHARACTER_H
#define GRAVITY_GAMECHARACTER_H

#include "headers.h"
#include <cmath>
#include "LevelTile.h"

class GameCharacter {
public:
    GameCharacter(float width, float height, sf::Color color, float posX = 0.f, float posY = 0.f);
    ~GameCharacter() = default;

    void render(sf::RenderTarget &target);
    void update(const float &dt, const std::vector<std::shared_ptr<LevelTile>>& objects, sf::RenderWindow *window);
    void checkCollisions(const float &dt, const std::vector<std::shared_ptr<LevelTile>>& objects);

    bool getJump() const{
        return canJump;
    }
    sf::Vector2f getVelocity() const{
        return velocity;
    }
    float getSpeed() const{
        return speed;
    }
    float getJumpHeight() const{
        return jumpHeight;
    }
    void setJump(bool jump){
         canJump = jump;
    }
    void setVelocity(float x, float y) {
        velocity.x = x;
        velocity.y = y;
    }



private:
    sf::RectangleShape body;
    sf::Vector2f velocity;
    float speed;
    float jumpHeight;
    bool canJump;

};


#endif //GRAVITY_GAMECHARACTER_H
