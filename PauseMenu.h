#ifndef PLATFORMGAME_PAUSEMENU_H
#define PLATFORMGAME_PAUSEMENU_H

#include "headers.h"
#include "Button.h"


class PauseMenu {

public:

    PauseMenu(sf::RenderWindow *window, sf::Font &font, bool isDeathMenu);
    ~PauseMenu() = default;

    void update(sf::Vector2f &mousePos);
    void render(sf::RenderTarget &target);
    bool isButtonPressed(const std::string &button);
    void moveButton(const std::string& buttonName, sf::Vector2f newPos);
    void resizeButton(const std::string& buttonName, sf::Vector2f newSize);

private:

    std::map<std::string, std::unique_ptr<Button>> buttons;
    sf::Font &font;
    sf::RectangleShape background;
    bool isDeathMenu = false;

    void initButtons();



};


#endif //PLATFORMGAME_PAUSEMENU_H
