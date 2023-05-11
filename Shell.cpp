

#include "Shell.h"

Shell::Shell(unsigned short *typeOfSprite) : SpecialAbility(typeOfSprite) {

}

void Shell::update() {

    if (*typeOfSprite != IDLELEFT and *typeOfSprite != IDLERIGHT)
        timer.restart();

    if ((*typeOfSprite == IDLELEFT or *typeOfSprite == IDLERIGHT) and timer.getElapsedTime().asSeconds() > delay)
        status = INVINCIBLE;
    else status = NORMAL;
}
