//
// Created by alessio on 14/05/23.
//


#include "lib/googletest/include/gtest/gtest.h"
#include "../TileMap.h"
#include "../GameCharacter.h"
#include "../AutoMovement.h"
#include "../AutoRanged.h"
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
    std::unique_ptr<Bullet> projectile;


    EnemyTest() {
        auto tileTexture = new sf::Texture;
        //auto sprite = IDLERIGHT;
        tileTexture->loadFromFile("./images/playerSheet.png");
        tile = std::make_shared<LevelTile>(tileTexture, 0.f, 50.f, sf::Vector2f(50.f, 50.f), 1);
        walls.push_back(tile);
        tile2 = std::make_shared<LevelTile>(tileTexture, 300.f, 50.f, sf::Vector2f(50.f, 50.f), 1);
        walls.push_back(tile2);
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
                                                                               enemy->spritePointer());
        std::unique_ptr<Attack> enemyAttack = std::make_unique<AutoMelee>(sf::Vector2f(60.f, 60.f), 0.5f, 1, 49.f,
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
        projectile = std::make_unique<Bullet>(sf::Vector2f(50.f, 50.f), 100.f, 1.f, 20.f, playerTexture, 3);
    }
};

TEST_F(EnemyTest, BulletTest) {
    projectile->shoot(sf::Vector2f(100.f, 50.f), sf::Vector2f(1, 0));
    player->update(0.01, walls, player->getPosition());
    for (int i = 0; i < 100000; i++) projectile->update(0.01, targetsList, walls);
    EXPECT_TRUE(projectile->isCollided());

}

TEST_F(EnemyTest, Enemytest) {
    player->setPosition(100.f, 50.f);
    enemy->setPosition(400.f, 50.f);
    float startLife = player->getHp();
    targets.push_back(player->generateTarget());
    enemy->addTargets(targets);
    enemy->addWalls(walls);
    sf::Clock time;
    while ((std::abs(player->getPosition().x - enemy->getPosition().x) > 20.f or
            std::abs(player->getPosition().y - enemy->getPosition().y) > 20.f) and
           time.getElapsedTime().asSeconds() < 10) {
        player->update(0.01, walls, player->getPosition());
        enemy->update(0.01f, walls, player->getPosition());
    }

    enemy->update(0.01f, walls, player->getPosition());
    player->update(0.01f, walls, player->getPosition());
    //enemy->getAttack().update(0.01,player->getMovement().getCollisions().getPosition()+player->getMovement().getCollisions().getSize()/2.f,true, walls);




    EXPECT_TRUE(std::abs(player->getPosition().x - enemy->getPosition().x) <= 25.f and
                std::abs(player->getPosition().y - enemy->getPosition().y) <= 25.f);


}



/*
TEST_F(EnemyTest, MeleeAttackTest){
    player->setPosition(0,0);
    enemy->setPosition(0,0);
    player->update(0.01,walls,player->getPosition());
    enemy->hit();
    enemy->update(0.01,walls,player->getPosition());
    EXPECT_TRUE(player->getHp()<50.f);
}
*/