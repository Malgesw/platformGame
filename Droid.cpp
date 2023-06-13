#include "Droid.h"

void Droid::use(GameCharacter &player) {
    playerMovement->clearWalls();
    playerMovement->addWalls(player.getWalls());
    playerAttack->clearTargets();
    playerAttack->addTargets(player.getTargets());
    if (!player.savedComponentsPresent())
        player.saveOldComponents();
    player.setAnimation(std::move(playerAnimation));
    player.setMovement(std::move(playerMovement));
    player.setAttack(std::move(playerAttack));
    player.setSpecialAbility(std::move(playerSpecialAbility));
    player.setEnergy(player.getStartEnergy());
    player.setDroidState(true);
}
