#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states) : State(window, states) {

    shape.setSize(sf::Vector2f(100.f, 100.f));
    shape.setFillColor(sf::Color::Red);

}

void MainMenuState::update(const float &dt) {

    checkForClose();

}

void MainMenuState::render(sf::RenderTarget &target) {

    target.draw(shape);

}
