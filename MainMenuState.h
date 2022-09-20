#ifndef PLATFORMGAME_MAINMENUSTATE_H
#define PLATFORMGAME_MAINMENUSTATE_H

#include "State.h"
#include "GameState.h"
#include "SettingsState.h"
#include "Button.h"

class MainMenuState : public State {

public:

    MainMenuState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states, const sf::Event &ev,
                  std::map<std::string, int> *supportedKeys);
    ~MainMenuState() override = default;

    void update(const float &dt) override;
    void updateButtons();
    void render(sf::RenderTarget &target) override;


private:

    std::map<std::string, std::unique_ptr<Button>> buttons;
    sf::Font font;
    sf::RectangleShape background;
    sf::Texture bgTexture;
    sf::Text title;

    void initButtons();
    void initKeys() override;



};


#endif //PLATFORMGAME_MAINMENUSTATE_H
