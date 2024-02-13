//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../Character/Character.h"

class Player: public Character {
protected:
    int experience;
    int level;
public:
    Player(string, int, int, int, int);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;

    void flee();
    void emote();
    void levelUp();
    void gainExperience(int);
};


#endif //RPG_PLAYER_H
