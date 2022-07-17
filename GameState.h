#ifndef PLATFORMGAME_GAMESTATE_H
#define PLATFORMGAME_GAMESTATE_H

#include "State.h"


class GameState : public State {

public:

    GameState(sf::RenderWindow *window, std::stack<std::unique_ptr<State>> *states);
    ~GameState() override = default;

    void update(const float &dt) override;
    void render(sf::RenderTarget &target) override;

private:

    sf::RectangleShape shape;

};


#endif //PLATFORMGAME_GAMESTATE_H
