//
// Created by Victor Navarro on 13/02/24.
//
#include "Character.h"
#include <string>
#include <sstream>

Character::Character(char _name[], int _health, int _attack, int _defense, int _speed,int _XpReward, bool _isPlayer) {
    strcpy(name, _name);
    health = _health;
    maxHealth = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
    fleed = false;
    kills = 0;
    XpReward = _XpReward;
}

void Character::setName(char _name[]) {
    strcpy(name, _name);
}

char* Character::getName() {
    return name;
}

void Character::setHealth(int _health) {
    health = _health;
}

int Character::getHealth() {
    return health;
}

void Character::setAttack(int _attack) {
    attack = _attack;
}

int Character::getAttack() {
    return attack;
}

void Character::setDefense(int _defense) {
    defense = _defense;
}

int Character::getDefense() {
    return defense;
}

void Character::setSpeed(int _speed) {
    speed = _speed;
}

int Character::getSpeed() {
    return speed;
}

string Character::toString() {

    std::string nameStr(name);
    std::stringstream ss;
    ss << "Name: " << nameStr << "\nHealth: " << getHealth() << "\nAttack: " << getAttack() << "\nDefense: " << getDefense() << "\nSpeed: " << getSpeed();
    return ss.str();
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::hasFleed() {
    return fleed;
}

int Character::getMaxHealth() {
    return maxHealth;
}

string Character::getLifeBar() {
    string lifebar = "[";
    int slideLength = getHealth() * 30 / getMaxHealth();
    for (size_t i = 1; i <= 30; i++)
    {
        if (i <= slideLength)
        {
            lifebar.append("=");
        }
        else
        {
            lifebar.append(" ");
        }

    }
    lifebar.append("] ");
    lifebar.append(to_string(getHealth()));
    lifebar.append("|");
    lifebar.append(to_string(getMaxHealth()));

    return lifebar;
}
int Character::getKills() {
    return kills;
}

int Character::getXpReward(){
    return XpReward;
}

void Character::setXpReward(int _XpReward) {
    XpReward = _XpReward;
}