#include "GameState.h"

GameState::GameState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states) : State(window, states) {

    shape.setSize(sf::Vector2f(100.f, 100.f));
    shape.setFillColor(sf::Color::Green);

}

void GameState::update(const float &dt) {

    checkForClose();

}

void GameState::render(sf::RenderTarget &target) {

    target.draw(shape);

}
