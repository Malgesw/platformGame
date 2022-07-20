#include "GameState.h"

GameState::GameState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev) :
State(window, states, ev) {

    shape.setSize(sf::Vector2f(100.f, 100.f));
    shape.setFillColor(sf::Color::Green);

    font.loadFromFile("/home/kaneki/CLionProjects/platformGame/Fonts/PAPYRUS.ttf");

    isPaused = false;

    pauseMenu = std::make_unique<PauseMenu>(window, font);
    pauseTime = 0.5f;
    pauseClock.restart();

}

void GameState::update(const float &dt) {

    mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && isReady()){

        pauseClock.restart();

        if(!isPaused)
            isPaused = true;
        else
            isPaused = false;

    }

    if(isPaused){

        pauseMenu->update(mousePos);

        if(pauseMenu->isButtonPressed("CONTINUE"))
            isPaused = false;

        if(pauseMenu->isButtonPressed("EXIT_MENU"))
            states->pop();

    }


}

void GameState::render(sf::RenderTarget &target) {

    target.draw(shape);
    
    if(isPaused)
        pauseMenu->render(target);


}

bool GameState::isReady() const {

    if(pauseClock.getElapsedTime().asSeconds() >= pauseTime)
        return true;
    else
        return false;

}
