#ifndef PLATFORMGAME_ATTACK_H
#define PLATFORMGAME_ATTACK_H



#include "headers.h"
#include "AttackTarget.h"
#include "Subject.h"
#include "spriteType.h"
#include "LevelTile.h"


class Attack :public Subject{

public:

    Attack(sf::Vector2f size, float speed, int hitDamage, float knockback, unsigned short *typeOfSprite);
    ~Attack() override = default;
    sf::RectangleShape &getHitBox();
    void addTargets(const std::vector<AttackTarget> &newTargets);
    void clearTargets();
    void attach(Observer *o) override;    void detach(Observer *o) override;
    void notify(char category) const override;
    virtual void hit() = 0;
    virtual void update(const float &dt, sf::Vector2f centerPosition, bool orientation,const std::vector<std::shared_ptr<LevelTile>> &walls)=0;
    virtual void render(sf::RenderTarget &target)=0;


protected:
    sf::Clock cooldown;
    float attackSpeed;
    int damage;
    float knockback;
    sf::RectangleShape hitBox;
    std::list<AttackTarget> targets;
    std::list<Observer *> observers;
    unsigned short *typeOfSprite;
    int targetscount = 0;
public:
    int getTargetscount() const;

protected:

    bool checkDeath(const AttackTarget &target) const;
};


#endif //PLATFORMGAME_ATTACK_H
