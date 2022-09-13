#include "Room.h"

Room::Room(const std::string& roomName,GameCharacter& mainCharacter):player(mainCharacter) {
    heightTiles = 8;
    widthTiles = 8;
    dimX = 800.f/widthTiles;
    dimY = 600.f/heightTiles;
    initFloor(roomName);



    auto enemy= std::make_shared<GameCharacter>(sf::Vector2f(500.f,100.f),sf::Vector2f(50,50),50,50);
    auto enemy2= std::make_shared<GameCharacter>(sf::Vector2f(500.f,100.f),sf::Vector2f(50,50),50,50);
    std::string enemyName("enemy1");
    std::string enemyName2("enemy2");
    addEnemy(enemy,enemyName);
    addEnemy(enemy2,enemyName2);
    std::shared_ptr<Movement> autoMovement;
    std::shared_ptr<Movement> autoMovement2;
    autoMovement=std::make_shared<AutoWalking>( AutoWalking(10,sf::Vector2f (510.f,100.f),sf::Vector2f(50,50),walls,50,4));
    autoMovement2=std::make_shared<AutoFlying>( AutoFlying(10,sf::Vector2f (510.f,500.f),sf::Vector2f(50,50),walls,sf::Vector2f(dimX,dimY)));
    enemy->setMovement(autoMovement);
    enemy2->setMovement(autoMovement2);
    for (auto &e : enemies){
        e.second->getMovement()->addWalls(walls);
        std::vector<AttackTarget> targets;
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

    for(int i = 0; i < heightTiles; i++) {

        while(ifs >> n){
            numbers.push_back(n);
        }

    }

    ifs.close();

    for(int i=0;i<heightTiles;i++){
        std::vector<std::shared_ptr<LevelTile>> row;
        for(int j=0;j<widthTiles;j++){
            row.push_back(std::make_unique<LevelTile>(numbers[j][i], i*dimX , j*dimY,  size));
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
        e.second->update(dt, walls,window, player.getMovement()->getPosition());
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
