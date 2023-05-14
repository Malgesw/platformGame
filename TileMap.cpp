//
// Created by seren on 19/07/2022.
//

#include "TileMap.h"

TileMap::TileMap(GameCharacter& player) {

    enum enemy{flying=0,walking=1};

    textures.push_back(new sf::Texture);
    textures[flying]->loadFromFile("./images/flyingEnemySheet.png");
    textures.push_back(new sf::Texture);
    textures[walking]->loadFromFile("./images/cyberMonkey2.png");


    tilesTextures.push_back(new sf::Texture);
    /* tilesTextures.push_back(new sf::Texture);
     tilesTextures.push_back(new sf::Texture);
     tilesTextures.push_back(new sf::Texture);
     */

    tilesTextures[0]->loadFromFile("./images/tilesheetWIP.png");
    /* tilesTextures[1]->loadFromFile("./images/tilesheet.png", sf::IntRect(1000,0,2000,2000));
     tilesTextures[2]->loadFromFile("./images/door.png");
     tilesTextures[3]->loadFromFile("./images/tilesheet.png", sf::IntRect(0,0,1000,975));
 */



    addRoom("room1.ini", player, sf::Vector2i(48, 27));
    addRoom("room2.ini", player, sf::Vector2i(16, 16));
    addRoom("room3.ini", player, sf::Vector2i(120, 17));
    currentRoom = 0;

    spawnEnemies(player);

}

void TileMap::render(sf::RenderTarget &target) {
    rooms[currentRoom]->render(target);

}

void TileMap::update(const float &dt, GameCharacter &player, sf::RenderWindow *window) {

    unsigned int room = currentRoom;

    rooms[currentRoom]->update(dt, currentRoom, window);
    std::vector<std::shared_ptr<LevelTile>> doors = rooms[currentRoom]->getDoors();

    if (currentRoom < room) {
        player.getMovement().getCollisions().setPosition(
                doors[doors.size() - 1]->getPosition().x - rooms[currentRoom]->getDimX(),
                doors[doors.size() - 1]->getPosition().y);
        player.getMovement().setBarriers(rooms[currentRoom]->getWalls());
        player.getAttack().clearTargets();
        player.getAttack().addTargets(rooms[currentRoom]->getTargets());
    }
    else if(currentRoom > room && currentRoom < 3){
        player.getMovement().getCollisions().setPosition(doors[0]->getPosition().x + rooms[currentRoom]->getDimX(), doors[0]->getPosition().y);
        player.getMovement().setBarriers(rooms[currentRoom]->getWalls());
        player.getAttack().clearTargets();
        player.getAttack().addTargets(rooms[currentRoom]->getTargets());
    }

    //____________________VIEW COLLISIONS

    rooms[currentRoom]->setCameraCenter(player.getCenter().x, player.getCenter().y);


    //_____RIGHT
    if(rooms[currentRoom]->getCamera().getSize().x/2.f >=
            static_cast<float>(rooms[currentRoom]->getMapSize().x)*rooms[currentRoom]->getDimX() - player.getCenter().x)
        rooms[currentRoom]->setCameraCenter(static_cast<float>(rooms[currentRoom]->getMapSize().x)*rooms[currentRoom]->getDimX() - rooms[currentRoom]->getCamera().getSize().x/2.f,
                                            rooms[currentRoom]->getCamera().getCenter().y);

    //_____LEFT
    if(rooms[currentRoom]->getCamera().getSize().x/2.f >= player.getCenter().x)
        rooms[currentRoom]->setCameraCenter(rooms[currentRoom]->getCamera().getSize().x/2.f,
                                            rooms[currentRoom]->getCamera().getCenter().y);

    //_____BOTTOM
    if(rooms[currentRoom]->getCamera().getSize().y/2.f >= static_cast<float>(rooms[currentRoom]->getMapSize().y)*rooms[currentRoom]->getDimY() - player.getCenter().y)
        rooms[currentRoom]->setCameraCenter(rooms[currentRoom]->getCamera().getCenter().x,
                                            static_cast<float>(rooms[currentRoom]->getMapSize().y)*rooms[currentRoom]->getDimY() - rooms[currentRoom]->getCamera().getSize().y/2.f);

    //_____TOP
    if(rooms[currentRoom]->getCamera().getSize().y/2.f >= player.getCenter().y)
        rooms[currentRoom]->setCameraCenter(rooms[currentRoom]->getCamera().getCenter().x,
                                            rooms[currentRoom]->getCamera().getSize().y/2.f);

}

void TileMap::spawnEnemies(GameCharacter &player) {
    generateEnemy(0, "./Levels/WalkingEnemy.ini", sf::Vector2i(20, 6), player);
    generateEnemy(0, "./Levels/FlyingEnemy.ini", sf::Vector2i(10, 13), player);
    generateEnemy(2, "./Levels/FlyingEnemy.ini", sf::Vector2i(8, 1), player);
}

void TileMap::clearEnemies() {
    for (auto &r: rooms) {
        r->clearEnemies();
    }
}

void TileMap::addRoom(const std::string& roomName, GameCharacter &player,sf::Vector2i roomSize) {

    rooms.push_back(std::make_unique<Room>(roomName,player,textures,roomSize,tilesTextures));
}

void TileMap::generateEnemy(int roomNumber,std::string configFile, sf::Vector2i startPosition, GameCharacter& player) {

    CSimpleIniA enemyIni;
    SI_Error err=enemyIni.LoadFile(configFile.c_str());
    if(err<0)throw std::runtime_error("path to enemy configuration file not valid");


    //________________generating character

    auto enemy= std::make_unique<GameCharacter>(std::stoi(enemyIni.GetValue("general","life")),
                                                std::stoi(enemyIni.GetValue("general","energy")));


    //________________generating movement
    std::unique_ptr<Movement> enemyMovement;

    if(strcmp(enemyIni.GetValue("movement","type"),"W") == 0){

        enemyMovement= std::make_unique<AutoWalking>(std::stof(enemyIni.GetValue("movement","speed")),
                                                     sf::Vector2f (static_cast<float>(startPosition.x)*rooms[roomNumber]->getDimX(),
                                                                   static_cast<float>(startPosition.y)*rooms[roomNumber]->getDimY()),
                                                     sf::Vector2f(std::stof(enemyIni.GetValue("general","sizeX")),
                                                                  std::stof(enemyIni.GetValue("general","sizeY"))),
                                                                  rooms[roomNumber]->getWalls(),
                                                                  std::stof(enemyIni.GetValue("movement","jHeight")),
                                                     std::stof(enemyIni.GetValue("movement","turnBackTime")),enemy->spritePointer());
    }
    else if(strcmp(enemyIni.GetValue("movement","type"),"F") == 0){

        enemyMovement= std::make_unique<AutoFlying>(std::stof(enemyIni.GetValue("movement","speed")),
                                                     sf::Vector2f (static_cast<float>(startPosition.x)*rooms[roomNumber]->getDimX(),
                                                                   static_cast<float>(startPosition.y)*rooms[roomNumber]->getDimY()),
                                                     sf::Vector2f(std::stof(enemyIni.GetValue("general","sizeX")),
                                                                  std::stof(enemyIni.GetValue("general","sizeY"))),
                                                     rooms[roomNumber]->getWalls(),
                                                     sf::Vector2f(rooms[roomNumber]->getDimX(),rooms[roomNumber]->getDimY()),enemy->spritePointer());

    }
    enemyMovement->addWalls(rooms[roomNumber]->getWalls());



    //________________generating attack
    std::unique_ptr<Attack> enemyAttack;

    if(strcmp(enemyIni.GetValue("attack","type"),"M") == 0){

        enemyAttack= std::make_unique<AutoMelee>(sf::Vector2f(std::stof(enemyIni.GetValue("attack","rangeX")),
                                                              std::stof(enemyIni.GetValue("attack","rangeY"))),
                                                            std::stof(enemyIni.GetValue("attack","speed")),
                                                                 std::stof(enemyIni.GetValue("attack","damage")),
                                                                    std::stof(enemyIni.GetValue("attack","knockback")),enemy->spritePointer());
    }
    std::vector<AttackTarget> targets;
    targets.push_back(player.generateTarget());
    enemyAttack->addTargets(targets);


    //________________generating animation
    std::unique_ptr<Animation> enemyAnimation;

    enemyAnimation=std::make_unique<Animation>(textures[std::stoi(enemyIni.GetValue("animation","texture"))],
                                               sf::Vector2i(std::stoi(enemyIni.GetValue("animation","imageCountX")),
                                                            std::stoi(enemyIni.GetValue("animation","imageCountY"))),
                                               std::stof(enemyIni.GetValue("animation","switchTime")),
                                               sf::Vector2f(std::stof(enemyIni.GetValue("general","sizeX")),
                                                            std::stof(enemyIni.GetValue("general","sizeY"))),false,enemy->spritePointer());


    //________________assigning enemy's components
    enemy->setMovement(std::move(enemyMovement));
    enemy->setAttack(std::move(enemyAttack));
    enemy->setAnimation(std::move(enemyAnimation));


    //________________adding enemy to the list
    rooms[roomNumber]->addEnemy(enemy);

}


TileMap::~TileMap() {
for (auto& t: textures){
    delete t;
}
}

