//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H

#include "../Character/Character.h"

class Player: Character {
protected:
    int experience;
    int level;
public:
    void doAttack(Character *target) override;
    void flee();
    void emote();
    void levelUp();
    void gainExperience(int);
};


#endif //RPG_PLAYER_H
