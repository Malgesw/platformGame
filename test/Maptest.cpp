//
// Created by seren on 04/09/2022.
//
#include "lib/googletest/include/gtest/gtest.h"
#include "../TileMap.h"
#include "../GameCharacter.h"
#include "../AutoMovement.h"
#include <map>


class Maptest : public ::testing::Test {
public:
    std::unique_ptr<GameCharacter> player;
    std::vector<std::shared_ptr<LevelTile>> walls;
    std::shared_ptr<LevelTile> tile;
    std::shared_ptr<LevelTile> tile2;
    std::unique_ptr<GameCharacter> enemy;
    std::unique_ptr<Movement> automovement;
    std::vector<AttackTarget> targets;

    Maptest(){
        auto tileTexture=new sf::Texture;
        tileTexture->loadFromFile("./images/playerSheet.png");
        tile=std::make_shared<LevelTile>(tileTexture,100.f,0.f, sf::Vector2f(50.f,50.f),1);
        walls.push_back(tile);
        tile2=std::make_shared<LevelTile>(tileTexture, 300.f,0.f,sf::Vector2f(50.f,50.f),0);
        player= std::make_unique<GameCharacter>(50, 50);
        auto playerTexture=new sf::Texture;
        playerTexture->loadFromFile("./images/playerSheet.png");
        std::unique_ptr<Movement> playerMovement=std::make_unique<WalkingMovement>(80,sf::Vector2f (50.f,50.f),sf::Vector2f (50,50),200);
        std::unique_ptr<Attack> playerAttack=std::make_unique<MeleeAttack>(sf::Vector2f (45.f,35.f),0.5f,1,49.f);
        auto playerAnimation=std::make_unique<Animation>(playerTexture, sf::Vector2i(5, 3), 0.3f, sf::Vector2f (35,35),true);
        player->setMovement(std::move(playerMovement));
        player->setAttack(std::move(playerAttack));
        player->setAnimation(std::move(playerAnimation));
        player->getMovement().addWalls(walls);
        enemy= std::make_unique<GameCharacter>(50, 50);
        std::unique_ptr<Movement> enemyMovement=std::make_unique<AutoFlying>(80,sf::Vector2f (50.f,50.f),sf::Vector2f (25,35),
                                                                             walls,sf::Vector2f(tile->getGlobalBounds().width,
                                                                                                tile->getGlobalBounds().height));
        std::unique_ptr<Attack> enemyAttack=std::make_unique<AutoMelee>(sf::Vector2f (150.f,150.f),0.5f,1,35.f);
        auto enemyAnimation=std::make_unique<Animation>(playerTexture, sf::Vector2i(5, 3), 0.3f, sf::Vector2f (35,35),false);
        enemy->setMovement(std::move(enemyMovement));
        enemy->setAttack(std::move(enemyAttack));
        enemy->setAnimation(std::move(enemyAnimation));
        enemy->getMovement().addWalls(walls);
    }
};

TEST_F(Maptest, Boundariestest) {
    auto bounds = player->getMovement().getCollisions().getGlobalBounds();
    auto objectbounds = tile->getGlobalBounds();
    player->getMovement().getCollisions().setPosition(101.f,0.f);
    EXPECT_TRUE(player->getMovement().checkCollisions());
    EXPECT_TRUE(std::abs(player->getMovement().getCollisions().getPosition().x - objectbounds.left - bounds.width) <= 0.1f);
    player->getMovement().getCollisions().setPosition(130.f,0.f);
    EXPECT_TRUE(player->getMovement().checkCollisions());
}

TEST_F(Maptest, Tiletest){
    EXPECT_EQ(tile->getTileType(), WALL);
    EXPECT_EQ(tile2->getTileType(), GROUND);
}

TEST_F(Maptest, Enemytest){
    player->getMovement().getCollisions().setPosition(50.f,0.f);
    enemy->getMovement().getCollisions().setPosition(400.f,250.f);
    int startLife=player->getHp();
    targets.push_back(player->generateTarget());
    enemy->getAttack().addTargets(targets);
    sf::Clock time;
    while((std::abs(player->getMovement().getPosition().x - enemy->getMovement().getPosition().x) > 20.f or
    std::abs(player->getMovement().getPosition().y -enemy->getMovement().getPosition().y)> 20.f) and time.getElapsedTime().asSeconds()<25){
       enemy->update(0.01f,walls,player->getMovement().getCollisions().getPosition());
   }

   enemy->update(0.01f,walls,player->getMovement().getCollisions().getPosition());
   player->update(0.01f,walls,player->getMovement().getCollisions().getPosition());
   enemy->getAttack().update(player->getMovement().getCollisions().getPosition()+player->getMovement().getCollisions().getSize()/2.f,true);



   EXPECT_TRUE(enemy->getAttack().getHitBox().getGlobalBounds().intersects(player->getMovement().getCollisions().getGlobalBounds()));
   EXPECT_TRUE(std::abs(player->getMovement().getPosition().x -enemy->getMovement().getPosition().x)<= 25.f);
   EXPECT_TRUE(std::abs(player->getMovement().getPosition().y -enemy->getMovement().getPosition().y)<= 25.f);
   EXPECT_TRUE(player->getHp()<startLife);
}

