//
// Created by alessio on 23/04/23.
//

#include "Shell.h"

Shell::Shell(unsigned short *typeOfSprite) : SpecialAbility(typeOfSprite) {

}

void Shell::update() {
    if (*typeOfSprite == IDLELEFT or *typeOfSprite == IDLERIGHT)status = INVINCIBLE;
    else status = NORMAL;
}
