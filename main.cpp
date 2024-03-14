#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"
#include <queue>

using namespace std;

int main() {
    Player *player = new Player("Devin", 100, 25, 20, 15);
    Enemy *enemy = new Enemy("Ingenieria", 100, 20, 5, 35);
    Enemy *enemy2 = new Enemy("La vida", 100, 35, 5, 10);

    vector<Character*> participants;
    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat* combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete enemy2;
    delete combat;

    return 0;
}
