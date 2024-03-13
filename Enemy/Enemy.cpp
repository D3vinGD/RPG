//
// Created by Victor Navarro on 13/02/24.
//
#include "Enemy.h"
#include <iostream>

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define CYAN    "\033[36m"      /* Cyan */


using namespace std;

//TODO: Check the circular dependency
int getRolledAttack(int attack) {
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

Enemy::Enemy(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed, false) {
    maxHealth = health;
}

void Enemy::doAttack(Character* target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}


void Enemy::takeDamage(int damage) {
    setHealth(getHealth() - damage);
    if (getHealth() <= 0) {
        cout << CYAN << "\t(!) " << getName() << " has died\n" << RESET << endl;
    }
    else {
        cout << GREEN << "\t(+) " << getName() << " has taken " << damage << " damage" << RESET;
    }
}

Character* Enemy::getTarget(vector<Player*> teamMembers) {
    // Obtiene el miembro del equipo con menos vida
    int targetIndex = 0;
    int lowestHealth = INT_MAX;
    for (int i = 0; i < teamMembers.size(); i++) {
        if (teamMembers[i]->getHealth() < lowestHealth) {
            lowestHealth = teamMembers[i]->getHealth();
            targetIndex = i;
        }
    }

    return teamMembers[targetIndex];
}

int Enemy::getMaxHealth() {
    return maxHealth;
}

Action Enemy::takeAction(vector<Player*> player) {
    Action myAction;
    myAction.speed = getSpeed();
    myAction.subscriber = this;
    Character* target = getTarget(player);
    myAction.target = target;
    if ((getMaxHealth() * 0.50 >= getHealth()) && rand() % 100 < 50){//ver si huye el pendejo este
        myAction.action = [this, target]() {
            this->fleed = true;
        };
    }
    else
    {
        myAction.action = [this, target]() {
        doAttack(target);
        };
    }
    

    return myAction;
}

