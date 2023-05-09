#ifndef PLATFORMGAME_ATTACK_H
#define PLATFORMGAME_ATTACK_H



#include "headers.h"
#include "AttackTarget.h"
#include "Subject.h"
#include "spriteType.h"
#include "LevelTile.h"

class GameCharacter;

class Attack :public Subject{

public:

    Attack(sf::Vector2f size, float speed, float delay, int hitDamage, float knockback, unsigned short *typeOfSprite);

    ~Attack() override = default;

    sf::RectangleShape &getHitBox();

    void addTargets(const std::vector<AttackTarget *> &newTargets);

    void clearTargets();

    void attach(Observer *o) override;

    void detach(Observer *o) override;

    void notify(unsigned short category) const override;

    void hit();

    virtual void update(const float &dt, sf::Vector2f centerPosition, bool orientation,
                        const std::vector<std::shared_ptr<LevelTile>> &walls) = 0;

    virtual void render(sf::RenderTarget &target) = 0;


protected:

    virtual void doDamage() = 0;

    bool incomingAttack = false;
    sf::Clock cooldown;
    sf::Clock delay;
    float attackSpeed;
    float attackDelay;
    int damage;
    float knockback;
    sf::RectangleShape hitBox;
    std::list<AttackTarget *> targets;
    std::list<Observer *> observers;
    unsigned short *typeOfSprite;

    bool checkDeath(AttackTarget *target) const;
};


#endif //PLATFORMGAME_ATTACK_H
