//
// Created by alessio on 06/03/23.
//

#include "NoMovement.h"

NoMovement::NoMovement(sf::Vector2f startPosition, sf::Vector2f size, unsigned short *typeOfSprite) : Movement(0.f,
                                                                                                               startPosition,
                                                                                                               size,
                                                                                                               'N',
                                                                                                               typeOfSprite,
                                                                                                               false) {

}
