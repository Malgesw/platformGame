//
// Created by alessio on 02/10/22.
//

#ifndef PLATFORMGAME_OBSERVER_H
#define PLATFORMGAME_OBSERVER_H
class Observer{

public:

    virtual ~Observer()=default;
    virtual void getNews(char category)=0;
};
#endif //PLATFORMGAME_OBSERVER_H
