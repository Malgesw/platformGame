//
// Created by kaneki on 17/07/22.
//

#include "State.h"

State::State(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states) : window(window), states(states) {}
