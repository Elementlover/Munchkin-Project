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
	GamePlayer(int level = 1, int power = 1, characterClass cls = characterClass())
		: playerLevel(level), playerPower(power), activeClass(cls) {}

    // Getters
    int getPlayerLevel() const { return playerLevel; }
    int getPlayerPower() const { return playerPower; }
    characterClass getActiveClass() const { return activeClass; }

    // Setters
    void setPlayerLevel(int level) { playerLevel = level; }
    void setPlayerPower(int power) { playerPower = power; }
    void setActiveClass(characterClass cls) { activeClass = cls; }
};

