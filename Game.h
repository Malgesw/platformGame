#ifndef PLATFORMGAME_GAME_H
#define PLATFORMGAME_GAME_H

#include "State.h"
#include "GameState.h"


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
    float deltaTime;
    sf::Clock clock;
    sf::Event event{};

    void initWindow();
    void initStates();





};


#endif //PLATFORMGAME_GAME_H
