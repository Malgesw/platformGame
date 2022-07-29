#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
                             std::map<std::string, int> *supportedKeys) : State(window, states, ev, supportedKeys) {

    font.loadFromFile("../Fonts/PAPYRUS.ttf");

    initKeys();
    initButtons();

    background.setSize(static_cast<sf::Vector2f>(this->window->getSize()));
    background.setFillColor(sf::Color::Green);

}

void MainMenuState::update(const float &dt) {

    checkForClose();
    if(!states->empty()) {
        updateMousePosition();
        updateButtons();
    }

}

void MainMenuState::updateButtons() {

    for(auto &b : buttons)
        b.second->update(mousePos);

    if(buttons["PLAY"]->isPressed())
        states->push(std::make_unique<GameState>(window, states, textEvent, supportedKeys));

    if(buttons["SETTINGS"]->isPressed())
        states->push(std::make_unique<SettingsState>(window, states, textEvent, supportedKeys));

    if(buttons["EXIT"]->isPressed()) {

        std::ofstream file;
        std::ifstream file2;
        std::string a, b;
        file.open("../Config/settingsState_keys.ini");
        file2.open("../Config/settingsState_keys.ini");
        while(file2 >> a >> b){
            file << " ";
        }
        file2.close();
        file.close();

        states->pop();
    }

}

void MainMenuState::updateMousePosition() {

    mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

}

void MainMenuState::render(sf::RenderTarget &target) {

    target.draw(background);

    for(auto &b : buttons)
        b.second->render(target);

}

void MainMenuState::initButtons() {

    buttons["PLAY"] = std::make_unique<Button>(sf::Vector2f(300.f, 100.f), sf::Vector2f(200.f, 50.f),
                                               sf::Color(70, 70, 70, 200), "Play", font, 16,
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

    buttons["SETTINGS"] = std::make_unique<Button>(sf::Vector2f(300.f, 100.f), sf::Vector2f(200.f, 250.f),
                                               sf::Color(70, 70, 70, 200), "Settings", font, 16,
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

    buttons["EXIT"] = std::make_unique<Button>(sf::Vector2f(300.f, 100.f), sf::Vector2f(200.f, 450.f),
                                               sf::Color(70, 70, 70, 200), "Exit", font, 16,
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
