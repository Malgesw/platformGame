#ifndef PLATFORMGAME_DROID_H
#define PLATFORMGAME_DROID_H

#include "Item.h"


class Droid : public Item {

public:

    Droid(std::unique_ptr<Animation> animation, std::unique_ptr<Movement> movement, std::unique_ptr<Attack> attack,
          std::unique_ptr<SpecialAbility> specialAbility,
          sf::Vector2f size, sf::Vector2f position, std::unique_ptr<Animation> itemAnimation) : playerAnimation(
            std::move(animation)), playerAttack(std::move(attack)), playerMovement(std::move(movement)),
                                                                                                playerSpecialAbility(
                                                                                                        std::move(
                                                                                                                specialAbility)),
                                                                                                Item(size, position,
                                                                                                     std::move(
                                                                                                             itemAnimation)) {
    }

    void use(GameCharacter &player) override;

private:
    std::unique_ptr<Movement> playerMovement;
    std::unique_ptr<Attack> playerAttack;
    std::unique_ptr<Animation> playerAnimation;
    std::unique_ptr<SpecialAbility> playerSpecialAbility;
};


#endif //PLATFORMGAME_DROID_H
