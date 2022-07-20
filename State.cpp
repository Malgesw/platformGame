#include "State.h"

State::State(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev) :
window(window), states(states), textEvent(ev) {}

void State::checkForClose() {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        states->pop();

}
