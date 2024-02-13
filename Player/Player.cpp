//
// Created by Victor Navarro on 13/02/24.
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string name, int health, int attack, int defense, int speed) : Character(name, health, attack, defense, speed) {
    experience = 0;
    level = 1;
}

void Player::doAttack(Character *target) {
    int trueDamage = getAttack() - target->getDefense();
    target->takeDamage(trueDamage);
}

void Player::takeDamage(int damage) {
    setHealth(health - damage);

    if(health <= 0) {
        cout<<"You have died"<<endl;
    }
    else {
        cout<<"You have taken " << damage << " damage" << endl;
    }
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