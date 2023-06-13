//
// Created by alessio on 23/04/23.
//

#ifndef PLATFORMGAME_NOSPECIALABILITY_H
#define PLATFORMGAME_NOSPECIALABILITY_H

#include "SpecialAbility.h"

class NoSpecialAbility : public SpecialAbility {
public:
    NoSpecialAbility();

    void update() override;
};


#endif //PLATFORMGAME_NOSPECIALABILITY_H
