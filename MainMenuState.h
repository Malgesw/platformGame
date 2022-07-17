#ifndef PLATFORMGAME_MAINMENUSTATE_H
#define PLATFORMGAME_MAINMENUSTATE_H

#include "State.h"


class MainMenuState : public State {

public:

    MainMenuState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states);
    ~MainMenuState() override = default;

    void update(const float &dt) override;
    void render(sf::RenderTarget &target) override;


private:

    sf::RectangleShape shape;



};


#endif //PLATFORMGAME_MAINMENUSTATE_H
