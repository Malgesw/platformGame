//
// Created by alessio on 23/04/23.
//

#ifndef PLATFORMGAME_SHELL_H
#define PLATFORMGAME_SHELL_H
#include "headers.h"
#include "SpecialAbility.h"

class Shell : public SpecialAbility {
public:
    explicit Shell(unsigned short int *typeOfSprite);

    void update() override;

    sf::Clock timer;

    const float delay = 0.2f;
};


#endif //PLATFORMGAME_SHELL_H
