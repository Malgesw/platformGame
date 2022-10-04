//
// Created by alessio on 04/10/22.
//

#ifndef PLATFORMGAME_ACHIEVEMENT_H
#define PLATFORMGAME_ACHIEVEMENT_H

#include "Observer.h"
#include "headers.h"

class Achievement: public Observer{

public:
    Achievement()=default;
    ~Achievement() override= default;
    void update(char category) override;
    void checkAchievements();

private:
    int enemiesKilled=0;
    bool newAchievement= false;
};


#endif //PLATFORMGAME_ACHIEVEMENT_H
