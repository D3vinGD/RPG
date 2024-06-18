
#include "../Player/Player.h"
#include "chrono"
#include <iostream>
#include "ctime"

using namespace std;

class Game {
private:
	int IDgame;
	string date;
	string time;
	struct PlayerData;
public:
	void startGame();
	void SaveGame();
	void LoadGame();

};
