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
	ItemCard(string cardName, string cardDescription, string type);
	void playCard(GamePlayer& player, GameInstance& game) override;
};

class MonsterCard : public Card
{
private:
	int level;
	unordered_map<string, int> WinEffects; // Tags for win condition
	unordered_map<string, int> LoseEffects; // Tags for lose condition

public:
	MonsterCard(string cardName, string cardDescription, string type, int level,
		unordered_map<string, int> WinEffects,
		unordered_map<string, int> LoseEffects);

	void playCard(GamePlayer& player, GameInstance& game) override;

	// Getters
	int getLevel() const { return level; }
    unordered_map<string, int> const& getWinEffects() const { return WinEffects; }  
    unordered_map<string, int> const& getLoseEffects() const { return LoseEffects; }
};

class CurseCard : public Card
{
private:
	int powerChange;
	int levelChange;
	
public:
	CurseCard(string cardName, string cardDescription, string type, int levelChange = 0, int powerChange = 0);
	void playCard(GamePlayer& player, GameInstance& game) override;
};