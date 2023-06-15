#include "Achievement.h"

#include <cmath>

Achievement::Achievement() {
    text.setCharacterSize(18);
    text.setString("");
    text.setFillColor(sf::Color::Red);

}



void Achievement::getNews(unsigned short category) {

    if (category == ENEMYKILLED) {
        enemiesKilled++;
        newAchievement = true;
        achievementType = ENEMYKILLED;
    } else if (category == DROIDACTIVATED) {
        std::cout << "from Achievement.cpp : droid activated" << std::endl;
        newAchievement = true;
        achievementType = DROIDACTIVATED;
    } else if (category == RESETACHIEVEMENTS) {
        newAchievement = true;
        achievementType = NOACHIEVEMENT;
        enemiesKilled = 0;
    } else if (category == BOSSKILLED) {
        newAchievement = true;
        achievementType = BOSSKILLED;
    } else throw std::runtime_error("Invalid achievement category");
}



bool Achievement::checkAchievements() {

    bool result = false;


    if (achievementType == ENEMYKILLED) {
        if (newAchievement and enemiesKilled == 1) {
            text.setString("first enemy killed, keep on");
            fontOpacity = 255;
            newAchievement = false;
        } else if (newAchievement and enemiesKilled == 2) {
            text.setString("double kill!");
            fontOpacity = 255;
            newAchievement = false;
        } else if (newAchievement and enemiesKilled == 3) {
            text.setString("rampage!");
            fontOpacity = 255;
            newAchievement = false;
        } else if (newAchievement and enemiesKilled == 10) {
            text.setString("please spare some enemies for our next game");
            fontOpacity = 255;
            newAchievement = false;
        } else if (newAchievement and enemiesKilled == 11) {
            text.setString("noone ever listens to me");
            fontOpacity = 255;
            newAchievement = false;
        } else if (newAchievement and enemiesKilled == 18) {
            text.setString("there are none left, are you happy now?");
            fontOpacity = 255;
            newAchievement = false;
        } else if (newAchievement) {
            std::string message = "Enemies Killed:  " + std::to_string(enemiesKilled);
            text.setString(message);
            fontOpacity = 255;
            newAchievement = false;
        }

    }
    if (newAchievement and achievementType == DROIDACTIVATED) {
        text.setString("Droid activated!");
        fontOpacity = 255;
        newAchievement = false;
    }

    if (newAchievement and achievementType == BOSSKILLED) {
        //text.setString("Congratulations, you killed the boss!");
        //fontOpacity = 255;
        //newAchievement = false;
        result = true;
    }
    return result;
}


bool Achievement::update(const sf::View &view, const float &dt) {
    text.setFillColor(sf::Color(255, 0, 0, fontOpacity));
    text.setPosition(view.getCenter().x - text.getGlobalBounds().width / 2.f,
                     view.getCenter().y - view.getSize().y / 3.f - text.getGlobalBounds().height / 2.f);
    text.setCharacterSize(static_cast<unsigned int>(4.f * view.getSize().y / 65.f));
    bool result = checkAchievements();
    //_____________________________TEXT FADE OUT EFFECT
    if (fontOpacity > 0) {
        fontOpacity = fontOpacity - static_cast<int>(std::round(dt * 100));
    }
    if (fontOpacity < 0) {
        fontOpacity = 0;
    }
    return result;
}


void Achievement::render(sf::RenderTarget &target) {
    target.draw(text);
}



void Achievement::setFont(const sf::Font &font) {
    text.setFont(font);
}