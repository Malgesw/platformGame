#include "GameState.h"
#include "WalkingMovement.h"
#include "FlyingMovement.h"
#include "AutoWalking.h"
#include "AutoFlying.h"
#include "MeleeAttack.h"



GameState::GameState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
                     std::map<std::string, int> *supportedKeys) : State(window, states, ev, supportedKeys){

    initKeys();
    playerTexture=new sf::Texture;
    playerTexture->loadFromFile("../images/playerSprite.png");
    playerTexture->setSmooth(true);
    font.loadFromFile("../Fonts/PAPYRUS.ttf");
    isPaused = false;
    pauseTime = 0.5f;
    pauseClock.restart();
    player = std::make_unique<GameCharacter>(50,50);

    std::unique_ptr<Movement> playerMovement=std::make_unique<WalkingMovement>(80,sf::Vector2f (50.f,50.f),sf::Vector2f (35,35),200);
    std::unique_ptr<Attack> playerAttack=std::make_unique<MeleeAttack>(sf::Vector2f (50.f,50.f)*1.5f,0.5f,1,49.f);
    auto playerAnimation=std::make_unique<Animation>(playerTexture, sf::Vector2u(5, 3), 0.3f, sf::Vector2f (50.f,50.f), sf::Vector2f (35,35));
    player->setAttack(std::move(playerAttack));
    player->setAnimation(std::move(playerAnimation));
    player->setMovement(std::move(playerMovement));
    tileMap = std::make_unique<TileMap>(*player);
    player->getMovement().addWalls(tileMap->getWalls());
    player->getAttack().addTargets(tileMap->getTargets());
    pauseMenu = std::make_unique<PauseMenu>(window, font);
}

void GameState::update(const float &dt) {
    updateMousePosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("CLOSE"))) && isReady()) {
        pauseClock.restart();
        if (!isPaused)
            isPaused = true;
        else
            isPaused = false;
    }

    if (isPaused) {
        pauseMenu->update(mousePos);
        pauseMenu->moveButton("CONTINUE", sf::Vector2f(tileMap->getRoom()->getCamera().getCenter().x-20.f,
                                                       tileMap->getRoom()->getCamera().getCenter().y-120.f));
        pauseMenu->moveButton("EXIT_MENU", sf::Vector2f(tileMap->getRoom()->getCamera().getCenter().x-20.f,
                                                        tileMap->getRoom()->getCamera().getCenter().y-60.f));

        if (pauseMenu->isButtonPressed("CONTINUE"))
            isPaused = false;

        if (pauseMenu->isButtonPressed("EXIT_MENU")) {
            sf::sleep(sf::seconds(0.1f));
            states->pop();
        }

    } else {
        if (firstframe) {
            firstframe = false;
            tileMap->update(0, *player, window);
            updatePlayerPos();
            player->update(0, tileMap->getWalls(), window, mainCharacterPos);
            player->getMovement().setBarriers(tileMap->getWalls());
        } else {
            updatePlayerPos();
            player->update(dt, tileMap->getWalls(), window, mainCharacterPos);
            player->getMovement().setBarriers(tileMap->getWalls());
            tileMap->update(dt, *player, window);

        }
    }
}

void GameState::updatePlayerPos() {

    player->getMovement().setVelocity(player->getMovement().getVelocity().x * 0.5f, player->getMovement().getVelocity().y);

    //WHEN PLAYER IS ON GROUND
    if(player->getMovement().onGround()) {
        if (player->isFacingRight()) {
            player->getMovement().setSpriteType(IDLERIGHT);
        }
        else{
            player->getMovement().setSpriteType(IDLELEFT);
        }
    }

    //WHEN PLAYER MOVES LEFT/RIGHT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Left"))))
        player->getMovement().moveLeft();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Right"))))
        player->getMovement().moveRight();

    //WHEN PLAYER JUMPS
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Jump")))){
        player->getMovement().moveUp();
        //JUMP AFTER IDLELEFT
        if (!player->isFacingRight()) {
            player->getMovement().setSpriteType(JUMPLEFT);
        }
        //MOVEMENT LEFT/RIGHT WHILE IN AIR
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Left"))))
            player->getMovement().setSpriteType(JUMPLEFT);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Right"))))
            player->getMovement().setSpriteType(JUMPRIGHT);;
    }
    //WHEN PLAYER SHOOTS
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Shoot")))){
        player->getAttack().hit();
    }
}

void GameState::render(sf::RenderTarget &target) {
    tileMap->render(target);
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

GameState::~GameState() {

    delete playerTexture;
}



