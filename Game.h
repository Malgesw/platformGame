#ifndef PLATFORMGAME_GAME_H
#define PLATFORMGAME_GAME_H

#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"


class Game {

public:

    Game();
    ~Game();

    void updateDeltaTime();
    void updateEvents();
    void update();
    void render();
    void run();

private:

    sf::RenderWindow *window;
    std::stack<std::unique_ptr<State>> states;
    std::map<std::string, int> supportedKeys;

    sf::Clock clock;
    sf::Event event{};

    float deltaTime;

    void initWindow();
    void initStates();
    void initKeys();





};


#endif //PLATFORMGAME_GAME_H
