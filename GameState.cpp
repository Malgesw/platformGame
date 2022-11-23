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
    statusBar.setSize(sf::Vector2f(150,60.f));
    statusBar.setTexture(statusBarTexture);
    hpBar.setFillColor(sf::Color(40,223,90));
    energyBar.setFillColor(sf::Color(123,234,209));
    player = std::make_unique<GameCharacter>(50,50);
    std::unique_ptr<Movement> playerMovement=std::make_unique<WalkingMovement>(80,sf::Vector2f (50.f,50.f),sf::Vector2f (25,35),200);
    std::unique_ptr<Attack> playerAttack=std::make_unique<MeleeAttack>(sf::Vector2f (45.f,35.f),0.5f,1,49.f);
    auto playerAnimation=std::make_unique<Animation>(playerTexture, sf::Vector2i(5, 3), 0.3f, sf::Vector2f (35,35),true);
    playerAttack->attach(&achievementCounter);
    player->setAttack(std::move(playerAttack));
    player->setAnimation(std::move(playerAnimation));
    player->setMovement(std::move(playerMovement));
    tileMap = std::make_unique<TileMap>(*player);
    player->getMovement().addWalls(tileMap->getWalls());
    player->getAttack().addTargets(tileMap->getTargets());
    pauseMenu = std::make_unique<PauseMenu>(window, font, false);
    deathMenu = std::make_unique<PauseMenu>(window, font, true);
    deathMessage.setFont(font);
    deathMessage.setString("You died, little sussy baka!");
    deathMessage.setCharacterSize(20);
    deathMessage.setFillColor(sf::Color::White);
    deathMessage.setPosition(tileMap->getRoom()->getCamera().getSize()/3.f);

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
        pauseMenu->moveButton("CONTINUE", sf::Vector2f(tileMap->getRoom()->getCamera().getCenter().x - tileMap->getRoom()->getCamera().getSize().x/8.f,
                                                       tileMap->getRoom()->getCamera().getCenter().y - 2.f*tileMap->getRoom()->getCamera().getSize().y/5.f));
        pauseMenu->moveButton("EXIT_MENU", sf::Vector2f(tileMap->getRoom()->getCamera().getCenter().x - tileMap->getRoom()->getCamera().getSize().x/8.f,
                                                        tileMap->getRoom()->getCamera().getCenter().y - tileMap->getRoom()->getCamera().getSize().y/5.f));

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

        if (deathMenu->isButtonPressed("RESTART")) {
            death = false;
            tileMap->setCurrentRoom(0);
            player->getMovement().getCollisions().setPosition(tileMap->getRoom()->getDimX(), tileMap->getRoom()->getDimY());
            hpBar.setSize(sf::Vector2f (statusBar.getSize().x/1.5f,statusBar.getSize().y/4.6f));
            player->setHp(50);
        }

        if (deathMenu->isButtonPressed("EXIT_MENU")) {
            sf::sleep(sf::seconds(0.15f));
            states->pop();
        }

    }
    else {
        //std::cout<<"fps is "<<1/dt<<std::endl;
        if (dt > 0.1f) {
            updatePlayerPos();
            player->update(0.1f, tileMap->getWalls(), mainCharacterPos);
            tileMap->update(0.1f, *player, window);
            achievementCounter.update(tileMap->getRoom()->getCamera(), 0.1f);

        } else {
            updatePlayerPos();
            player->update(dt, tileMap->getWalls(), mainCharacterPos);
            tileMap->update(dt, *player, window);
            achievementCounter.update(tileMap->getRoom()->getCamera(), dt);

            //___________________UPDATING STATUS BAR

            statusBar.setPosition(tileMap->getRoom()->getCamera().getCenter()-tileMap->getRoom()->getCamera().getSize()/2.f);
            statusBar.setSize(sf::Vector2f(tileMap->getRoom()->getCamera().getSize().x/2.7f,tileMap->getRoom()->getCamera().getSize().y/5.f));
            hpBar.setPosition(statusBar.getPosition().x+statusBar.getSize().x/6.5f,statusBar.getPosition().y+statusBar.getSize().y/2.05f);
            hpBar.setSize(sf::Vector2f (statusBar.getSize().x/1.5f,statusBar.getSize().y/4.6f));
            energyBar.setPosition(statusBar.getPosition().x+statusBar.getSize().x/6.5f,statusBar.getPosition().y+statusBar.getSize().y/2.5f);
            energyBar.setSize(sf::Vector2f (statusBar.getSize().x/2.5f,statusBar.getSize().y/10.f));
            if(player->getHp() < 50) {
                if(hpBar.getSize().x > 0.f) {
                    death = false;
                    hpBar.setSize(sf::Vector2f(hpBar.getSize().x - static_cast<float>(50 - player->getHp()) * hpBar.getSize().x / 8.f,
                                               hpBar.getSize().y));
                }
                if(hpBar.getSize().x <= 0.f) {
                    death = true;
                    deathMessage.setPosition(tileMap->getRoom()->getCamera().getCenter().x - tileMap->getRoom()->getCamera().getSize().x/4.f,
                                             tileMap->getRoom()->getCamera().getCenter().y- tileMap->getRoom()->getCamera().getSize().y/3.f);
                }
            }
        }
    }
}
void GameState::updatePlayerPos() {

    if(textEvent.type==sf::Event::KeyReleased and textEvent.key.code==(sf::Keyboard::Key(keyBinds.at("Jump")))){
        keyReleased=true;
    }

    player->getMovement().setVelocity(player->getMovement().getVelocity().x * 0.5f, player->getMovement().getVelocity().y);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Left")))) {
        player->getMovement().moveLeft();
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Right")))) {
        player->getMovement().moveRight();
    }

    else if(player->getMovement().onGround()) {
        if (player->isFacingRight()) {
            player->getMovement().setSpriteType(IDLERIGHT);
        }
        else{
            player->getMovement().setSpriteType(IDLELEFT);
        }
    }


    //WHEN PLAYER JUMPS
    if(keyReleased and sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Jump")))){
        keyReleased=false;
        player->getMovement().moveUp();
        //JUMP AFTER IDLELEFT
        if (!player->isFacingRight()) {
            player->getMovement().setSpriteType(JUMPLEFT);
        }
        //MOVEMENT LEFT/RIGHT WHILE IN AIR
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Left")))) {
            player->getMovement().setSpriteType(JUMPLEFT);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Right")))) {
            player->getMovement().setSpriteType(JUMPRIGHT);
        }
    }

    //WHEN PLAYER SHOOTS
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keyBinds.at("Shoot")))){
        player->getAttack().hit();
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



