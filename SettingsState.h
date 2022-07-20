#ifndef PLATFORMGAME_SETTINGSSTATE_H
#define PLATFORMGAME_SETTINGSSTATE_H

#include "State.h"
#include "GameState.h"
#include "Button.h"
#include "MainMenuState.h"
#include "headers.h"

class SettingsState : public State {

public:

    SettingsState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states);
    ~SettingsState() override = default;

    void update(const float &dt) override;
    void updateButtons();
    void updateMousePosition();
    void render(sf::RenderTarget &target) override;

private:

    std::map<std::string, std::unique_ptr<Button>> buttons;
    sf::Font font;
    sf::Vector2f mousePos;
    sf::RectangleShape background;

    void initButtons();




};


#endif //PLATFORMGAME_SETTINGSSTATE_H
