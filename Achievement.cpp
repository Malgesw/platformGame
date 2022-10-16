//
// Created by alessio on 04/10/22.
//

#include "Achievement.h"

#include <cmath>

Achievement::Achievement() {
    text.setCharacterSize(18);
    text.setString("prova");
    text.setFillColor(sf::Color::Red);

}



void Achievement::getNews(char category) {

    if(category=='k'){
        enemiesKilled++;
        newAchievement=true;
    }
    else{
    }
}



void Achievement::checkAchievements(){

    if(newAchievement and enemiesKilled==1) {
        text.setString("first enemy killed, keep on");
        std::cout<<"fatto"<<std::endl;
        fontOpacity=255;
        newAchievement=false;
    }

    if(newAchievement and enemiesKilled==2){
        text.setString("double kill");
        fontOpacity=255;
        newAchievement=false;
    }

}


void Achievement::update(const sf::View& view, const float& dt ) {
    text.setFillColor(sf::Color(255,0,0,fontOpacity));
    text.setPosition(view.getCenter().x-text.getGlobalBounds().width/2,view.getCenter().y-view.getSize().x/4-text.getGlobalBounds().height/2);
    checkAchievements();
    if (fontOpacity>0){
        fontOpacity= fontOpacity- std::round(dt*100);
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