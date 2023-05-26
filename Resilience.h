#ifndef PLATFORMGAME_RESILIENCE_H
#define PLATFORMGAME_RESILIENCE_H

#include "SpecialAbility.h"

class Resilience : public SpecialAbility {

public:
    explicit Resilience(unsigned short int *typeOfSprite);

    void update() override;
};


#endif //PLATFORMGAME_RESILIENCE_H
