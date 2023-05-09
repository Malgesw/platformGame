#ifndef PLATFORMGAME_OBSERVER_H
#define PLATFORMGAME_OBSERVER_H

enum achievementTypes {
    ENEMYKILLED, DROIDACTIVATED, RESETACHIEVEMENTS, NOACHIEVEMENT
};

class Observer {

public:

    virtual ~Observer() = default;

    virtual void getNews(unsigned short category) = 0;
};

#endif //PLATFORMGAME_OBSERVER_H
