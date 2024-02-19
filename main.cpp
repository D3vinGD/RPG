#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"

int main() {

    Player *player = new Player("Victor", 100, 5, 3, 5);
    Enemy *enemy = new Enemy("Recursos Humanos", 100, 5, 3, 5);

    vector<Character*> participants;
    participants.push_back(player);
    participants.push_back(enemy);

    Combat* combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete combat;
    return 0;
}
