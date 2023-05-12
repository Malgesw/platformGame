#include "GameState.h"


GameState::GameState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
                     std::map<std::string, int> *supportedKeys) : State(window, states, ev, supportedKeys){


    initKeys();
    statusBarTexture= new sf::Texture;
    playerTexture=new sf::Texture;
    playerTexture->loadFromFile("./images/playerSheet.png");
    playerTexture->setSmooth(true);
    statusBarTexture->loadFromFile("./images/hp bar.png");
    statusBarTexture->setSmooth(true);

    font.loadFromFile("./Fonts/PAPYRUS.ttf");
    achievementCounter.setFont(font);
    isPaused = false;
    pauseTime = 0.5f;
    pauseClock.restart();
    statusBar.setSize(sf::Vector2f(150, 60.f));
    statusBar.setTexture(statusBarTexture);
    hpBar.setFillColor(sf::Color(40, 223, 90));
    energyBar.setFillColor(sf::Color(123, 234, 209));
    player = std::make_unique<GameCharacter>(startPlayerLife, startPlayerEnergy);
    std::unique_ptr<Movement> playerMovement = std::make_unique<GlidingMovement>(380, startPlayerPosition,
                                                                                 sf::Vector2f(120, 126), 2000,
                                                                                 player->spritePointer());
    //std::unique_ptr<Attack> playerAttack=std::make_unique<MeleeAttack>(sf::Vector2f (216.f,126.f),0.5f,1,200.f,player->spritePointer());
    std::unique_ptr<Attack> playerAttack = std::make_unique<StarRangedAttack>(sf::Vector2f(40.f, 40.f), 400.5f, 0.5f, 1,
                                                                              150.f, player->spritePointer(), true);
    //std::unique_ptr<Attack> playerAttack = std::make_unique<NoAttack>();

    auto playerAnimation = std::make_unique<Animation>(playerTexture, sf::Vector2i(5, 3), 0.3f, sf::Vector2f(168, 126),
                                                       true, player->spritePointer());
    playerAttack->attach(&achievementCounter);
    player->setAttack(std::move(playerAttack));
    player->setAnimation(std::move(playerAnimation));
    player->setMovement(std::move(playerMovement));
    tileMap = std::make_unique<TileMap>(*player);
    player->addWalls(tileMap->getWalls());
    player->addTargets(tileMap->getTargets());
    player->attach(&achievementCounter);
    pauseMenu = std::make_unique<PauseMenu>(window, font, false);
    deathMenu = std::make_unique<PauseMenu>(window, font, true);
    deathMessage.setFont(font);
    deathMessage.setString("You died, little sussy baka!");
    deathMessage.setCharacterSize(20);
    deathMessage.setFillColor(sf::Color::White);
    deathMessage.setPosition(tileMap->getRoom()->getCamera().getSize() / 3.f);

}

void GameState::update(const float &dt) {
    updateMousePosition();
    float currentPlayerLife;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("CLOSE"))) && isReady()) {
        pauseClock.restart();
        if (!isPaused)
            isPaused = true;
        else
            isPaused = false;
    }

    if (isPaused) {
        pauseMenu->update(mousePos);
        pauseMenu->moveButton("CONTINUE", sf::Vector2f(tileMap->getRoom()->getCamera().getCenter().x - tileMap->getRoom()->getCamera().getSize().x/8.f,
                                                       tileMap->getRoom()->getCamera().getCenter().y - 2.f*tileMap->getRoom()->getCamera().getSize().y/5.f));
        pauseMenu->moveButton("EXIT_MENU", sf::Vector2f(tileMap->getRoom()->getCamera().getCenter().x - tileMap->getRoom()->getCamera().getSize().x/8.f,
                                                        tileMap->getRoom()->getCamera().getCenter().y - tileMap->getRoom()->getCamera().getSize().y/5.f));
        pauseMenu->resizeButton("CONTINUE",sf::Vector2f(tileMap->getRoom()->getCamera().getSize().x/4.f,tileMap->getRoom()->getCamera().getSize().y/8.f));
        pauseMenu->resizeButton("EXIT_MENU",sf::Vector2f (tileMap->getRoom()->getCamera().getSize().x/4.f,tileMap->getRoom()->getCamera().getSize().y/8.f));


        if (pauseMenu->isButtonPressed("CONTINUE"))
            isPaused = false;

        if (pauseMenu->isButtonPressed("EXIT_MENU")) {
            sf::sleep(sf::seconds(0.15f));
            states->pop();
        }

    }
    else if(death){
        deathMenu->update(mousePos);
        deathMenu->moveButton("RESTART", sf::Vector2f(tileMap->getRoom()->getCamera().getCenter().x-tileMap->getRoom()->getCamera().getSize().x/10.f,
                                                       tileMap->getRoom()->getCamera().getCenter().y-tileMap->getRoom()->getCamera().getSize().y/5.f));
        deathMenu->moveButton("EXIT_MENU", sf::Vector2f(tileMap->getRoom()->getCamera().getCenter().x-tileMap->getRoom()->getCamera().getSize().x/10.f,
                                                        tileMap->getRoom()->getCamera().getCenter().y));
        deathMenu->resizeButton("RESTART",sf::Vector2f (tileMap->getRoom()->getCamera().getSize().x/4.f,tileMap->getRoom()->getCamera().getSize().y/8.f));
        deathMenu->resizeButton("EXIT_MENU",sf::Vector2f (tileMap->getRoom()->getCamera().getSize().x/4.f,tileMap->getRoom()->getCamera().getSize().y/8.f));



        if (deathMenu->isButtonPressed("RESTART")) {
            death = false;
            tileMap->setCurrentRoom(0);
            tileMap->clearEnemies();
            tileMap->clearItems();
            tileMap->spawnEnemies(*player); //after every restart, the map is cleared and enemies are respawned
            tileMap->placeItems(*player); //after every restart, the map is cleared and items are regenerated
            player->setPosition(startPlayerPosition.x, startPlayerPosition.y);
            player->clearWalls();
            player->addWalls(tileMap->getRoom()->getWalls());
            player->clearTargets();
            player->addTargets(tileMap->getRoom()->getTargets());
            hpBar.setSize(sf::Vector2f(statusBar.getSize().x / 1.5f, statusBar.getSize().y / 4.6f));
            player->setHp(startPlayerLife);
            player->setEnergy(0.f);
        }

        if (deathMenu->isButtonPressed("EXIT_MENU")) {
            sf::sleep(sf::seconds(0.15f));
            states->pop();
        }

    }
    else {
        //std::cout<<"fps is "<<1/dt<<std::endl;
        currentPlayerLife = player->getHp();
        if (invincibilityTimer.getElapsedTime().asSeconds() > invincibilityTime) {
            isInvincible = false;
        }

        if (dt > 0.05f) {
            updatePlayerPos();
            player->update(0.05f, tileMap->getWalls(), mainCharacterPos);
            tileMap->update(0.05f, *player, window);
            if (isInvincible)
                player->setHp(currentPlayerLife);
            else if (currentPlayerLife < player->getHp()) {
                isInvincible = true;
                invincibilityTimer.restart();
            }

            achievementCounter.update(tileMap->getRoom()->getCamera(), 0.1f);

        } else {
            updatePlayerPos();
            player->update(dt, tileMap->getWalls(), mainCharacterPos);
            tileMap->update(dt, *player, window);
            if (isInvincible) {
                player->setHp(currentPlayerLife);

            } else if (currentPlayerLife > player->getHp()) {
                isInvincible = true;
                invincibilityTimer.restart();
            }
            achievementCounter.update(tileMap->getRoom()->getCamera(), dt);

            //___________________UPDATING STATUS BAR

            statusBar.setPosition(
                    tileMap->getRoom()->getCamera().getCenter() - tileMap->getRoom()->getCamera().getSize() / 2.f);
            statusBar.setSize(sf::Vector2f(tileMap->getRoom()->getCamera().getSize().x / 2.7f,
                                           tileMap->getRoom()->getCamera().getSize().y / 5.f));
            hpBar.setPosition(statusBar.getPosition().x + statusBar.getSize().x / 6.5f,
                              statusBar.getPosition().y + statusBar.getSize().y / 2.05f);
            hpBar.setSize(sf::Vector2f(statusBar.getSize().x / 1.5f, statusBar.getSize().y / 4.6f));
            energyBar.setPosition(statusBar.getPosition().x + statusBar.getSize().x / 6.5f,
                                  statusBar.getPosition().y + statusBar.getSize().y / 2.5f);
            energyBar.setSize(sf::Vector2f(statusBar.getSize().x / 2.5f, statusBar.getSize().y / 10.f));

            if (player->getHp() > 0) {
                death = false;
                hpBar.setSize(sf::Vector2f(
                        (static_cast<float>(player->getHp()) / static_cast<float>(startPlayerLife)) * hpBar.getSize().x,
                        hpBar.getSize().y));
            }
            if (player->getEnergy() > -1) {

                energyBar.setSize(
                        sf::Vector2f(static_cast<float>(player->getEnergy() / maxPlayerEnergy) * energyBar.getSize().x,
                                     energyBar.getSize().y));
            }
            if (player->getHp() <= 0) {
                death = true;
                deathMessage.setPosition(tileMap->getRoom()->getCamera().getCenter().x -
                                         tileMap->getRoom()->getCamera().getSize().x / 8.5f,
                                         tileMap->getRoom()->getCamera().getCenter().y -
                                         tileMap->getRoom()->getCamera().getSize().y / 3.f);
                deathMessage.setCharacterSize(
                        static_cast<unsigned int>(2.f * tileMap->getRoom()->getCamera().getSize().y / 45.f));
            }


        }
    }
}
void GameState::updatePlayerPos() {

    if(textEvent.type==sf::Event::KeyReleased and textEvent.key.code==(sf::Keyboard::Key(keyBinds.at("Jump")))){
        keyReleased=true;
    }

    player->setVelocity(player->getVelocity().x * 0.5f, player->getVelocity().y);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Left")))) {
        player->moveLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Right")))) {
        player->moveRight();
    }

    //WHEN PLAYER JUMPS

    if (keyReleased and sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Jump")))) {
        keyReleased = false;
        player->moveUp();
    }

    //WHEN PLAYER SHOOTS
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Shoot")))){
        player->hit();
    }
}

void GameState::render(sf::RenderTarget &target) {

    tileMap->render(target);
    achievementCounter.render(target);
    target.draw(energyBar);
    if(!death)
        target.draw(hpBar);
    target.draw(statusBar);
    player->render(target);

    if(death) {
        deathMenu->render(target);
        target.draw(deathMessage);
    }
    else if(isPaused)
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
    file.open("./Config/mainMenuState_keys.ini");
    std::string keyName;
    std::string key;

    while(file >> keyName >> key)
        keyBinds[keyName] = supportedKeys->at(key);

    file.close();
    std::ifstream file2;
    file2.open("./Config/settingsState_keys.ini");

    while(file2 >> keyName >> key) {
        try {
            keyBinds[keyName] = supportedKeys->at(key);
        }
        catch (std::exception &problem) {
            throw std::runtime_error("unsupported_keys");
        }
    }

        bool noMisMatchFound=true;
        auto i= keyBinds.begin();
        auto j= keyBinds.begin();
        while(noMisMatchFound and i!=--keyBinds.end()){
            j=i;
            j++;
            while(noMisMatchFound and j!=keyBinds.end()){
                if((*i).second==(*j).second)
                    noMisMatchFound=false;
                else
                    j++;
            }
            i++;
        }

        if(!noMisMatchFound)
            throw std::runtime_error("unsupported_keys");


    file2.close();
}

GameState::~GameState() {

    delete playerTexture;
}



