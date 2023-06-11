

#ifndef PLATFORMGAME_SPECIALATTACK_H
#define PLATFORMGAME_SPECIALATTACK_H

#include "MeleeAttack.h"

class SpecialAttack : public SpecialAbility, public MeleeAttack {
    void update() override;
};


#endif //PLATFORMGAME_SPECIALATTACK_H
