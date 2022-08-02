#include "GameState.h"
#include "WalkingMovement.h"

GameState::GameState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
                     std::map<std::string, int> *supportedKeys) : State(window, states, ev, supportedKeys) {

    initKeys();


    font.loadFromFile("../Fonts/PAPYRUS.ttf");

    isPaused = false;

    pauseMenu = std::make_unique<PauseMenu>(window, font);
    pauseTime = 0.5f;
    pauseClock.restart();
    tileMap = std::make_unique<TileMap>(window);
    player = std::make_shared<GameCharacter>(sf::Vector2f (100.f,75.f),sf::Vector2f (0,0));

}

void GameState::update(const float &dt) {

    mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

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
    else{
        updatePlayerPos();
        player->update(dt,tileMap->getWalls(), window);
    }





}

void GameState::updatePlayerPos() {

    player->getMovement()->setVelocity(player->getMovement()->getVelocity().x * 0.5f, player->getMovement()->getVelocity().y);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Left"))))
        player->getMovement()->setVelocity(player->getMovement()->getVelocity().x - player->getMovement()->getSpeed(), player->getMovement()->getVelocity().y);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Right"))))
        player->getMovement()->setVelocity(player->getMovement()->getVelocity().x + player->getMovement()->getSpeed(), player->getMovement()->getVelocity().y);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Jump"))) && dynamic_cast<WalkingMovement*>(player->getMovement())->getJump()){

        dynamic_cast<WalkingMovement*>(player->getMovement())->setJump(false);
        player->getMovement()->setVelocity(player->getMovement()->getVelocity().x, -sqrtf(2.f* 981.f * dynamic_cast<WalkingMovement*>(player->getMovement())->getJumpHeight()));
    }
}

void GameState::render(sf::RenderTarget &target) {
    tileMap->renderMap(target);
    player->render(target);

    
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



