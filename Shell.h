//
// Created by alessio on 23/04/23.
//

#ifndef PLATFORMGAME_SHELL_H
#define PLATFORMGAME_SHELL_H

#include "SpecialAbility.h"

class Shell : public SpecialAbility {
public:
    Shell(unsigned short int *typeOfSprite);

    void update() override;
};


#endif //PLATFORMGAME_SHELL_H
