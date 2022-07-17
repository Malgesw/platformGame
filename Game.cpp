#include "Game.h"

Game::Game() {

    initWindow();

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

}

void Game::render() {

    window->clear();
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

    window = new sf::RenderWindow(sf::VideoMode(400, 400), "Platform");

}


