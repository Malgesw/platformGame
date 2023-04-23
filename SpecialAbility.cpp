//
// Created by alessio on 23/04/23.
//

#include "SpecialAbility.h"

SpecialAbility::SpecialAbility(unsigned short *typeOfSprite) : typeOfSprite(typeOfSprite) {

}

unsigned short int SpecialAbility::getStatus() const {
    return status;
}
