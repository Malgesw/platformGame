//
// Created by alessio on 26/07/22.
//

#ifndef PLATFORMGAME_OBSERVER_H
#define PLATFORMGAME_OBSERVER_H

class Observer{
protected:
    virtual ~Observer()=default;

public:
    virtual void updateDt(float deltaTime)=0;
};

#endif //PLATFORMGAME_OBSERVER_H
