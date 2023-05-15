//
// Created by alessio on 14/05/23.
//

#include "lib/googletest/include/gtest/gtest.h"
#include "../GameCharacter.h"
#include "../TileMap.h"

class ItemTest : public ::testing::Test {
public:
    std::unique_ptr<GameCharacter> player;
    std::vector<std::shared_ptr<LevelTile>> walls;
    std::shared_ptr<LevelTile> tile;
    std::shared_ptr<LevelTile> tile2;
    std::shared_ptr<LevelTile> tile3;
    std::unique_ptr<Item> taco;
    std::unique_ptr<Item> deathZone;
    std::unique_ptr<Item> droid;

    ItemTest() {

        auto tileTexture = new sf::Texture;
        tileTexture->loadFromFile("./images/playerSheet.png");
        tile = std::make_shared<LevelTile>(tileTexture, 0.f, 50.f, sf::Vector2f(50.f, 50.f), 1);
        tile2 = std::make_shared<LevelTile>(tileTexture, 100.f, 50.f, sf::Vector2f(50.f, 50.f), 1);
        tile3 = std::make_shared<LevelTile>(tileTexture, 200.f, 50.f, sf::Vector2f(50.f, 50.f), 1);
        walls.push_back(tile);
        walls.push_back(tile2);
        walls.push_back(tile3);
        auto playerTexture = new sf::Texture;
        playerTexture->loadFromFile("./images/playerSheet.png");
        player = std::make_unique<GameCharacter>(50, 50);
        std::unique_ptr<Movement> playerMovement = std::make_unique<WalkingMovement>(80, sf::Vector2f(50.f, 50.f),
                                                                                     sf::Vector2f(25, 35), 200,
                                                                                     player->spritePointer());
        std::unique_ptr<Attack> playerAttack = std::make_unique<MeleeAttack>(sf::Vector2f(45.f, 35.f), 0.5f, 1, 49.f,
                                                                             0.0f, player->spritePointer());
        auto playerAnimation = std::make_unique<Animation>(playerTexture, sf::Vector2i(5, 3), 0.3f,
                                                           sf::Vector2f(35, 35), true, player->spritePointer());
        player->setMovement(std::move(playerMovement));
        player->setAttack(std::move(playerAttack));
        player->setAnimation(std::move(playerAnimation));
        player->addWalls(walls);
        std::unique_ptr<Movement> droidMovement = std::make_unique<WalkingMovement>(80, sf::Vector2f(50.f, 50.f),
                                                                                    sf::Vector2f(25, 35), 200,
                                                                                    player->spritePointer());
        std::unique_ptr<Attack> droidAttack = std::make_unique<MeleeAttack>(sf::Vector2f(45.f, 35.f), 0.5f, 1, 49.f,
                                                                            0.0f, player->spritePointer());
        auto droidAnimation = std::make_unique<Animation>(playerTexture, sf::Vector2i(5, 3), 0.3f, sf::Vector2f(35, 35),
                                                          true, player->spritePointer());
        auto tacoTexture = new sf::Texture;
        tacoTexture->loadFromFile("./images/taco.png");
        auto tacoAnimation = std::make_unique<Animation>(tacoTexture, sf::Vector2i(4, 1), 0.3f, sf::Vector2f(50, 50));
        taco = std::make_unique<Item>(sf::Vector2f(50.f, 50.f), sf::Vector2f(0.f, 0.f), std::move(tacoAnimation), 1);
        deathZone = std::make_unique<Item>(sf::Vector2f(50.f, 50.f), sf::Vector2f(100.f, 0.f), std::move(tacoAnimation),
                                           -1000000);
        droid = std::make_unique<Droid>(std::move(droidAnimation), std::move(droidMovement), std::move(droidAttack),
                                        sf::Vector2f(50.f, 50.f), sf::Vector2f(0.f, 0.f), std::move(tacoAnimation));

    }
};

TEST_F(ItemTest, tacoTest) {
    player->setHp(30);
    player->setPosition(0.f, 0.f);
    taco->use(*player);
    EXPECT_TRUE(player->getHp() > 30);

}

TEST_F(ItemTest, deathZoneTest) {
    player->setPosition(100.f, 0.f);
    deathZone->use(*player);
    EXPECT_TRUE(player->getHp() <= 0);
}

TEST_F(ItemTest, DroidTest) {
    player->setPosition(200.f, 0.f);
    droid->use(*player);
    EXPECT_TRUE(player->savedComponentsPresent());

}
