//
// Created by alessio on 04/10/22.
//

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
    } else throw std::runtime_error("Invalid achievement category");
}



void Achievement::checkAchievements(){

    if(newAchievement and enemiesKilled==1) {
        text.setString("first enemy killed, keep on");
        fontOpacity=255;
        newAchievement=false;
    }

    if(newAchievement and enemiesKilled==2){
        text.setString("double kill!");
        fontOpacity=255;
        newAchievement=false;
    }

    if(newAchievement and enemiesKilled==3){
        text.setString("rampage!");
        fontOpacity=255;
        newAchievement=false;
    }

}


void Achievement::update(const sf::View& view, const float& dt ) {
    text.setFillColor(sf::Color(255,0,0,fontOpacity));
    text.setPosition(view.getCenter().x-text.getGlobalBounds().width/2.f,view.getCenter().y-view.getSize().y/3.f-text.getGlobalBounds().height/2.f);
    text.setCharacterSize(static_cast<unsigned int>(4.f*view.getSize().y/65.f));
    checkAchievements();
    //_____________________________TEXT FADE OUT EFFECT
    if (fontOpacity>0){
        fontOpacity= fontOpacity- static_cast<int>(std::round(dt * 100));
    }
    if (fontOpacity<0) {
        fontOpacity = 0;
    }
}


void Achievement::render(sf::RenderTarget &target) {
    target.draw(text);
}



void Achievement::setFont(const sf::Font &font) {
    text.setFont(font);
}