#include <iostream>
#include "Enemy/Enemy.h"
#include "Player/Player.h"
#include "Combat/Combat.h"
#include <queue>

using namespace std;

int main() { 

    //{JUGADORES} Nombre, vida , ataque, defensa, velocidad
    Player *player = new Player("Devin", 100, 30, 18, 15);

    //{ENEMIGOS} Nombre, vida , ataque, defensa, velocidad, xp de recompensa

    Enemy *enemy = new Enemy("El Padrastro", 35, 32, 5, 10, 55);
    Enemy *enemy2 = new Enemy("Pug", 1, 19, 0, 14, 31);
    Enemy* enemy3 = new Enemy("YucatecoTactico", 50, 20, 10, 12, 80);
    Enemy* enemy4 = new Enemy("Peruano", 100, 16, 1, 9, 41);


    vector<Character*> participants;
    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);
    participants.push_back(enemy3);
    participants.push_back(enemy4);

    Combat* combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete enemy2;
    delete enemy3;
    delete enemy4;
    delete combat;
    return 0;
}
