#include "TileMap.h"
#include "AutoRanged.h"


TileMap::TileMap(GameCharacter &player, Achievement *achievementCounter) : achievementCounter(achievementCounter) {

    enum enemy {
        flying = 0, walking = 1, boss = 2
    };

    textures.push_back(new sf::Texture);
    textures[flying]->loadFromFile("./images/flyingEnemySheetfixed.png");
    textures.push_back(new sf::Texture);
    textures[walking]->loadFromFile("./images/cyberMonkey2.png");
    tilesTextures.push_back(new sf::Texture);
    tilesTextures[0]->loadFromFile("./images/tilesheetWIP.png");
    textures.push_back(new sf::Texture); //Boss

    addRoom("room1.ini", player, sf::Vector2i(48, 27));
    addRoom("room2.ini", player, sf::Vector2i(48, 26));
    addRoom("room3.ini", player, sf::Vector2i(80, 17));
    addRoom("room4.ini", player, sf::Vector2i(26, 14));

    currentRoom = 0;

    spawnEnemies(player);
    placeItems(player);

}

void TileMap::render(sf::RenderTarget &target) {
    rooms[currentRoom]->render(target);

}

void TileMap::update(const float &dt, GameCharacter &player, sf::RenderWindow *window) {

    unsigned int room = currentRoom;
    unsigned short int collisionType;

    collisionType = rooms[currentRoom]->update(dt, currentRoom, window);
    std::vector<std::shared_ptr<LevelTile>> doors = rooms[currentRoom]->getDoors();

    if (currentRoom < room) {
        player.setPosition(
                doors[doors.size() - 1]->getPosition().x -
                (collisionType == LEFT ? rooms[currentRoom]->getDimX() : 0.f),
                doors[doors.size() - 1]->getPosition().y -
                (collisionType == TOP ? 2.f * rooms[currentRoom]->getDimY() : 0.f));
        player.clearWalls();
        player.addWalls(rooms[currentRoom]->getWalls());
        player.clearTargets();
        player.clearRelatedObjects();
        player.addTargets(rooms[currentRoom]->getTargets());
    } else if (currentRoom > room && currentRoom < maxRoom) {
        player.setPosition(doors[0]->getPosition().x + (collisionType == RIGHT ? rooms[currentRoom]->getDimX() : 0.f),
                           doors[0]->getPosition().y + (collisionType == BOTTOM ? rooms[currentRoom]->getDimY() : 0.f));
        player.clearWalls();
        player.addWalls(rooms[currentRoom]->getWalls());
        player.clearTargets();
        player.clearRelatedObjects();
        player.addTargets(rooms[currentRoom]->getTargets());
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
                                            rooms[currentRoom]->getCamera().getSize().y / 2.f);

}

void TileMap::spawnEnemies(GameCharacter &player) {
    generateEnemy(0, "./Levels/WalkingEnemy.ini", sf::Vector2i(20, 6), player);
    generateEnemy(1, "./Levels/WalkingEnemy.ini", sf::Vector2i(25, 9), player);
    generateEnemy(1, "./Levels/WalkingEnemy.ini", sf::Vector2i(18, 9), player);
    generateEnemy(1, "./Levels/WalkingEnemy.ini", sf::Vector2i(30, 23), player);
    generateEnemy(1, "./Levels/WalkingEnemy.ini", sf::Vector2i(34, 23), player);
    generateEnemy(2, "./Levels/WalkingEnemy.ini", sf::Vector2i(15, 8), player);
    generateEnemy(2, "./Levels/WalkingEnemy.ini", sf::Vector2i(39, 10), player);
    generateEnemy(2, "./Levels/WalkingEnemy.ini", sf::Vector2i(58, 8), player);
    generateEnemy(0, "./Levels/FlyingEnemy.ini", sf::Vector2i(40, 3), player);
    generateEnemy(0, "./Levels/FlyingEnemy.ini", sf::Vector2i(40, 14), player);
    generateEnemy(0, "./Levels/FlyingEnemy.ini", sf::Vector2i(40, 24), player);

    generateEnemy(0, "./Levels/FlyingEnemy.ini", sf::Vector2i(32, 3), player);
    generateEnemy(0, "./Levels/FlyingEnemy.ini", sf::Vector2i(32, 14), player);
    generateEnemy(0, "./Levels/FlyingEnemy.ini", sf::Vector2i(32, 24), player);

    generateEnemy(1, "./Levels/FlyingEnemy.ini", sf::Vector2i(10, 13), player);
    generateEnemy(2, "./Levels/FlyingEnemy.ini", sf::Vector2i(25, 4), player);
    generateEnemy(2, "./Levels/FlyingEnemy.ini", sf::Vector2i(45, 6), player);

    generateEnemy(2, "./Levels/FlyingEnemy.ini", sf::Vector2i(8, 1), player);
    generateEnemy(3, "./Levels/Boss.ini", sf::Vector2i(12, 10), player);
}

void TileMap::placeItems(GameCharacter &player) {
    generateItem(0, sf::Vector2i(43, 25), sf::Vector2f(80.f, 80.f), TACO, player);
    generateItem(1, sf::Vector2i(13, 6), sf::Vector2f(80.f, 80.f), TACO, player);
    generateItem(1, sf::Vector2i(24, 4), sf::Vector2f(80.f, 80.f), TACO, player);
    generateItem(1, sf::Vector2i(32, 22), sf::Vector2f(80.f, 80.f), TACO, player);
    generateItem(2, sf::Vector2i(20, 2), sf::Vector2f(80.f, 80.f), TACO, player);
    generateItem(2, sf::Vector2i(67, 7), sf::Vector2f(80.f, 80.f), TACO, player);
    generateItem(2, sf::Vector2i(75, 1), sf::Vector2f(80.f, 80.f), TACO, player);

    generateItem(1, sf::Vector2i(38, 5), sf::Vector2f(50.f, 50.f), SHELLDROID, player);
    generateItem(1, sf::Vector2i(45, 23), sf::Vector2f(50.f, 50.f), GLIDINGDROID, player);
    generateItem(3, sf::Vector2i(7, 9), sf::Vector2f(50.f, 50.f), SHELLDROID, player);
    generateItem(3, sf::Vector2i(18, 9), sf::Vector2f(50.f, 50.f), GLIDINGDROID, player);

    generateItem(2, sf::Vector2i(2, 12),
                 sf::Vector2f(rooms[currentRoom]->getDimX() / 1.5f, rooms[currentRoom]->getDimY() / 1.5f), DEATHZONE,
                 player);
    generateItem(2, sf::Vector2i(1, 12),
                 sf::Vector2f(rooms[currentRoom]->getDimX() / 1.5f, rooms[currentRoom]->getDimY() / 1.5f), DEATHZONE,
                 player);
    for (int i = 0; i < rooms[2]->getMapSize().x; i++) {
        generateItem(2, sf::Vector2i(i, rooms[2]->getMapSize().y - 1),
                     sf::Vector2f(rooms[2]->getDimX() / 1.5f, rooms[2]->getDimY() / 1.5f), DEATHZONE,
                     player);
    }
}

void TileMap::clearEnemies() {
    for (auto &r: rooms) {
        r->clearEnemies();
    }
}

void TileMap::clearItems() {
    for (auto &r: rooms)
        r->clearItems();
}

void TileMap::addRoom(const std::string &roomName, GameCharacter &player, sf::Vector2i roomSize) {

    rooms.push_back(std::make_unique<Room>(roomName, player, textures, roomSize, tilesTextures));
}

void TileMap::generateEnemy(int roomNumber, std::string configFile, sf::Vector2i startPosition, GameCharacter &player) {

    CSimpleIniA enemyIni;
    SI_Error err = enemyIni.LoadFile(configFile.c_str());
    if(err<0)throw std::runtime_error("path to enemy configuration file not valid");


    //________________generating character

    auto enemy = std::make_unique<GameCharacter>(std::stoi(enemyIni.GetValue("general", "life")),
                                                 std::stoi(enemyIni.GetValue("general", "energy")),
                                                 not strcmp(enemyIni.GetValue("general", "isBoss"), "true"));


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
    else if (strcmp(enemyIni.GetValue("movement", "type"), "F") == 0) {

        enemyMovement = std::make_unique<AutoFlying>(std::stof(enemyIni.GetValue("movement", "speed")),
                                                     sf::Vector2f(static_cast<float>(startPosition.x) *
                                                                  rooms[roomNumber]->getDimX(),
                                                                  static_cast<float>(startPosition.y) *
                                                                  rooms[roomNumber]->getDimY()),
                                                     sf::Vector2f(std::stof(enemyIni.GetValue("general", "sizeX")),
                                                                  std::stof(enemyIni.GetValue("general", "sizeY"))),
                                                     rooms[roomNumber]->getWalls(),
                                                     sf::Vector2f(rooms[roomNumber]->getDimX(),
                                                                  rooms[roomNumber]->getDimY()),
                                                     enemy->spritePointer(),
                                                     sf::Vector2f(rooms[roomNumber]->getMapSize()));

    } else if (strcmp(enemyIni.GetValue("movement", "type"), "N") == 0) {
        enemyMovement = std::make_unique<NoMovement>(
                sf::Vector2f(static_cast<float>(startPosition.x) * rooms[roomNumber]->getDimX(),
                             static_cast<float>(startPosition.y) * rooms[roomNumber]->getDimY()),
                sf::Vector2f(std::stof(enemyIni.GetValue("general", "sizeX")),
                             std::stof(enemyIni.GetValue("general", "sizeY"))), enemy->spritePointer());

    } else if (strcmp(enemyIni.GetValue("movement", "type"), "P") == 0) {

        enemyMovement = std::make_unique<PeriodicFlying>(std::stof(enemyIni.GetValue("movement", "speed")),
                                                         sf::Vector2f(static_cast<float>(startPosition.x) *
                                                                      rooms[roomNumber]->getDimX(),
                                                                      static_cast<float>(startPosition.y) *
                                                                      rooms[roomNumber]->getDimY()),
                                                         sf::Vector2f(std::stof(enemyIni.GetValue("general", "sizeX")),
                                                                      std::stof(enemyIni.GetValue("general", "sizeY"))),
                                                         rooms[roomNumber]->getWalls(),
                                                         std::stof(enemyIni.GetValue("movement", "turnBackTime")),
                                                         enemy->spritePointer());

        std::unique_ptr<SpecialAbility> enemyAbility = std::make_unique<Resilience>(enemy->spritePointer());
        enemy->setSpecialAbility(std::move(enemyAbility));
    }
    enemyMovement->addWalls(rooms[roomNumber]->getWalls());



    //________________generating attack
    std::unique_ptr<Attack> enemyAttack;

    if (strcmp(enemyIni.GetValue("attack", "type"), "M") == 0) {

        enemyAttack = std::make_unique<AutoMelee>(sf::Vector2f(std::stof(enemyIni.GetValue("attack", "rangeX")),
                                                               std::stof(enemyIni.GetValue("attack", "rangeY"))),
                                                  std::stof(enemyIni.GetValue("attack", "speed")),
                                                  std::stof(enemyIni.GetValue("attack", "damage")),
                                                  std::stof(enemyIni.GetValue("attack", "knockback")),
                                                  std::stof(enemyIni.GetValue("attack", "delay")),
                                                  std::stof(enemyIni.GetValue("attack", "offset")),
                                                  enemy->spritePointer());
    } else if (strcmp(enemyIni.GetValue("attack", "type"), "R") == 0) {

        enemyAttack = std::make_unique<AutoRanged>(sf::Vector2f(std::stof(enemyIni.GetValue("attack", "bulletSize")),
                                                                std::stof(enemyIni.GetValue("attack", "bulletSize"))),
                                                   std::stof(enemyIni.GetValue("attack", "bulletSpeed")),
                                                   std::stof(enemyIni.GetValue("attack", "speed")),
                                                   std::stof(enemyIni.GetValue("attack", "damage")),
                                                   std::stof(enemyIni.GetValue("attack", "knockback")),
                                                   std::stof(enemyIni.GetValue("attack", "delay")),
                                                   enemy->spritePointer(), 400.f);
    } else if (strcmp(enemyIni.GetValue("attack", "type"), "S") == 0) {

        enemyAttack = std::make_unique<AutoStarRanged>(
                sf::Vector2f(std::stof(enemyIni.GetValue("attack", "bulletSize")),
                             std::stof(enemyIni.GetValue("attack", "bulletSize"))),
                std::stof(enemyIni.GetValue("attack", "bulletSpeed")),
                std::stof(enemyIni.GetValue("attack", "speed")),
                std::stof(enemyIni.GetValue("attack", "damage")),
                std::stof(enemyIni.GetValue("attack", "knockback")),
                std::stof(enemyIni.GetValue("attack", "delay")),
                enemy->spritePointer(), 1000.f);
    } else
        std::cout << "errore nell' inizializzazi" << std::endl;
    std::vector<AttackTarget *> targets;
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

void TileMap::generateItem(int roomNumber, sf::Vector2i position, sf::Vector2f size, unsigned short int type,
                           GameCharacter &player) {

    if (type == TACO) {
        auto tex = new sf::Texture;
        tex->loadFromFile("./images/taco.png");
        auto animation = std::make_unique<Animation>(tex, sf::Vector2i(4, 1), 0.30f, size);
        std::unique_ptr<Item> item_i = std::make_unique<Item>(size,
                                                              sf::Vector2f(
                                                                      static_cast<float>(position.x) *
                                                                      rooms[roomNumber]->getDimX() +
                                                                      rooms[roomNumber]->getDimX() / 4.f,
                                                                      static_cast<float>(position.y) *
                                                                      rooms[roomNumber]->getDimY() +
                                                                      rooms[roomNumber]->getDimY() / 4.f),
                                                              std::move(animation), 1);
        rooms[roomNumber]->addItem(item_i);
    } else if (type == DEATHZONE) {
        auto tex = new sf::Texture;
        sf::Image transparent;
        transparent.create(rooms[currentRoom]->getDimX(), rooms[currentRoom]->getDimY(), sf::Color::Transparent);
        tex->loadFromImage(transparent);
        auto animation = std::make_unique<Animation>(tex, sf::Vector2i(4, 1), 0.30f, size);
        std::unique_ptr<Item> item_s = std::make_unique<Item>(size,
                                                              sf::Vector2f(
                                                                      static_cast<float>(position.x) *
                                                                      rooms[roomNumber]->getDimX(),
                                                                      static_cast<float>(position.y) *
                                                                      rooms[roomNumber]->getDimY()),
                                                              std::move(animation), -1000000);
        rooms[roomNumber]->addItem(item_s);
    } else if (type == SHELLDROID) {
        auto text = new sf::Texture;
        text->loadFromFile("./images/droidstatic2.png");
        auto text2 = new sf::Texture;
        text2->loadFromFile("./images/ballDroid.png");
        auto animation = std::make_unique<Animation>(text, sf::Vector2i(1, 1), 0.30f, size * 1.3f);
        std::unique_ptr<Movement> playerMovement = std::make_unique<WalkingMovement>(380, sf::Vector2f(
                                                                                             position.x * rooms[currentRoom]->getDimX(),
                                                                                             position.y * rooms[currentRoom]->getDimY()), sf::Vector2f(120, 126), 2000, player.spritePointer(),
                                                                                     true);
        playerMovement->addWalls(rooms[currentRoom]->getWalls());
        //auto playerAttack=std::make_unique<RangedAttack>(sf::Vector2f (40.f,40.f),400.5f,0.5f,1,150.f,player.spritePointer(),true);
        std::unique_ptr<Animation> playerAnimation = std::make_unique<Animation>(text2, sf::Vector2i(5, 4), 0.3f,
                                                                                 sf::Vector2f(168, 126) / 1.1f, true,
                                                                                 player.spritePointer());
        std::unique_ptr<SpecialAbility> playerSpecialAbility = std::make_unique<Shell>(player.spritePointer());
        std::unique_ptr<Attack> playerAttack = std::make_unique<MeleeAttack>(sf::Vector2f(120.f, 126.f), 1.0f, 3.0f,
                                                                             200.f,
                                                                             0.f, 40.f, player.spritePointer());
        playerAttack->addTargets(rooms[currentRoom]->getTargets());
        playerAttack->attach(achievementCounter);
        std::unique_ptr<Item> item_d = std::make_unique<Droid>(std::move(playerAnimation), std::move(playerMovement),
                                                               std::move(playerAttack), std::move(playerSpecialAbility),
                                                               size * 1.3f,
                                                               sf::Vector2f(static_cast<float>(position.x) *
                                                                            rooms[roomNumber]->getDimX() +
                                                                            rooms[roomNumber]->getDimX() / 2 -
                                                                            size.x / 2 - 20.f,
                                                                            static_cast<float>(position.y) *
                                                                            rooms[roomNumber]->getDimY() +
                                                                            rooms[roomNumber]->getDimY() / 2 -
                                                                            size.y / 2 - 15.f),
                                                               std::move(animation));
        rooms[roomNumber]->addItem(item_d);
        std::vector<AttackTarget *> newTargets;
        newTargets.push_back(player.generateTarget());

        /*for (auto &r: rooms) {
            for (auto &e: r->getEnemies()) {
                e->addTargets(newTargets);
            }
        }*/
    } else if (type == GLIDINGDROID) {
        auto text = new sf::Texture;
        text->loadFromFile("./images/staticdroid.png");
        auto text2 = new sf::Texture;
        text2->loadFromFile("./images/jb_spritesheetnew.png");
        auto animation = std::make_unique<Animation>(text, sf::Vector2i(1, 1), 0.30f, size * 1.3f);
        std::unique_ptr<Movement> playerMovement = std::make_unique<GlidingMovement>(380, sf::Vector2f(
                                                                                             position.x * rooms[currentRoom]->getDimX(),
                                                                                             position.y * rooms[currentRoom]->getDimY()), sf::Vector2f(120, 126), 2000, player.spritePointer(),
                                                                                     true);
        playerMovement->addWalls(rooms[currentRoom]->getWalls());
        auto playerAttack = std::make_unique<RangedAttack>(sf::Vector2f(40.f, 40.f), 400.5f, 1.0f, 2.f,
                                                           150.f, 0.3f, player.spritePointer(), true);
        std::unique_ptr<Animation> playerAnimation = std::make_unique<Animation>(text2, sf::Vector2i(5, 4), 0.3f,
                                                                                 sf::Vector2f(168, 126) / 1.1f, true,
                                                                                 player.spritePointer());
        std::unique_ptr<SpecialAbility> playerSpecialAbility = std::make_unique<NoSpecialAbility>();
        //std::unique_ptr<Attack> playerAttack = std::make_unique<MeleeAttack>(sf::Vector2f (120.f,126.f),0.5f,1,200.f,
        //                                                                     0.f,40.f,player.spritePointer());
        playerAttack->addTargets(rooms[currentRoom]->getTargets());
        playerAttack->attach(achievementCounter);
        std::unique_ptr<Item> item_d = std::make_unique<Droid>(std::move(playerAnimation), std::move(playerMovement),
                                                               std::move(playerAttack), std::move(playerSpecialAbility),
                                                               size * 1.3f,
                                                               sf::Vector2f(static_cast<float>(position.x) *
                                                                            rooms[roomNumber]->getDimX() +
                                                                            rooms[roomNumber]->getDimX() / 2.f
                                                                            - size.x / 2 - 20.f,
                                                                            static_cast<float>(position.y) *
                                                                            rooms[roomNumber]->getDimY() +
                                                                            rooms[roomNumber]->getDimY() / 2.f
                                                                            - size.y / 2 - 20.f),
                                                               std::move(animation));
        rooms[roomNumber]->addItem(item_d);
        std::vector<AttackTarget *> newTargets;
        newTargets.push_back(player.generateTarget());

        /*for (auto &r: rooms) {
            for (auto &e: r->getEnemies()) {
                e->addTargets(newTargets);
            }
        }*/
    }

}


TileMap::~TileMap() {
    for (auto &t: textures) {
        delete t;
    }
}

