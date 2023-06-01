#ifndef PLATFORMGAME_ACHIEVEMENT_H
#define PLATFORMGAME_ACHIEVEMENT_H

#include "Observer.h"
#include "headers.h"

class Achievement : public Observer {

public:
    explicit Achievement();

    ~Achievement() override = default;

    void setFont(const sf::Font &font);

    void getNews(unsigned short category) override;

    bool checkAchievements();

    bool update(const sf::View &view, const float &dt);

    void render(sf::RenderTarget &target);

private:
    int enemiesKilled = 0;
    bool newAchievement = false;
    sf::Clock timeCounter;
    sf::Text text;
    int fontOpacity = 0;
    int achievementType = NOACHIEVEMENT;
};


#endif //PLATFORMGAME_ACHIEVEMENT_H
