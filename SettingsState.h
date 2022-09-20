#ifndef PLATFORMGAME_SETTINGSSTATE_H
#define PLATFORMGAME_SETTINGSSTATE_H

#include "State.h"
#include "GameState.h"
#include "Button.h"
#include "TextField.h"
#include "DropDownList.h"
#include "headers.h"

class SettingsState : public State {

public:

    SettingsState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
                  std::map<std::string, int> *supportedKeys);
    ~SettingsState() override = default;

    void update(const float &dt) override;
    void updateButtons();

    void updateTextFields();
    void updateKeys();
    void render(sf::RenderTarget &target) override;

private:

    std::map<std::string, std::unique_ptr<Button>> buttons;
    std::map<std::string, std::unique_ptr<TextField>> textFields;
    std::unique_ptr<DropDownList> dropDownList;
    sf::Font font;
    sf::RectangleShape background;
    sf::Texture bgTexture;

    void initButtons();
    void initTextFields();
    void initDropDownList();
    void initKeys() override;




};


#endif //PLATFORMGAME_SETTINGSSTATE_H
