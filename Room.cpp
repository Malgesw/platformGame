#include "Room.h"

Room::Room(const std::string& roomName,GameCharacter &mainCharacter,const std::vector<sf::Texture * > & textures ):player(mainCharacter) {
    heightTiles = 16;
    widthTiles = 16;
    dimX = 800.f/widthTiles;
    dimY = 600.f/heightTiles;
    initFloor(roomName);
    camera.setSize(400.f, 300.f);
    camera.setCenter(player.getMovement().getPosition().x+player.getMovement().getCollisions().getGlobalBounds().width/2.f,
                     player.getMovement().getPosition().y+player.getMovement().getCollisions().getGlobalBounds().height/2.f);


    if(roomName=="room1.ini") {
        auto enemy = std::make_unique<GameCharacter>(3, 50);
        auto enemy2 = std::make_unique<GameCharacter>(3, 50);

        std::unique_ptr<Movement> autoMovement = std::make_unique<AutoWalking>(
                AutoWalking(10, sf::Vector2f(10*dimX, 6 * dimY), sf::Vector2f(35, 35), walls, 50, 4));
        std::unique_ptr<Movement> autoMovement2= std::make_unique<AutoFlying>(
                AutoFlying(7, sf::Vector2f(10 * dimX, 13 * dimY), sf::Vector2f(50, 37.5), walls,
                           sf::Vector2f(dimX, dimY)));

        std::unique_ptr<Attack> autoAttack= std::make_unique<AutoMelee>( sf::Vector2f(35,35),1.f,1,40.f);
        std::unique_ptr<Attack> autoAttack2= std::make_unique<AutoMelee>( sf::Vector2f(50,37.5),1.f,1,40.f);
        std::unique_ptr<Animation> enemyanimation= std::make_unique<Animation>(textures[flying],sf::Vector2u (5,3),0.3f,sf::Vector2f (10 * dimX, 6 * dimY),sf::Vector2f(35, 35));
        std::unique_ptr<Animation> enemyanimation2= std::make_unique<Animation>(textures[flying],sf::Vector2u (5,3),0.3f,sf::Vector2f (10 * dimX, 13 * dimY),sf::Vector2f(50, 37.5));

        enemy->setMovement(std::move(autoMovement));
        enemy2->setMovement(std::move(autoMovement2));
        enemy->setAttack(std::move(autoAttack));
        enemy2->setAttack(std::move(autoAttack2));
        enemy->setAnimation(std::move(enemyanimation));
        enemy2->setAnimation(std::move(enemyanimation2));

        addEnemy(enemy);
        addEnemy(enemy2);

    }

    for (auto &e: enemies) {

        //____________________________ADDING WALLS
        e->getMovement().addWalls(walls);
        std::vector<AttackTarget> targets;
        //____________________________ADDING ATTACK TARGETS
        targets.push_back(player.generateTarget());
        e->getAttack().addTargets(targets);

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
        e->render(target);
    }

    target.setView(camera);
}

void Room::update(const float &dt, unsigned int &currentRoom,sf::RenderWindow* window) {

    //________________________________UPDATING MAP
    for(int i=0;i<heightTiles;i++){
        for(int j=0;j<widthTiles;j++){

            if(tiles[i][j]->isExit() && tiles[i][j]->getGlobalBounds().intersects(player.getMovement().getCollisions().getGlobalBounds())){
                if(player.getMovement().getVelocity().x >= 0.f)
                    currentRoom++;
                else
                    currentRoom--;
            }
        }
    }
    //________________________________UPDATING ENEMIES

    for(auto &e : enemies){
        e->update(dt, walls,window, player.getCenter());
    }

    auto i = enemies.begin();
    int j=0;

    while (i!= enemies.end()) {
        //std::cout<<"nemico numero "<<j<<std::endl;

        //std::cout<<"vita nemico "<<(*i)->getHp()<<std::endl;

        if((*i)->getHp()<=0){
            std::cout<<"nemico cancellato dalla mappa"<<std::endl;
            enemies.erase(i++);

        }

        else{
            i++;
            j++;
        }
    }

}

void Room::addEnemy(std::unique_ptr<GameCharacter>& enemy) {
    enemies.push_back(std::move(enemy));
}



std::vector<AttackTarget> Room::getTargets() {
    std::vector<AttackTarget> targets;
    for(auto &e : enemies){
        targets.push_back(e->generateTarget());
    }
    return targets;
}
