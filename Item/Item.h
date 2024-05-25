#ifndef RPG_ITEM_H
#define RPG_ITEM_H
#include<string>
#include "../Player/Player.h"
#include "../Character/Character.h"

class Player;

class Item {
protected:
	string itemName;
	int attackUp = 0;
	int healthUp = 0;
	int defenseUp = 0;
	int speedUp = 0;
	int expUp = 0;

	string status ;

public:
	void Use(Player *owner);
	Item(string,int,int,int,int,int);

	string getName();
	string getStatus();
	void checkResults(Player* owner);
	int getAttackUp();
	int getHealthUp();
	int getDefenseUp();
	int getSpeedUp();
	int getExpUp();

};


#endif //RPG_ITEM_H