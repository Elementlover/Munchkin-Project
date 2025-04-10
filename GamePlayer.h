#pragma once
#include "characterClass.h"

using namespace std;

class GamePlayer
{
private:
	int playerLevel;
	int playerPower;
	characterClass activeClass;
    string playerName;
    vector<Card> heldCards;

public:
	GamePlayer(string name = "Default Name", int level = 1, int power = 1, characterClass cls = characterClass())
		: playerName(name), playerLevel(level), playerPower(power), activeClass(cls) {}

    // Getters
    int getPlayerLevel() const { return playerLevel; }
    int getPlayerPower() const { return playerPower; }
    characterClass getActiveClass() const { return activeClass; }
    string getPlayerName() const { return playerName; }

    // Setters
    void setPlayerLevel(int level) { playerLevel = level; }
    void setPlayerPower(int power) { playerPower = power; }
    void setPlayerName(string name) { playerName = name; }
    void setActiveClass(characterClass cls) { activeClass = cls; }

	void addOneLevel() { playerLevel++; }


};

