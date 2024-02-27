//
// Created by Victor Navarro on 19/02/24.
//
#include "Combat.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant: participants) {
        if(participant->getIsPlayer()) {
            teamMembers.push_back((Player*)participant);
        }
        else {
            enemies.push_back((Enemy*)participant);
        }
    }
}

Combat::Combat(vector<Player*> _teamMembers, vector<Enemy*> _enemies) {
    teamMembers = std::move(_teamMembers);
    enemies = std::move(_enemies);
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()) {
        teamMembers.push_back((Player*)participant);
    }
    else {
        enemies.push_back((Enemy*)participant);
    }
}

void Combat::prepareCombat() {
    sort(participants.begin(), participants.end(), compareSpeed);
}

void Combat::doCombat() {
    prepareCombat();

    //Este while es 1 iteracion por ronda
    while(enemies.size() != 0 && teamMembers.size() != 0) {
        vector<Character*>::iterator participant = participants.begin();

        //Una iteracion por turno de cada participante (player y enemigo)
        while(participant != participants.end()) {
            Character* target = nullptr;
            Action currentAction;
            if((*participant)->getIsPlayer()) {
                currentAction = ((Player*)*participant)->takeAction(enemies);
            }
            else {
                currentAction = ((Enemy*)*participant)->takeAction(teamMembers);
            }
            actions.push(currentAction);
            participant++;
        }
        //Aqui se ejecutan las acciones
        while(!actions.empty()) {
            Action currentAction = actions.top();
            currentAction.action();
            actions.pop();
        }
    }

    //No se imprime el nombre del ganador
    if(enemies.size() == 0) {
        cout<<"You have won the combat"<<endl;
    }
    else {
        cout<<"The enemies have won the combat - Game Over"<<endl;
    }
}

string Combat::participantsToString() {
    string result = "";
    for (int i = 0; i < participants.size(); i++) {
        result += participants[i]->toString() + "\n";
    }
    return result;
}