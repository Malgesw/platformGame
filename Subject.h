//
// Created by alessio on 26/07/22.
//

#ifndef PLATFORMGAME_SUBJECT_H
#define PLATFORMGAME_SUBJECT_H

#include "Observer.h"

class Subject{
protected:
    virtual ~Subject()= default;

public:
    virtual void addObserver(Observer * o)=0;
    virtual void removeObserver(Observer * o)=0;
    virtual void notifyObservers () const=0;
};



#endif //PLATFORMGAME_SUBJECT_H
