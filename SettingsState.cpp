#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states) : State(window, states) {

    font.loadFromFile("/home/kaneki/CLionProjects/platformGame/Fonts/PAPYRUS.ttf");
    initButtons();

    background.setSize(static_cast<sf::Vector2f>(this->window->getSize()));
    background.setFillColor(sf::Color::Green);

}

void SettingsState::update(const float &dt) {

    updateMousePosition();
    checkForClose(); //FIXME : checkForClose() causes segmentation fault error
    updateButtons();

}

void SettingsState::updateButtons() {

    for(auto &b : buttons)
        b.second->update(mousePos);

    if(buttons["EXIT"]->isPressed())
        states->pop();

}

void SettingsState::updateMousePosition() {

    mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

}

void SettingsState::render(sf::RenderTarget &target) {

    target.draw(background);

    for(auto &b : buttons)
        b.second->render(target);

}

void SettingsState::initButtons() {

    buttons["EXIT"] = std::make_unique<Button>(sf::Vector2f(300.f, 100.f), sf::Vector2f(200.f, 350.f),
                                               sf::Color(70, 70, 70, 200), "Exit", font, 16,
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

}
