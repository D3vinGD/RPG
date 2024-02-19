//
// Created by Victor Navarro on 19/02/24.
//
#include "Combat.h"
#include <iostream>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
}

void Combat::prepareCombat() {
    sort(participants.begin(), participants.end(), compareSpeed);
}

void Combat::doCombat() {
    prepareCombat();

    while(participants.size() > 1) {
        vector<Character*>::iterator participant;

        for(participant = participants.begin(); participant != participants.end(); participant++) {
            Character* target = getTarget(*participant);
            (*participant)->doAttack(target);

            if(target->getHealth() <= 0) {
                participant = participants.erase(remove(participants.begin(), participants.end(), target), participants.end());
            }
        }
    }

    //No se imprime el nombre del ganador
    cout << participants[0]->getName() << " has won the combat!" << endl;
}

Character* Combat::getTarget(Character* attacker) {
    for(auto &participant: participants) {
        if(participant->getIsPlayer() != attacker->getIsPlayer()) {
            return participant;
        }
    }
    return nullptr;
}

string Combat::participantsToString() {
    string result = "";
    for (int i = 0; i < participants.size(); i++) {
        result += participants[i]->toString() + "\n";
    }
    return result;
}