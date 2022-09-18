#include "Room.h"

Room::Room(const std::string& roomName,GameCharacter& mainCharacter):player(mainCharacter) {
    heightTiles = 16;
    widthTiles = 16;
    dimX = 800.f/widthTiles;
    dimY = 600.f/heightTiles;
    initFloor(roomName);


    if(roomName=="room1.ini") {
        auto enemy = std::make_shared<GameCharacter>(sf::Vector2f(500.f, 100.f), sf::Vector2f(50, 37.5), 50, 50);
        auto enemy2 = std::make_shared<GameCharacter>(sf::Vector2f(500.f, 100.f), sf::Vector2f(50, 37.5), 50, 50);
        std::string enemyName("enemy1");
        std::string enemyName2("enemy2");
        addEnemy(enemy, enemyName);
        addEnemy(enemy2, enemyName2);
        std::shared_ptr<Movement> autoMovement;
        std::shared_ptr<Movement> autoMovement2;
        std::shared_ptr<Attack> autoAttack;
        std::shared_ptr<Attack> autoAttack2;
        autoMovement = std::make_shared<AutoWalking>(
                AutoWalking(10, sf::Vector2f(10*dimX, 6 * dimY), sf::Vector2f(35, 35), walls, 50, 4));
        autoMovement2 = std::make_shared<AutoFlying>(
                AutoFlying(7, sf::Vector2f(10 * dimX, 13 * dimY), sf::Vector2f(50, 37.5), walls,
                           sf::Vector2f(dimX, dimY)));
        autoAttack= std::make_shared<AutoAttack>( sf::Vector2f(35,35),1.f,5.f,40.f);
        autoAttack2= std::make_shared<AutoAttack>( sf::Vector2f(50,37.5),1.f,5.f,40.f);



        enemy->setMovement(autoMovement);
        enemy2->setMovement(autoMovement2);
        enemy->setAttack(autoAttack);
        enemy2->setAttack(autoAttack2);
    }

    for (auto &e: enemies) {

        //____________________________ADDING WALLS
        e.second->getMovement()->addWalls(walls);
        std::vector<AttackTarget> targets;
        //____________________________ADDING ATTACK TARGETS
        targets.push_back(player.generateTarget());
        e.second->getAttack()->addTargets(targets);

    }

}

void Room::initFloor(const std::string& roomName) {

    sf::Vector2f size(dimX, dimY);
    tiles.clear();
    doors.clear();
    std::ifstream ifs;
    std::string n;
    ifs.open("../Levels/"+roomName);
    for(int i = 0; i < widthTiles; i++) {

        while(ifs >> n){
            numbers.push_back(n);
        }

    }

    ifs.close();

    for(int i=0;i<heightTiles;i++){
        std::vector<std::shared_ptr<LevelTile>> row;
        for(int j=0;j<widthTiles;j++){
            row.push_back(std::make_unique<LevelTile>(numbers[i][j], j*dimX , i*dimY,  size));
        }
        tiles.push_back(row);
    }

    for(int i=0;i<heightTiles;i++){
        for(int j=0;j<widthTiles;j++){
            if(tiles[i][j]->getTileType() == WALL)
                walls.push_back(tiles[i][j]);
            else if(tiles[i][j]->getTileType() == DOOR)
                doors.push_back(tiles[i][j]);
        }
    }

}

void Room::render(sf::RenderTarget &target) {

    //________________________________RENDERING MAP
    for(int i=0;i<heightTiles;i++){
        for(int j=0;j<widthTiles;j++){
            tiles[i][j]->render(target);
        }
    }
    //________________________________RENDERING ENEMIES
    for(auto &e : enemies){
        e.second->render(target);
    }
}

void Room::update(const float &dt, unsigned int &currentRoom,sf::RenderWindow* window) {

    //________________________________UPDATING MAP
    for(int i=0;i<heightTiles;i++){
        for(int j=0;j<widthTiles;j++){

            if(tiles[i][j]->isExit() && tiles[i][j]->getGlobalBounds().intersects(player.getMovement()->getCollisions().getGlobalBounds())){
                if(player.getMovement()->getVelocity().x >= 0.f)
                    currentRoom++;
                else
                    currentRoom--;
            }
        }
    }
    //________________________________UPDATING ENEMIES
    for (auto &e: enemies) {
        e.second->update(dt, walls,window, sf::Vector2f (player.getMovement()->getPosition().x+player.getMovement()->getCollisions().getSize().x/2,player.getMovement()->getPosition().y+player.getMovement()->getCollisions().getSize().y/2));
    }
}

void Room::addEnemy(std::shared_ptr<GameCharacter>& enemy, std::string& id) {
    enemies.insert({id,enemy});
}

void Room::removeEnemy(std::string &id) {
    enemies.erase(id);
}

std::vector<AttackTarget> Room::getTargets() {
    std::vector<AttackTarget> targets;
    for(auto &e : enemies){
        targets.push_back(e.second->generateTarget());
    }
    return targets;
}
