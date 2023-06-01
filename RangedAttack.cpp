#include "RangedAttack.h"

RangedAttack::RangedAttack(sf::Vector2f newBulletSize, float newBulletSpeed, float attackSpeed, float hitDamage,
                           float newKnockback, float delay, unsigned short *typeOfSprite, bool isPlayer) :
        Attack(sf::Vector2f(50.f, 50.f), attackSpeed, delay, hitDamage, newKnockback, typeOfSprite),
        bulletSize(newBulletSize), bulletSpeed(newBulletSpeed) {

    texture = new sf::Texture;
    if (isPlayer)
        texture->loadFromFile("./images/bulletplayer.png");
    else
        texture->loadFromFile("./images/bulletenemy.png");


    bullets.emplace_back(bulletSize, bulletSpeed, damage, knockback, texture, 3);

}

void RangedAttack::doDamage() {

    bullets.emplace_back(bulletSize, bulletSpeed, damage, knockback, texture, 3);
    auto i = bullets.begin();
    while (i != bullets.end() and (*i).isActive()) i++;
    if (i != bullets.end()) (*i).shoot(nextBulletStartPosition, nextBulletDirection);

}

void RangedAttack::hit(sf::Vector2f direction) {


    Attack::hit();
    nextBulletDirection = direction;

    /*
    if (cooldown.getElapsedTime().asSeconds() > attackSpeed) {
        cooldown.restart();
        auto i = bullets.begin();
        while (i != bullets.end() and (*i).isActive()) i++;
        if (i != bullets.end()) (*i).shoot(nextBulletStartPosition, direction);
        bullets.emplace_back(bulletSize, bulletSpeed, damage, knockback, texture);
    */
}


void RangedAttack::update(const float &dt, sf::Vector2f centerPosition, bool facingRight,
                          const std::vector<std::shared_ptr<LevelTile>> &walls) {

    Attack::update(dt, centerPosition, facingRight, walls);
    hitBox.setPosition(centerPosition - hitBox.getSize() / 2.f);


    for (auto &b: bullets) {

        auto i=b.update(dt,targets,walls);
        if (i!=targets.end()){

            if ((*i)->getBoss())
                Attack::notify(BOSSKILLED);
            else
                Attack::notify(ENEMYKILLED);
            targets.erase(i);
        }
    }


    auto j = bullets.begin();
    while (j != bullets.end()) {
        if (j->isCollided()) {
            j = bullets.erase(j);
        } else {
            ++j;
        }
    }

    nextBulletDirection = sf::Vector2f(facingRight ? 1.f : -1.f, 0.f);
    nextBulletStartPosition = centerPosition - hitBox.getSize() / 2.f;

}

void RangedAttack::render(sf::RenderTarget &target) {

    for (auto &b: bullets) {

        if (b.isActive())
            b.render(target);
    }
}

void RangedAttack::clearRelatedObjects() {
    bullets.clear();
}


