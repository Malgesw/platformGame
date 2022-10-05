#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
                             std::map<std::string, int> *supportedKeys) : State(window, states, ev, supportedKeys) {

    font.loadFromFile("../Fonts/PAPYRUS.ttf");

    initKeys();
    initButtons();

    bgTexture.loadFromFile("../images/bg2fixed.png");

    background.setSize(sf::Vector2f(800.f,600.f));
    background.setTexture(&bgTexture);

    title.setFont(font);
    title.setCharacterSize(50);
    title.setString("Steamrush");
    title.setFillColor(sf::Color::White);
    title.setPosition(sf::Vector2f(270.f, 80.f));

    view = window->getView();
    view.setCenter(view.getSize()/2.f);

}

void MainMenuState::update(const float &dt) {

    checkForClose();
    if(!states->empty()) {
        window->setView(view);
        updateMousePosition();
        updateButtons();
    }

}

void MainMenuState::updateButtons() {

    for(auto &b : buttons)
        b.second->update(mousePos);

    if(buttons["PLAY"]->isPressed()) {
        try {
            states->push(std::make_unique<GameState>(window, states, textEvent, supportedKeys));
        }
        catch (std::runtime_error& error){
           if (strcmp(error.what(),"unsupported_keys")==0){
               std::cout<<"unsupported keys"<<std::endl;
           }
        }
    }

    if(buttons["SETTINGS"]->isPressed())
        states->push(std::make_unique<SettingsState>(window, states, textEvent, supportedKeys));

    if(buttons["EXIT"]->isPressed())
        states->pop();

}

void MainMenuState::render(sf::RenderTarget &target) {

    target.draw(background);
    target.draw(title);

    for(auto &b : buttons)
        b.second->render(target);

}

void MainMenuState::initButtons() {

    buttons["PLAY"] = std::make_unique<Button>(sf::Vector2f(200.f, 50.f), sf::Vector2f(295.f, 200.f),
                                               sf::Color(130, 130, 130, 200), "Play", font, 16,
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

    buttons["SETTINGS"] = std::make_unique<Button>(sf::Vector2f(200.f, 50.f), sf::Vector2f(295.f, 260.f),
                                               sf::Color(130, 130, 130, 200), "Settings", font, 16,
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

    buttons["EXIT"] = std::make_unique<Button>(sf::Vector2f(200.f, 50.f), sf::Vector2f(295.f, 320.f),
                                               sf::Color(130, 130, 130, 200), "Exit", font, 16,
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

}

void MainMenuState::initKeys() {

    std::ifstream file;

    file.open("../Config/mainMenuState_keys.ini");
    std::string keyName;
    std::string key;

    while(file >> keyName >> key)
        keyBinds[keyName] = supportedKeys->at(key);

    file.close();

}
