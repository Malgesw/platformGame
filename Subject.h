#ifndef PLATFORMGAME_SUBJECT_H
#define PLATFORMGAME_SUBJECT_H

#include "Observer.h"

class Subject{

    public:

    virtual ~Subject()= default;
    virtual void attach(Observer* obs)=0;
    virtual void detach(Observer *obs) = 0;

    virtual void notify(unsigned short category) const = 0;

};

#endif //PLATFORMGAME_SUBJECT_H
