#include "lib/googletest/include/gtest/gtest.h"
#include "../TileMap.h"
#include <map>


class EnemyTest : public ::testing::Test {
public:
    std::unique_ptr<GameCharacter> player;
    std::vector<std::shared_ptr<LevelTile>> walls;
    std::shared_ptr<LevelTile> tile;
    std::shared_ptr<LevelTile> tile2;
    std::unique_ptr<GameCharacter> enemy;
    std::unique_ptr<Movement> automovement;
    std::vector<AttackTarget *> targets;
    std::list<AttackTarget *> targetsList;
    std::vector<AttackTarget *> enemyTargets;
    std::unique_ptr<Bullet> projectile;


    EnemyTest() {
        auto tileTexture = new sf::Texture;
        tileTexture->loadFromFile("./images/playerSheet.png");
        tile = std::make_shared<LevelTile>(tileTexture, 0.f, 50.f, sf::Vector2f(50.f, 50.f), 1);
        walls.push_back(tile);
        tile2 = std::make_shared<LevelTile>(tileTexture, 300.f, 50.f, sf::Vector2f(50.f, 50.f), 1);
        walls.push_back(tile2);
        player = std::make_unique<GameCharacter>(50, 50);
        auto playerTexture = new sf::Texture;
        playerTexture->loadFromFile("./images/playerSheet.png");
        std::unique_ptr<Movement> playerMovement = std::make_unique<FlyingMovement>(80, sf::Vector2f(500.f, 500.f),
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
        std::unique_ptr<Attack> enemyAttack = std::make_unique<AutoMelee>(sf::Vector2f(600.f, 600.f), 0.5f, 1, 49.f,
                                                                          0.0f, 0.f,
                                                                          player->spritePointer());
        auto enemyAnimation = std::make_unique<Animation>(playerTexture, sf::Vector2i(5, 3), 0.3f, sf::Vector2f(35, 35),
                                                          false,
                                                          enemy->spritePointer());
        enemy->setMovement(std::move(enemyMovement));
        enemy->setAttack(std::move(enemyAttack));
        enemy->setAnimation(std::move(enemyAnimation));
        targets.push_back(player->generateTarget());
        targetsList.push_back(player->generateTarget());
        enemy->addWalls(walls);
        enemy->addTargets(targets);
        enemyTargets.push_back(enemy->generateTarget());
        player->addTargets(enemyTargets);
        projectile = std::make_unique<Bullet>(sf::Vector2f(50.f, 50.f), 100.f, 1.f, 20.f, playerTexture, 3, 30000.f);
    }
};

TEST_F(EnemyTest, BulletTest) {
    projectile->shoot(sf::Vector2f(100.f, 50.f), sf::Vector2f(1, 0));
    player->update(0.01, walls, player->getPosition());
    for (int i = 0; i < 100000; i++) projectile->update(0.01, targetsList, walls);
    EXPECT_TRUE(projectile->isCollided());

}

TEST_F(EnemyTest, PathFinderTest) {
    player->setPosition(100.f, 50.f);
    enemy->setPosition(400.f, 50.f);
    targets.push_back(player->generateTarget());
    enemy->addTargets(targets);
    enemy->addWalls(walls);
    sf::Clock time;
    while ((std::abs(player->getPosition().x - enemy->getPosition().x) > 20.f or
            std::abs(player->getPosition().y - enemy->getPosition().y) > 20.f) and
           time.getElapsedTime().asSeconds() < 10) {
        player->update(0.01f, walls, player->getPosition());
        enemy->update(0.01f, walls, player->getPosition());
    }

    enemy->update(0.01f, walls, player->getPosition());
    player->update(0.01f, walls, player->getPosition());


    EXPECT_TRUE(std::abs(player->getPosition().x - enemy->getPosition().x) <= 25.f and
                std::abs(player->getPosition().y - enemy->getPosition().y) <= 25.f);


}

TEST_F(EnemyTest, AttackTest) {
    float startHp = player->getHp();
    player->setPosition(100.f, 50.f);
    enemy->setPosition(100.f, 50.f);
    for (int i = 0; i < 3; i++) {
        player->update(0.01f, walls, player->getPosition());
        enemy->update(0.01f, walls, player->getPosition());
        sf::sleep(sf::seconds(
                0.5f)); //necessario poichè l'attacco utilizza un sistema di delay per sincronizzarsi con l'animazione
    }
    EXPECT_TRUE(player->getHp() < startHp);
}