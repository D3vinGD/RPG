//
// Created by Victor Navarro on 13/02/24.
//

#include "Player.h"
#include <iostream>

using namespace std;

void Player::doAttack(Character *target) {
    target->setHealth(target->getHealth() - (attack - target->getDefense()));
}

void Player::flee() {
    //TODO: Implement flee
    cout<<"Work in progress"<<endl;
}

void Player::emote() {
    cout<<"Jokes on you" << endl;
}

void Player::levelUp() {
    level++;
    setHealth(getHealth() + 10);
    setAttack(getAttack() + 5);
    setDefense(getDefense() + 5);
    setSpeed(getSpeed() + 5);
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 0;
    }
}