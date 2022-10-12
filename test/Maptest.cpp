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
    std::shared_ptr<Movement> automovement;
    std::vector<AttackTarget> targets;

    Maptest(){
        tile=std::make_shared<LevelTile>('1',100.f,0.f, sf::Vector2f(50.f,50.f));
        walls.push_back(tile);
        tile2=std::make_shared<LevelTile>('0', 300.f,0.f,sf::Vector2f(50.f,50.f));
        player= std::make_unique<GameCharacter>(sf::Vector2f(50.f,0.f), sf::Vector2f(50.f,50.f), 50, 50);
        player->getMovement()->addWalls(walls);
        enemy= std::make_unique<GameCharacter>(sf::Vector2f(400.f,250.f), sf::Vector2f(50.f,50.f), 50, 50);
        automovement = std::make_shared<AutoFlying>(7, enemy->getMovement()->getPosition(), sf::Vector2f(50, 50), walls,sf::Vector2f (tile->getGlobalBounds().width,tile->getGlobalBounds().height));
    }
};

TEST_F(Maptest, Boundariestest) {
    auto bounds = player->getMovement()->getCollisions().getGlobalBounds();
    auto objectbounds = tile->getGlobalBounds();
    player->getMovement()->moveRight();
    EXPECT_TRUE(player->getMovement()->checkCollisions());
    EXPECT_TRUE(player->getMovement()->getCollisions().getPosition().x - objectbounds.left - bounds.width <= 0.1f);
    player->getMovement()->getCollisions().setPosition(130.f,0.f);
    EXPECT_TRUE(player->getMovement()->checkCollisions());
}

TEST_F(Maptest, Tiletest){
    EXPECT_EQ(tile->getTileType(), WALL);
    EXPECT_EQ(tile2->getTileType(), GROUND);
}

TEST_F(Maptest, Enemytest){
   enemy->setMovement(automovement);
   enemy->getMovement()->addWalls(walls);
   targets.push_back(player->generateTarget());
   EXPECT_TRUE(player->getMovement()->getPosition().x -enemy->getMovement()->getPosition().x<= 0.1f);
   EXPECT_TRUE(player->getMovement()->getPosition().y -enemy->getMovement()->getPosition().y<= 0.1f);
}

