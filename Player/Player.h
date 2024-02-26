//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "./ActionResult.h"

class Enemy;

class Player: public Character {
protected:
    int experience;
    int level;
public:
    Player(string _name, int _health, int _attack, int _defense, int _speed);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* getTarget(vector<Enemy*> enemies);

    bool flee(vector<Enemy*> enemies);
    void emote();
    void levelUp();
    void gainExperience(int);
    ActionResult takeAction(vector<Enemy*> enemies);
};


#endif //RPG_PLAYER_H
