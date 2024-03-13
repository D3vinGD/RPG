//
// Created by Victor Navarro on 19/02/24.
//
#include "Combat.h"
#include <iostream>
#include <algorithm>
#include <vector>

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define CYAN    "\033[36m"      /* Cyan */
#define ORANGE "\033[38;5;208m" /* Orange */

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
        registerActions();
        executeActions();
    }

    //No se imprime el nombre del ganador
    if(enemies.size() == 0) {
        cout<< GREEN <<"\n\t{ You have won the combat }"<< RESET <<endl;
    }
    else {
        cout<< RED <<"\n\t{ The enemies have won the combat - Game Over }"<< RESET <<endl;
    }
}

void Combat::registerActions() {
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
}

void Combat::executeActions() {
    //Aqui se ejecutan las acciones
    while(!actions.empty()) {
        Action currentAction = actions.top();
        currentAction.action();
        checkForFlee(currentAction.subscriber);
        if (currentAction.target != nullptr) {
            checkParticipantStatus(currentAction.subscriber);
            checkParticipantStatus(currentAction.target);
            actions.pop();
        }
        else if(currentAction.subscriber->hasFleed())
        {
            while (!actions.empty()) {
                actions.pop();
            }
        }
        else
        {
            actions.pop();
        }
        
    }
}

void Combat::checkParticipantStatus(Character* participant) {
    if(participant->getHealth() <= 0) {
        if(participant->getIsPlayer()) {
            teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), participant), teamMembers.end());
        }
        else {
            enemies.erase(remove(enemies.begin(), enemies.end(), participant), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), participant), participants.end());
    }
}

void Combat::checkForFlee(Character *character) {
    bool fleed = character->hasFleed();
    if(fleed) {
        if(character->getIsPlayer()) {

            cout << CYAN << "\t>" << character->getName() << " has fled the combat" << RESET << endl;
            teamMembers.erase(remove(teamMembers.begin(), teamMembers.end(), character), teamMembers.end());
        }
        else {
            cout<< CYAN<< "\t>" << character->getName() << " has fled the combat" << RESET << endl;
            enemies.erase(remove(enemies.begin(), enemies.end(), character), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), character), participants.end());
    }
    
}

string Combat::participantsToString() {
    string result = "";
    for (int i = 0; i < participants.size(); i++) {
        result += participants[i]->toString() + "\n";
    }
    return result;
}