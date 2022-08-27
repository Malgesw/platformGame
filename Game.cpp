#include "Game.h"

Game::Game() {

    initWindow();
    initKeys();
    initStates();

    deltaTime = 0.f;

}

Game::~Game() {

    delete window;

    while(!states.empty())
        states.pop();

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

    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Steamrush");

    std::ifstream ifs;
    ifs.open("../Config/window_settings.ini");
    std::string w,h;
    while(ifs >> w >> h){
        window->setSize(sf::Vector2u(std::stoi(w), std::stoi(h)));
    }
    ifs.close();
    window->setFramerateLimit(120);

}

void Game::initStates() {

    states.push(std::make_unique<MainMenuState>(window, &states, event, &supportedKeys));

}

void Game::initKeys() {

    std::ifstream file;

    file.open("../Config/supported_keys.ini");
    std::string key;
    int keyValue = 0;

    while(file >> key >> keyValue)
        supportedKeys[key] = keyValue;

    file.close();

}





