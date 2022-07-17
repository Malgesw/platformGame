#ifndef PLATFORMGAME_GAME_H
#define PLATFORMGAME_GAME_H

#include "SFML/Graphics.hpp"


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
    float deltaTime;
    sf::Clock clock;
    sf::Event event{};

    void initWindow();





};


#endif //PLATFORMGAME_GAME_H
