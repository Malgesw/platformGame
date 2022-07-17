#ifndef PLATFORMGAME_STATE_H
#define PLATFORMGAME_STATE_H

#include "headers.h"

class State {

public:

    State(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states);
    virtual ~State() = default;

    virtual void update(const float &dt) = 0;
    virtual void render(sf::RenderTarget &target) = 0;


protected:

    sf::RenderWindow *window;
    std::stack<std::unique_ptr<State>> *states;

};


#endif //PLATFORMGAME_STATE_H
