//
// Created by alessio on 10/03/23.
//

#include "InvalidComponent.h"


InvalidComponent::InvalidComponent(const GameCharacter &faultyCharacter, unsigned short faultyComponent) :
        faultyCharacter(faultyCharacter), faultyComponent(faultyComponent) {

}

const GameCharacter &InvalidComponent::getFaultyCharacter() const {
    return faultyCharacter;
}

unsigned short InvalidComponent::getFaultyComponent() const {
    return faultyComponent;
}
