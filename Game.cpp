#include "Game.h"

Game::Game() {

    initWindow();
    initStates();
    deltaTime = 0.f;

}

Game::~Game() {

    delete window;

}

void Game::updateDeltaTime() {

    deltaTime = clock.getElapsedTime().asSeconds();
    clock.restart();

}

void Game::updateEvents() {

    while(window->pollEvent(event)){
        if(event.type == sf::Event::Closed)
            window->close();
    }

}

void Game::update() {

    updateEvents();

    if(!states.empty())
        states.top()->update(deltaTime);
    else
        window->close();


}

void Game::render() {

    window->clear();

    if(!states.empty())
        states.top()->render(*window);

    window->display();

}

void Game::run() {

    while(window->isOpen()){

        updateDeltaTime();
        update();
        render();

    }

}

void Game::initWindow() {

    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Platform");

}

void Game::initStates() {

    states.push(std::make_unique<MainMenuState>(window, &states));

}


