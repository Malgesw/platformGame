#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow *window, sf::Font &font, bool isDeathMenu) : font(font), isDeathMenu(isDeathMenu) {

    initButtons();

    background.setSize(static_cast<sf::Vector2f>(window->getSize()));
    background.setFillColor(sf::Color(sf::Color(20, 20, 20, 100)));

}

void PauseMenu::update(sf::Vector2f &mousePos) {

    for(auto &b : buttons)
        b.second->update(mousePos);

}

void PauseMenu::render(sf::RenderTarget &target) {

    target.draw(background);

    for(auto &b : buttons)
        b.second->render(target);

}

bool PauseMenu::isButtonPressed(const std::string &button) {

    if(buttons[button]->isPressed())
        return true;
    else
        return false;

}

void PauseMenu::initButtons() {

    if(isDeathMenu)
        buttons["RESTART"] = std::make_unique<Button>(sf::Vector2f(90.f, 30.f), sf::Vector2f(300.f, 50.f),
                                                       sf::Color(70, 70, 70, 200), "Restart", font, 14,
                                                       sf::Color(150, 150, 150, 255),
                                                       sf::Color(20, 20, 20, 200));
    else
        buttons["CONTINUE"] = std::make_unique<Button>(sf::Vector2f(90.f, 30.f), sf::Vector2f(300.f, 50.f),
                                               sf::Color(70, 70, 70, 200), "Continue", font, 14,
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

    buttons["EXIT_MENU"] = std::make_unique<Button>(sf::Vector2f(90.f, 30.f), sf::Vector2f(300.f, 110.f),
                                               sf::Color(70, 70, 70, 200), "Exit to menu", font, 14,
                                               sf::Color(150, 150, 150, 255),
                                               sf::Color(20, 20, 20, 200));

}

void PauseMenu::moveButton(const std::string& buttonName, sf::Vector2f newPos) {

    buttons[buttonName]->setPosition(newPos);

}
