#ifndef PLATFORMGAME_MAINMENUSTATE_H
#define PLATFORMGAME_MAINMENUSTATE_H

#include "State.h"
#include "GameState.h"
#include "Button.h"

class MainMenuState : public State {

public:

    MainMenuState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states);
    ~MainMenuState() override = default;

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


#endif //PLATFORMGAME_MAINMENUSTATE_H
