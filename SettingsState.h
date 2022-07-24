#ifndef PLATFORMGAME_SETTINGSSTATE_H
#define PLATFORMGAME_SETTINGSSTATE_H

#include "State.h"
#include "GameState.h"
#include "Button.h"
#include "TextField.h"
#include "headers.h"

class SettingsState : public State {

public:

    SettingsState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
                  std::map<std::string, int> *supportedKeys);
    ~SettingsState() override = default;

    void update(const float &dt) override;
    void updateButtons();
    void updateMousePosition();
    void updateTextFields();
    void updateKeys();
    void render(sf::RenderTarget &target) override;

private:

    std::map<std::string, std::unique_ptr<Button>> buttons;
    std::map<std::string, std::unique_ptr<TextField>> textFields;
    sf::Font font;
    sf::Vector2f mousePos;
    sf::RectangleShape background;

    void initButtons();
    void initTextFields();
    void initKeys() override;




};


#endif //PLATFORMGAME_SETTINGSSTATE_H
