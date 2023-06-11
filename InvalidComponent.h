//
// Created by alessio on 10/03/23.
//

#ifndef PLATFORMGAME_INVALIDCOMPONENT_H
#define PLATFORMGAME_INVALIDCOMPONENT_H

#include "headers.h"

class GameCharacter;

class InvalidComponent : public std::exception {
private:
    const GameCharacter &faultyCharacter;
    unsigned short faultyComponent;

public:
    InvalidComponent(const GameCharacter &faultyCharacter, unsigned short faultyComponent);

    const GameCharacter &getFaultyCharacter() const;

    unsigned short getFaultyComponent() const;

};


#endif //PLATFORMGAME_INVALIDCOMPONENT_H
