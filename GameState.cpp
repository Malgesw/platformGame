#include "GameState.h"
#include "WalkingMovement.h"
#include "FlyingMovement.h"
#include "AutoWalking.h"
#include "AutoFlying.h"

GameState::GameState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
                     std::map<std::string, int> *supportedKeys) : State(window, states, ev, supportedKeys) {

    initKeys();


    font.loadFromFile("../Fonts/PAPYRUS.ttf");

    isPaused = false;

    pauseMenu = std::make_unique<PauseMenu>(window, font);
    pauseTime = 0.5f;
    pauseClock.restart();
    tileMap = std::make_unique<TileMap>(window);

    player = std::make_unique<GameCharacter>(sf::Vector2f (0.f,0.f),sf::Vector2f (50,50),tileMap->getWalls(),50,50);
    auto enemy= std::make_shared<GameCharacter>(sf::Vector2f(500.f,100.f),sf::Vector2f(50,50),tileMap->getWalls(),50,50);
    auto enemy2= std::make_shared<GameCharacter>(sf::Vector2f(500.f,100.f),sf::Vector2f(50,50),tileMap->getWalls(),50,50);
    std::string enemyName("enemy1");
    std::string enemyName2("enemy2");
    tileMap->addEnemy(enemy,enemyName);
    tileMap->addEnemy(enemy2,enemyName2);
    std::shared_ptr<Movement> autoMovement;
    std::shared_ptr<Movement> autoMovement2;
    autoMovement=std::make_shared<AutoWalking>( AutoWalking(10,sf::Vector2f (510.f,100.f),sf::Vector2f(50,50),tileMap->getWalls(),50,4));
    autoMovement2=std::make_shared<AutoFlying>( AutoFlying(10,sf::Vector2f (510.f,500.f),sf::Vector2f(50,50),tileMap->getWalls(),tileMap->getTileSize()));
    enemy->setMovement(autoMovement);
    enemy2->setMovement(autoMovement2);


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
        mainCharacterPos=player->getMovement()->getPosition();
        updatePlayerPos();
        player->update(dt,tileMap->getWalls(), window,mainCharacterPos);
        tileMap->update(dt,tileMap->getWalls(),window,mainCharacterPos);

    }





}

void GameState::updatePlayerPos() {

    player->getMovement()->setVelocity(player->getMovement()->getVelocity().x * 0.5f, player->getMovement()->getVelocity().y);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Left"))))
        player->getMovement()->moveLeft();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Right"))))
        player->getMovement()->moveRight();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Jump")))){

        player->getMovement()->moveUp();
    }
}

void GameState::render(sf::RenderTarget &target) {
    tileMap->renderMap(target);
    player->render(target);
    tileMap->renderEnemies(target);

    
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



