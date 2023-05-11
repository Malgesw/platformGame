#include "Droid.h"

void Droid::use(GameCharacter &player) {
    player.saveOldComponents();
    player.setAnimation(std::move(playerAnimation));
    player.setMovement(std::move(playerMovement));
    player.setAttack(std::move(playerAttack));
    player.setEnergy(player.getStartEnergy());
    player.setDroidState(true);
}
