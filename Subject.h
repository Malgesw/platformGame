//
// Created by alessio on 02/10/22.
//

#ifndef PLATFORMGAME_SUBJECT_H
#define PLATFORMGAME_SUBJECT_H

#include "Observer.h"

class Subject{

    public:

    virtual ~Subject()= default;
    virtual void attach(Observer* obs)=0;
    virtual void detach(Observer *obs)=0;
    virtual void notify(char category) const=0;

};

#endif //PLATFORMGAME_SUBJECT_H
