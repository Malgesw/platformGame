#ifndef PLATFORMGAME_STATE_H
#define PLATFORMGAME_STATE_H

#include "headers.h"

class State {

public:

    State(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
          std::map<std::string, int> *supportedKeys);
    virtual ~State() = default;

    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget &target) = 0;
    virtual void initKeys() = 0;
    virtual void checkForClose();



protected:

    sf::RenderWindow *window;
    std::stack<std::unique_ptr<State>> *states;
    std::map<std::string, int> *supportedKeys;
    std::map<std::string, int> keyBinds;

    const sf::Event &textEvent;

};


#endif //PLATFORMGAME_STATE_H
