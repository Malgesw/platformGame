//
// Created by seren on 04/09/2022.
//
#include "lib/googletest/include/gtest/gtest.h"
#include "../TileMap.h"
#include "../GameCharacter.h"
#include "../AutoMovement.h"
#include "../AutoRanged.h"
#include <map>


class Maptest : public ::testing::Test {
public:
    std::unique_ptr<GameCharacter> player;
    std::vector<std::shared_ptr<LevelTile>> walls;
    std::shared_ptr<LevelTile> tile;
    std::shared_ptr<LevelTile> tile2;
    std::unique_ptr<GameCharacter> enemy;
    std::unique_ptr<Movement> automovement;
    std::vector<AttackTarget *> targets;

    Maptest() {
        auto tileTexture = new sf::Texture;
        //auto sprite = IDLERIGHT;
        tileTexture->loadFromFile("./images/playerSheet.png");
        tile = std::make_shared<LevelTile>(tileTexture, 100.f, 0.f, sf::Vector2f(50.f, 50.f), 1);
        walls.push_back(tile);
        tile2 = std::make_shared<LevelTile>(tileTexture, 300.f, 0.f, sf::Vector2f(50.f, 50.f), 0);
        player = std::make_unique<GameCharacter>(50, 50);
        auto playerTexture = new sf::Texture;
        playerTexture->loadFromFile("./images/playerSheet.png");
        //std::unique_ptr<Movement> playerMovement = std::make_unique<WalkingMovement>(80, sf::Vector2f(50.f, 50.f),
        //                                                                             sf::Vector2f(50, 50), 200,
        //                                                                             player->spritePointer());
        std::unique_ptr<Movement> playerMovement = std::make_unique<FlyingMovement>(80, sf::Vector2f(50.f, 50.f),
                                                                                    sf::Vector2f(50, 50),
                                                                                    player->spritePointer(), true);
        std::unique_ptr<Attack> playerAttack = std::make_unique<MeleeAttack>(sf::Vector2f(45.f, 35.f), 0.5f, 1, 49.f,
                                                                             0.0f, 0.f,
                                                                             player->spritePointer());
        auto playerAnimation = std::make_unique<Animation>(playerTexture, sf::Vector2i(5, 3), 0.3f,
                                                           sf::Vector2f(35, 35), true,
                                                           player->spritePointer());
        player->setMovement(std::move(playerMovement));
        player->setAttack(std::move(playerAttack));
        player->setAnimation(std::move(playerAnimation));
        player->addWalls(walls);
        enemy = std::make_unique<GameCharacter>(50, 50);
        std::unique_ptr<Movement> enemyMovement = std::make_unique<AutoFlying>(80, sf::Vector2f(50.f, 50.f),
                                                                               sf::Vector2f(25, 35),
                                                                               walls, sf::Vector2f(
                        tile->getGlobalBounds().width,
                        tile->getGlobalBounds().height),
                                                                               enemy->spritePointer(),
                                                                               sf::Vector2f(16, 16));
        std::unique_ptr<Attack> enemyAttack = std::make_unique<AutoRanged>(sf::Vector2f(50.f, 50.f), 100, 0.5f, 5.f,
                                                                           50.f, 0.f, player->spritePointer(), 400.f);
        auto enemyAnimation = std::make_unique<Animation>(playerTexture, sf::Vector2i(5, 3), 0.3f, sf::Vector2f(35, 35),
                                                          false,
                                                          enemy->spritePointer());
        enemy->setMovement(std::move(enemyMovement));
        enemy->setAttack(std::move(enemyAttack));
        enemy->setAnimation(std::move(enemyAnimation));
        enemy->addWalls(walls);
    }
};

TEST_F(Maptest, Boundariestest) {
    auto bounds = player->getGlobalBounds();
    auto objectbounds = tile->getGlobalBounds();
    player->setPosition(101.f, 0.f);
    EXPECT_TRUE(player->isColliding());
    EXPECT_TRUE(std::abs(player->getPosition().x - objectbounds.left - bounds.width) <= 0.1f);
    player->setPosition(130.f, 0.f);
    EXPECT_TRUE(player->isColliding());
}

TEST_F(Maptest, Tiletest){
    EXPECT_EQ(tile->getTileType(), WALL);
    EXPECT_EQ(tile2->getTileType(), GROUND);
}


