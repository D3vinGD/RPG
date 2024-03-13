//
// Created by Victor Navarro on 13/02/24.
//
#include "Player.h"
#include <iostream>
#include "../Utils.h"
#include <algorithm>

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define CYAN    "\033[36m"      /* Cyan */
#define ORANGE "\033[38;5;208m" /* Orange */

using namespace std;
using namespace combat_utils;

bool compareSpeed(Enemy *a, Enemy *b) {
    return a->getSpeed() > b->getSpeed();
}

Player::Player(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense,
                                                                                        speed, true) {
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
    if (CriticalHit && target->getHealth() > 0) {
        cout << GREEN << "  [ Critical Hit! ]" << RESET << endl;
    }
    else
    {
        cout << endl;
    }
    gainExperience(25);
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);
    cout << RED << "\t(-) " << name << " have taken " << damage << " damage" << RESET << endl;

    if (health <= maxHealth * 0.30 && warning == false) {
        cout << ORANGE << "\t(!!!)" << name << ", your health is low, be careful" << RESET << endl;
        warning = true;
    }

    if (health <= 0) {
        cout << CYAN << "\n\t(~) " << name << " have died" << RESET << endl;
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
        cout << "chance: " << chance << endl;
        fleed = chance > 99;
    }

    this->fleed = fleed;
}

void Player::emote() {
    cout << "Jokes on you" << endl;
}

void Player::levelUp() {
    level++;
    setHealth(getHealth() + 10);
    setAttack(getAttack() + 2);
    setDefense(getDefense() + 1);
    setSpeed(getSpeed() + 3);

    if (health >= maxHealth * 0.30) {
        warning = false;
    }

    cout << YELLOW << "\n\t~~~~~~~~~~~~~\n" << name << ", your level has gone up to "<< level <<"\n\t~~~~~~~~~~~~~\n"<< RESET << endl;
    
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 0;
    }
}

Character *Player::getTarget(vector<Enemy *> enemies) {
    cout << "Choose a target" << endl;
    int targetIndex = 0;
    for (int i = 0; i < enemies.size(); i++) {
        cout << i << ". " << enemies[i]->getName() << endl;
    }
    cin >> targetIndex;
    //TODO: Add input validation
    return enemies[targetIndex];
}

Action Player::takeAction(vector<Enemy *> enemies) {
    int option = 0;
    cout << "\n" << name << ", choose an action" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Flee" << endl;
    cin >> option;
    Character *target = nullptr;

    //Esta variable guarda
    //1. Que voy a hacer?
    //2. Con que velocidad/prioridad?
    Action myAction;
    //2.
    myAction.speed = this->getSpeed();
    myAction.subscriber = this;

    switch (option) {
        case 1:
            target = getTarget(enemies);
            myAction.target = target;
            //1.
            myAction.action = [this, target]() {
                doAttack(target);
            };
            break;
        case 2:
            myAction.action = [this, enemies]() {
                flee(enemies);
            };
            break;
        default:
            cout << "Invalid option" << endl;
            break;
    }

    return myAction;
}