
#include <string>
#include <iostream>
#include <sstream>
#include "Item.h"
#include "../colors.h"

using namespace std;

Item::Item(string _itemName, int _attackUP ,int _healthUp, int _defenseUP, int _speedUp, int _expUp ) {
	itemName = _itemName;
	attackUp = _attackUP;
	healthUp = _healthUp;
	defenseUp = _defenseUP;
	speedUp = _speedUp;
	expUp = _expUp;
}
void Item::Use(Player *owner) {
	owner->setAttack(owner->getAttack() + attackUp);
	if ((owner->getHealth() + healthUp) > owner->getMaxHealth()) {
		owner->setHealth(owner->getMaxHealth());
	}
	else
	{
		owner->setHealth(owner->getHealth() + healthUp);
	}
	owner->setDefense(owner->getDefense() + defenseUp);
	owner->setSpeed(owner->getSpeed() + speedUp);
	owner->gainExperience(expUp);
	

	checkResults(owner);

	cout << GOLDEN_YELLOW << "\t(*) " << getStatus() << RESET << endl;

}
void Item::checkResults(Player* owner) {
	std::ostringstream oss;
	oss <<owner->getName()<< " uses "<< getName() << " |";

	if (attackUp != 0) {
		oss << "Att(" << getAttackUp() << ")|";
	}
	if (healthUp != 0) {
		oss << "Hp(" << getHealthUp() << ")|";
	}
	if (defenseUp != 0) {
		oss << "Def(" << getDefenseUp() << ")|";
	}
	if (speedUp != 0) {
		oss << "Speed(" << getSpeedUp() << ")|";
	}
	if (expUp != 0) {
		oss << "Exp(" << getExpUp() << ")|";
	}

	status.append(oss.str());
}
string Item::getName() {
	return itemName;
}

int Item::getAttackUp() {
	return attackUp;
}

int Item::getHealthUp() {
	return healthUp;
}

int Item::getDefenseUp() {
	return defenseUp;
}

int Item::getSpeedUp() {
	return speedUp;
}

int Item::getExpUp() {
	return expUp;
}

string Item::getStatus() {
	return status;
}