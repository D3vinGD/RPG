//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include "../Item/Item.h"

#include <vector>

struct Action;
class Enemy;
class Item;

class Player: public Character {
protected:
    bool warning;
    vector<unique_ptr<Item>> Items;
public:
    Player(char _name[], int _health, int _attack, int _defense, int _speed);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;

    Character* getTarget(vector<Enemy*> enemies);

    void flee(vector<Enemy*> enemies);
    void emote(vector<Enemy*> enemies);
    void showItems(const vector<unique_ptr<Item>>& items);
    void levelUp() override;
    void gainExperience(int);

    Action takeAction(vector<Enemy*> enemies);


};


#endif //RPG_PLAYER_H
