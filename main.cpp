#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"

int main() {

    Player *player = new Player("Victor", 100, 10, 5, 5);
    Enemy *enemy = new Enemy("Recursos Humanos", 50, 5, 2, 3);

    player->doAttack(enemy);
    enemy->doAttack(player);

    cout<< player->toString()<< endl;
    cout<< enemy->toString()<< endl;
    return 0;
}
