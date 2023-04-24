#include "Droid.h"

void Droid::use(GameCharacter &player) {
    player.saveOldComponents();
    player.setAnimation(std::move(animation));
    player.setMovement(std::move(movement));
    player.setEnergy(player.getStartEnergy());
    player.setDroidState(true);
}
