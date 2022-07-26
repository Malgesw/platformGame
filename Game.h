#ifndef PLATFORMGAME_GAME_H
#define PLATFORMGAME_GAME_H

#include "State.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "Subject.h"
#include "list"

class Game: public Subject{

public:

    Game();
    ~Game() override;

    void updateDeltaTime();
    void updateEvents();
    void update();
    void render();
    void run();
    void addObserver(Observer* o) override;
    void removeObserver(Observer* o) override;
    void notifyObservers() const override;


private:

    sf::RenderWindow *window;
    std::stack<std::unique_ptr<State>> states;
    std::map<std::string, int> supportedKeys;

    sf::Clock clock;
    sf::Event event{};

    float deltaTime;
    std::list<Observer*> dtShare;

    void initWindow();
    void initStates();
    void initKeys();





};


#endif //PLATFORMGAME_GAME_H
