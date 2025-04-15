#pragma once
#include <string>
#include <json.hpp>
#include <iostream>
#include "GamePlayer.h" // included for now but should be move into a .cpp file to avoid circular dependencies
//#include "GameInstance.h"

class GamePlayer; // Forward declaration
class GameInstance;

using namespace std;
using json = nlohmann::json;

class Card
{
private:
	string name;
	string type; // "Door" or "Treasure"
	string description;
	vector<string> tags; // Tags for card categorization

public:
	Card(string cardName = "Unknown", string cardDescription = "No description", string cardType = "No Type", vector<string> cardTags = {});

	// Destructor for cleanup of derived classes
	virtual ~Card();

	// Getters
	string getName() const;
	string getType() const;
	string getDescription() const;
	vector<string> getTags() const;

	// Setters
	void setName(string cardName);
	void setDescription(string cardDescription);

	// Card Actions
	virtual void playCard(GamePlayer& player, GameInstance& game) = 0;
};

// -------- Derived classes for specific card types --------- //

class ItemCard : public Card
{

public:
	ItemCard(string cardName, string cardDescription);
	void playCard(GamePlayer& player, GameInstance& game) override;
};

class MonsterCard : public Card
{
private:
	int level;
	string monsterType; // e.g., "Undead", "Beast", etc.

public:
	MonsterCard(string cardName, string cardDescription, int level, string monsterType);
	void playCard(GamePlayer& player, GameInstance& game) override;
};

class CurseCard : public Card
{
private:
	int powerChange;
	int levelChange;
	
public:
	CurseCard(string cardName, string cardDescription, int levelChange = 0, int powerChange = 0);
	void playCard(GamePlayer& player, GameInstance& game) override;
};