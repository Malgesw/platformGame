//
// Created by seren on 04/09/2022.
//
#include "lib/googletest/include/gtest/gtest.h"
#include "../TileMap.h"
#include "../GameCharacter.h"
#include <map>


class Maptest : public ::testing::Test {
public:
    std::unique_ptr<GameCharacter> player;
    std::vector<std::shared_ptr<LevelTile>> walls;
    std::shared_ptr<LevelTile> tile;
    Maptest(){
        tile=std::make_shared<LevelTile>('1',50.f,0.f, sf::Vector2f(50.f,50.f));
        walls.push_back(tile);
        player= std::make_unique<GameCharacter>(sf::Vector2f(0.f,0.f), sf::Vector2f(50.f,50.f), walls);

    }
};
TEST_F(Maptest, Boundariestest) {
   player->getMovement()->getCollisions().setPosition(50.f,0.f);
   EXPECT_TRUE(player->getMovement()->checkCollisions());
}

