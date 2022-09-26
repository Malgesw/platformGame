//
// Created by alessio on 26/09/22.
//

#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(sf::Vector2f size, float speed, int hitDamage, float knockback) : Attack(size, speed,
                                                                                                  hitDamage,
                                                                                                  knockback) {
}


void MeleeAttack::hit() {

    if (cooldown.getElapsedTime().asSeconds()>attackSpeed) {

        cooldown.restart();

        auto i= targets.begin();

        while (i!=targets.end()) {
            auto currentTarget=*i;
            bool enemyCancelled=false;

            if (hitBox.getGlobalBounds().intersects(currentTarget.getHitbox().getGlobalBounds())) {


                sf::Vector2f knockbackDirection;
                knockbackDirection.x= (currentTarget.getHitbox().getPosition().x - hitBox.getPosition().x) /
                                      std::abs(currentTarget.getHitbox().getPosition().x - hitBox.getPosition().x);
                knockbackDirection.y= (currentTarget.getHitbox().getPosition().y - hitBox.getPosition().y) /
                                      std::abs(currentTarget.getHitbox().getPosition().y - hitBox.getPosition().y);

                if(currentTarget.getHp()<=damage){

                    targets.erase(i++);
                    enemyCancelled=true;
                }

                currentTarget.receiveDamage(knockbackDirection * knockbackDistance, damage);

            }
            if(not enemyCancelled){
                i++;
            }

        }
    }
}

