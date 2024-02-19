//
// Created by Victor Navarro on 19/02/24.
//

#ifndef RPG_COMBAT_H
#define RPG_COMBAT_H
#pragma once
#include "../Character/Character.h"
#include <vector>
#include <string>

using namespace std;

class Combat {
private:
    vector<Character*> participants;
    void prepareCombat();
    Character* getTarget(Character* attacker);
public:
    Combat(vector<Character*> _participants);
    Combat();
    void addParticipant(Character *participant);
    void doCombat();
    string participantsToString();
};


#endif //RPG_COMBAT_H
