//
// Created by seren on 08/09/2022.
//
#include "lib/googletest/include/gtest/gtest.h"
#include "../GameCharacter.h"
#include "../TileMap.h"

class Gamecharactertest : public ::testing::Test {
public:
    std::unique_ptr<GameCharacter> player;
    std::vector<std::shared_ptr<LevelTile>> walls;
    std::shared_ptr<LevelTile> tile;
    Gamecharactertest(){
        tile=std::make_shared<LevelTile>('1',0.f,0.f, sf::Vector2f(50.f,50.f));
        walls.push_back(tile);
        player= std::make_unique<GameCharacter>(sf::Vector2f(0.f,50.f), sf::Vector2f(50.f,50.f),50, 50);

    }
};
TEST_F(Gamecharactertest, playeronground){
    player->getMovement()->getCollisions().setPosition(0.f,50.f);
    EXPECT_TRUE(player->getMovement()->onGround());
}
