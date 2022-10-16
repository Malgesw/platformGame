//
// Created by alessio on 04/10/22.
//

#ifndef PLATFORMGAME_ACHIEVEMENT_H
#define PLATFORMGAME_ACHIEVEMENT_H

#include "Observer.h"
#include "headers.h"

class Achievement: public Observer{

public:
    explicit Achievement(float showTime);
    ~Achievement() override= default;
    void setFont(const sf::Font& font);
    void getNews(char category) override;
    void checkAchievements();
    void update(const sf::View& view, const float& dt);
    void render(sf::RenderTarget &target);

private:
    int enemiesKilled=0;
    bool newAchievement= false;
    float showTime=1.5f;
    sf::Clock timeCounter;
    sf::Text text;
    int fontOpacity=0;
};


#endif //PLATFORMGAME_ACHIEVEMENT_H
