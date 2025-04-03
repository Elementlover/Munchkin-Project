#pragma once
#include "characterClass.h"

using namespace std;

class GamePlayer
{
private:
	int playerLevel;
	int playerPower;
	characterClass activeClass;

public:
	GamePlayer() : playerLevel(0) {}
};

