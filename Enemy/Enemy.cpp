//
// Created by Victor Navarro on 13/02/24.
//
#include "Enemy.h"
#include <iostream>
#include <string>
#include "../colors.h"

using namespace std;

//TODO: Check the circular dependency
int getRolledAttack(int attack) {
    int lowerLimit = attack * .80;
    return (rand() % (attack - lowerLimit)) + lowerLimit;
}

Enemy::Enemy(char name[], int health, int attack, int defense, int speed, int XpReward)
    : Character(name, health, attack, defense, speed, XpReward, false) {
    maxHealth = health;
}

void Enemy::doAttack(Character* target) {
    int rolledAttack = getRolledAttack(getAttack());
    int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
    target->takeDamage(trueDamage);
}


void Enemy::takeDamage(int damage) {
    setHealth(getHealth() - damage);
    if (this->fleed != true) {
        if (getHealth() <= 0) {
            cout << MAGENTA << "\t(!) " << getName() << " has died" << RESET;

        }
        else {
            cout << GREEN << "\t(+) " << getName() << " has taken " << damage << " damage" << RESET;
        }
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

        if (((getMaxHealth() * 0.25 >= getHealth()) && rand() % 100 < 50)) {//ver si huye el pendejo este
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

