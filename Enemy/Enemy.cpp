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
    if (target->getHealth() > 0) {
        int rolledAttack = getRolledAttack(getAttack());
        int trueDamage = target->getDefense() > rolledAttack ? 0 : rolledAttack - target->getDefense();
        target->takeDamage(trueDamage);
    }
    else {
        cout << MAGENTA <<"\t" << getName() << " le baila a " << target->getName() << RESET << endl;
    }
    
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

void Enemy::levelUp() {
    level++;

    if ((getHealth() + 5) > getMaxHealth()) {
        setMaxHealth(getHealth() + 5);
    }
    setHealth(getHealth() + 5);

    setAttack(getAttack() + 2);
    setDefense(getDefense() + 1);
    setSpeed(getSpeed() + 1);

    cout << ORANGE<< "\t" << getName() << " (Level Up to: " << getLevel() << ") " << RESET << endl;
    
}
void Enemy::gainExperience(int exp,int enemies_size) {

    exp /= enemies_size;//regula para que no suban a la par con el jugador

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

