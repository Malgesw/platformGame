
#include <SFML/Graphics.hpp>

#include "TileMap.h"




int main()
{
    sf::RenderWindow window(sf::VideoMode(400,400), "map_attempt");

    TileMap levelMapstate = TileMap();




    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
            }
        }

        window.clear();
        for(int i=0;i<levelMapstate.gridWidth;i++){
            for(int j=0;j<levelMapstate.gridLength;j++){
                window.draw(levelMapstate.tiles[i][j]->body);
            }
        }



        window.display();
    }

}
