#include "GameState.h"

GameState::GameState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
                     std::map<std::string, int> *supportedKeys) : State(window, states, ev, supportedKeys) {

    initKeys();

    shape.setSize(sf::Vector2f(100.f, 100.f));
    shape.setFillColor(sf::Color::Green);

    font.loadFromFile("../Fonts/PAPYRUS.ttf");

    isPaused = false;

    pauseMenu = std::make_unique<PauseMenu>(window, font);
    pauseTime = 0.5f;
    pauseClock.restart();

}

void GameState::update(const float &dt) {

    updateMousePosition();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("CLOSE"))) && isReady()){

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
    else
        updatePlayerPos();
    
}

void GameState::updatePlayerPos() {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Jump"))))
        shape.move(0.f, -1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Left"))))
        shape.move(-1.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Right"))))
        shape.move(1.f, 0.f);


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

void GameState::initKeys() {

    std::ifstream file;

    file.open("../Config/mainMenuState_keys.ini");
    std::string keyName;
    std::string key;

    while(file >> keyName >> key)
        keyBinds[keyName] = supportedKeys->at(key);

    file.close();

    std::ifstream file2;

    file2.open("../Config/settingsState_keys.ini");

    while(file2 >> keyName >> key)
        keyBinds[keyName] = supportedKeys->at(key);

    file2.close();

}
