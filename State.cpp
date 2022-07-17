#include "State.h"

State::State(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states) : window(window), states(states) {}

void State::checkForClose() {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        states->pop();

}
