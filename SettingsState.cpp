#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev) :
State(window, states, ev) {

    font.loadFromFile("/home/kaneki/CLionProjects/platformGame/Fonts/PAPYRUS.ttf");

    initButtons();
    initTextFields();

    background.setSize(static_cast<sf::Vector2f>(this->window->getSize()));
    background.setFillColor(sf::Color::Green);

}

void SettingsState::update(const float &dt) {

    updateMousePosition();
    checkForClose(); //FIXME : checkForClose() causes segmentation fault error
    updateButtons();
    updateTextFields();

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

    for(auto &t : textFields)
        t.second->render(target);

}

void SettingsState::updateTextFields() {

    if(textEvent.type == sf::Event::TextEntered){

        for(auto &t : textFields){

            if(t.second->contains(mousePos)){

                if(textEvent.text.unicode < 128){

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        t.second->setString("Space");
                    else{

                        sf::String string = static_cast<sf::String>(textEvent.text.unicode);
                        std::transform(string.begin(), string.end(), string.begin(), ::toupper);
                        t.second->setString(string);

                    }
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                    t.second->clear();

            }
        }
    }
}

void SettingsState::initButtons() {

    buttons["EXIT"] = std::make_unique<Button>(sf::Vector2f(300.f, 100.f), sf::Vector2f(200.f, 350.f),
                                               sf::Color(70, 70, 70, 200), "Exit", font, 16,
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

}

void SettingsState::initTextFields() {

    textFields["LEFT"] = std::make_unique<TextField>(sf::Vector2f(50.f, 50.f), sf::Vector2f(100.f, 100.f), 22,
                                                     sf::Vector2f(125.f, 110.f), "Left", sf::Vector2f(40.f, 110.f),
                                                     &font, sf::Color(31, 157, 115, 255), sf::Color::Red);

    textFields["RIGHT"] = std::make_unique<TextField>(sf::Vector2f(50.f, 50.f), sf::Vector2f(100.f, 160.f), 22,
                                                     sf::Vector2f(125.f, 170.f), "Right", sf::Vector2f(40.f, 170.f),
                                                     &font, sf::Color(31, 157, 115, 255), sf::Color::Red);

    textFields["JUMP"] = std::make_unique<TextField>(sf::Vector2f(50.f, 50.f), sf::Vector2f(100.f, 220.f), 22,
                                                     sf::Vector2f(100.f, 230.f), "Jump", sf::Vector2f(40.f, 230.f),
                                                     &font, sf::Color(31, 157, 115, 255), sf::Color::Red);

    textFields["SHOOT"] = std::make_unique<TextField>(sf::Vector2f(50.f, 50.f), sf::Vector2f(100.f, 280.f), 22,
                                                     sf::Vector2f(125.f, 290.f), "Shoot", sf::Vector2f(35.f, 290.f),
                                                     &font, sf::Color(31, 157, 115, 255), sf::Color::Red);

}
