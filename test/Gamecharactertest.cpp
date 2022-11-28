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
        auto tileTexture=new sf::Texture;
        tileTexture->loadFromFile("./images/playerSheet.png");
        tile=std::make_shared<LevelTile>(tileTexture,0.f,0.f, sf::Vector2f(50.f,50.f),1);
        walls.push_back(tile);
        auto playerTexture=new sf::Texture;
        playerTexture->loadFromFile("./images/playerSheet.png");
        player= std::make_unique<GameCharacter>(50, 50);
        std::unique_ptr<Movement> playerMovement=std::make_unique<WalkingMovement>(80,sf::Vector2f (50.f,50.f),sf::Vector2f (25,35),200);
        std::unique_ptr<Attack> playerAttack=std::make_unique<MeleeAttack>(sf::Vector2f (45.f,35.f),0.5f,1,49.f);
        auto playerAnimation=std::make_unique<Animation>(playerTexture, sf::Vector2i(5, 3), 0.3f, sf::Vector2f (35,35),true);
        player->setMovement(std::move(playerMovement));
        player->setAttack(std::move(playerAttack));
        player->setAnimation(std::move(playerAnimation));
        player->getMovement().addWalls(walls);

    }
};
TEST_F(Gamecharactertest, playeronground){
    player->getMovement().getCollisions().setPosition(0.f,50.f);
    EXPECT_TRUE(player->getMovement().onGround());
}
