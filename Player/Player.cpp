//
// Created by Victor Navarro on 13/02/24.
//
#include "Player.h"
#include <iostream>
#include "../Utils.h"
#include <algorithm>
#include "..\colors.h"

using namespace std;
using namespace combat_utils;

bool compareSpeed(Enemy *a, Enemy *b) {
    return a->getSpeed() > b->getSpeed();
}

Player::Player(char name[], int health, int attack, int defense, int speed) : Character(name, health, attack, defense,
                                                                                        speed, XpReward, true) {
    experience = 0;
    level = 1;
    maxHealth = health;
    warning = false;
}

void Player::doAttack(Character *target) {
    int rolledAttack = getRolledAttack(getAttack());
    bool CriticalHit = false;
    if (rolledAttack > attack * 0.85) {
        CriticalHit = true;
    }
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
    if (CriticalHit && (target->getHealth() > 0)) {
        cout << GREEN << "  [ Critical Hit! ]" << RESET << endl;
        CriticalHit = false;
    }
    else
    {
        cout << endl;
    }
    if ((target->getHealth() <= 0) && !(target->hasFleed()))
    {
        kills++;
        cout << YELLOW <<"\t" << getName() << ", you get " << target->getXpReward() << "XP" << RESET << endl;
        gainExperience(target->getXpReward());
        
    }
    
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    cout << RED << "\t(-) " << name << " have taken " << damage << " damage" << RESET << endl;

    if (health <= maxHealth * 0.30 && warning == false) {
        cout << ORANGE << "\t(!!!)" << name << ", your health is low, be careful" << RESET << endl;
        warning = true;
    }

    if (health <= 0) {
        cout << MAGENTA << "\n\t(~) " << name << " have died" << RESET << endl;
    }
}

void Player::flee(vector<Enemy *> enemies) {
    std::sort(enemies.begin(), enemies.end(), compareSpeed);
    Enemy *fastestEnemy = enemies[0];
    bool fleed = false;
    if (this->getSpeed() > fastestEnemy->getSpeed()) {
        fleed = true;
    } else {
        srand(time(NULL));
        int chance = rand() % 100;
        fleed = chance > 80;
        if ((fleed == false) && (this->getHealth() > 0)) {
            cout << ORANGE << "\t("<<chance<<"%/80) You couldn't fleed" << RESET << endl;
        }
    }

    this->fleed = fleed;
}

void Player::emote(vector<Enemy*> enemies) {
    cout << MAGENTA << "\t" << getName() << ": * Does T-bag *" << RESET << endl;

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->setDefense(enemies[i]->getDefense() - 2 );
    }
    cout << MAGENTA << "\t(*) All enemies defense has been diminished" << RESET << endl;

    kills = 0;
}

void Player::levelUp() {
    level++;
    setHealth(getHealth() + 10);
    setAttack(getAttack() + 2);
    setDefense(getDefense() + 1);
    setSpeed(getSpeed() + 3);

    if ((health >= maxHealth * 0.30)&&(warning == true)) {
        cout << ORANGE << "\t(!)" << getName() << ", nevermind you level up" << RESET << endl;
        warning = false;
    }

    cout << YELLOW << "\t(^)" << getName() << ", your level has gone up to "<< level << RESET << endl;
    
}

void Player::gainExperience(int exp) {
    const int maxExperience = 100;

    if (exp > (maxExperience - experience)) {

        int remainingExp = exp - (maxExperience - experience);
        levelUp();
        experience = remainingExp;
    }
    else {
        experience += exp;
    }
    if (experience >= maxExperience) {
        levelUp();
        experience = 0;
    }

}

Character *Player::getTarget(vector<Enemy *> enemies) {
    cout << "\t\t| Choose a target |\n" << endl;
    int targetIndex = 0;
    do
    {
        for (int i = 0; i < enemies.size(); i++) {
            cout << i << ". " << enemies[i]->getName() << "\t" << enemies[i]->getLifeBar()<< "\t\tExp Reward: "<< enemies[i]->getXpReward() << endl;
        }
        cin >> targetIndex;

    } while (  !(targetIndex >= 0 && targetIndex < enemies.size()) );
    
    return enemies[targetIndex];
}

Action Player::takeAction(vector<Enemy *> enemies) {
    int option = 0;
    bool actionTaked = false;
    Character* target = nullptr;
    Action myAction;

    myAction.speed = this->getSpeed();
    myAction.subscriber = this;

    while (actionTaked == false) {
        cout << "\n==<>==<>==<>==[ " << getName() << ", choose an action ]==<>==<>==<>==" << endl;
        cout << "\t Life: " << getLifeBar() << "\n\t\tAtk: "<<getAttack()<< "\tDef: "<<getDefense()<< "\tVel: "<<getSpeed()<< endl;
    
        if (getKills() <= 0)
        {
            cout << RED << "\n\t1. Attack\t" << RESET;
            cout << CYAN << "2. Flee\t" << RESET << endl;
        }
        else
        {
            cout << RED << "\n\t1. Attack\t" << RESET;
            cout << CYAN << "2. Flee\t" << RESET;
            cout << MAGENTA << "\t3. Emote" << RESET << endl;
        }
       

            cin >> option;
        switch (option) {
        case 1:
            target = getTarget(enemies);
            myAction.target = target;
            //1.
            myAction.action = [this, target]() {
                doAttack(target);
                };
                actionTaked = true;
            break;
        case 2:
            myAction.action = [this, enemies]() {
                flee(enemies);
            };
            actionTaked = true;
            break;
        case 3:
            if (kills > 0) {
                myAction.action = [this, enemies]() {
                    emote(enemies);
                };
                actionTaked = true;
            }
            else {
                system("cls");
            }
            break;
        default:
            system("cls");
            break;
        }
    }

    return myAction;
}