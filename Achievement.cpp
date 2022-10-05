//
// Created by alessio on 04/10/22.
//

#include "Achievement.h"

void Achievement::update(char category) {
    if(category=='k'){
        enemiesKilled++;
        newAchievement=true;
    }
    else{
    }
}

void Achievement::checkAchievements(){

    if(newAchievement and enemiesKilled==1) {
        std::cout << "si capit" << std::endl;
        newAchievement=false;
    }

    if(newAchievement and enemiesKilled==2){
        std::cout<<"waaa si propria brav"<<std::endl;
        newAchievement=false;
    }

}
