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

    player = std::make_unique<GameCharacter>(sf::Vector2f (300.f,100.f),sf::Vector2f(30,60),tileMap->getWalls());
    jumped = false;

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
    else{
        updatePlayerPos();
        player->update(dt,tileMap->getWalls(), window);
    }

}

void GameState::updatePlayerPos() {

    player->getMovement()->setVelocity(player->getMovement()->getVelocity().x * 0.5f, player->getMovement()->getVelocity().y);

    if(player->getMovement()->onGround())
        player->getMovement()->setSpriteType(IDLE_SPRITE);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Left"))))
        player->getMovement()->moveLeft();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Right"))))
        player->getMovement()->moveRight();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Jump")))){

        player->getMovement()->moveUp();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Left"))))
            player->getMovement()->setSpriteType(JUMPLEFT);
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



