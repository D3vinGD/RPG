//
// Created by Victor Navarro on 13/02/24.
//

#ifndef RPG_ENEMY_H
#define RPG_ENEMY_H
#include "../Character/Character.h"
#include "../Player/Player.h"

class Player;

class Enemy: public Character {
public:
    Enemy(string, int, int, int, int);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* getTarget(vector<Player*> teamMembers);
    //TODO: Crear el metodo takeAction en la clase Enemy
    // Cuando el enemigo tenga menos del 15% de su vida máxima, habrá un 5% de probabilidad de que intente huir
    // rand() % 100 < 5 ------> intentas huir flee()

    //TODO: Mover metodo flee a character
};


#endif //RPG_ENEMY_H
