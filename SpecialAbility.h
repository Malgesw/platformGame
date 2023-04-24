//
// Created by alessio on 23/04/23.
//

#ifndef PLATFORMGAME_SPECIALABILITY_H
#define PLATFORMGAME_SPECIALABILITY_H

#include "spriteType.h"

enum statusType {
    NORMAL = 0, INVINCIBLE = 1
};

class SpecialAbility {
public:
    explicit SpecialAbility(unsigned short int *typeOfSprite);

    unsigned short int getStatus() const;

protected:
    unsigned short int *typeOfSprite;
    unsigned short int status = 0;

    virtual void update() = 0;
};


#endif //PLATFORMGAME_SPECIALABILITY_H
