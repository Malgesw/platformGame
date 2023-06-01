#ifndef PLATFORMGAME_GAMESTATE_H
#define PLATFORMGAME_GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "GameCharacter.h"
#include "WalkingMovement.h"
#include "FlyingMovement.h"
#include "MeleeAttack.h"
#include "RangedAttack.h"
#include "Achievement.h"
#include "NoAttack.h"
#include "GlidingMovement.h"
#include "StarRangedAttack.h"

class GameState : public State {

public:

    GameState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,std::map<std::string, int> *supportedKeys);
    ~GameState() override;

    void update(const float &dt) override;

    void updatePlayerPos();

    void render(sf::RenderTarget &target) override;

    bool isReady() const;


private:

    bool jumpKeyReleased = true;
    bool attackKeyReleased = true;
    bool death = false;
    const float startPlayerLife = 10;
    const float startPlayerEnergy = 0;
    const float maxPlayerEnergy = 20;
    const sf::Vector2f startPlayerPosition = sf::Vector2f(300.f, 2880.f);
    std::unique_ptr<GameCharacter> player;
    sf::Vector2f mainCharacterPos;
    sf::Font font;
    std::unique_ptr<PauseMenu> pauseMenu;
    std::unique_ptr<PauseMenu> deathMenu;
    bool isPaused;
    float pauseTime;
    sf::Clock pauseClock;
    std::unique_ptr<TileMap> tileMap;
    sf::Texture *playerTexture;
    sf::Texture *statusBarTexture;
    sf::RectangleShape statusBar;
    sf::RectangleShape hpBar;
    sf::RectangleShape energyBar;
    sf::Text deathMessage;
    Achievement achievementCounter;
    sf::Clock invincibilityTimer;
    const float invincibilityTime = 0.5f;
    bool isInvincible = false;


    void initKeys() override;

};


#endif //PLATFORMGAME_GAMESTATE_H
