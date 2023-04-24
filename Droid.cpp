#include "Droid.h"

void Droid::use(GameCharacter &player) {
    player.saveOldComponents();
    player.setAnimation(std::move(animation));
    player.setMovement(std::move(movement));
    player.setEnergy(10);
    player.setDroidState(true);
}
