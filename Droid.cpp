#include "Droid.h"

void Droid::use(GameCharacter &player) {
    player.setAnimation(std::move(animation));
    player.setMovement(std::move(movement));
}
