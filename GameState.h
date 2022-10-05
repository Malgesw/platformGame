#ifndef PLATFORMGAME_GAMESTATE_H
#define PLATFORMGAME_GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "GameCharacter.h"
#include "WalkingMovement.h"
#include "FlyingMovement.h"
#include "MeleeAttack.h"
#include "Achievement.h"


class GameState : public State {

public:

    GameState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,std::map<std::string, int> *supportedKeys);
    ~GameState() override;
    void update(const float &dt) override;
    void updatePlayerPos();
    void render(sf::RenderTarget &target) override;
    bool isReady() const;


private:

    bool keyReleased=true;
    std::unique_ptr<GameCharacter> player;
    sf::Vector2f mainCharacterPos;
    sf::Font font;
    std::unique_ptr<PauseMenu> pauseMenu;
    bool isPaused;
    float pauseTime;
    sf::Clock pauseClock;
    std::unique_ptr<TileMap> tileMap;
    sf::Texture* playerTexture;
    Achievement achievementCounter;


    void initKeys() override;

};


#endif //PLATFORMGAME_GAMESTATE_H
