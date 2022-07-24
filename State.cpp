#include "State.h"

State::State(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
             std::map<std::string, int> *supportedKeys) : window(window), states(states), textEvent(ev),
             supportedKeys(supportedKeys) {}

void State::checkForClose() {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("CLOSE"))))
        states->pop();

}
