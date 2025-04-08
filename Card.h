#pragma once
#include <string>
#include "GamePlayer.h"
#include "GameInstance.h"
#include <json.hpp>

using namespace std;

class Card
{
private:
	string name;
	string type; // "Door" or "Treasure"
	string description;
	vector<string> tags; // Tags for card categorization

public:
	Card(string cardName = "Unknown", string cardDescription = "No description", string cardType = "No Type", vector<string> cardTags)
		: name(cardName), description(cardDescription), type(cardType), tags(cardTags) {
	}

	// Destructor for cleanup of derived classes
	virtual ~Card() {
		// Cleanup code if needed
	}

	// Getters
	string getName() const { return name; }
	string getType() const { return type; }
	string getDescription() const { return description; }
	vector<string> getTags() const { return tags; }

	// Setters
	void setName(string cardName) { name = cardName; }
	void setDescription(string cardDescription) { description = cardDescription; }

	// Card Actions
	virtual void playCard(GamePlayer& player, GameInstance& game) = 0;
};
// Card Types
// Derived classes for specific card types
class ItemCard : public Card
{

public:
	ItemCard(string cardName, string cardDescription)
		: Card(cardName, cardDescription) {
	}
	void playCard(GamePlayer& player, GameInstance& game) override {
		// Implement item-specific logic
	}
};

class MonsterCard : public Card
{
public:
	MonsterCard(string cardName, string cardDescription)
		: Card(cardName, cardDescription) {
	}
	void playCard(GamePlayer& player, GameInstance& game) override {
		// Implement monster-specific logic
	}
};

class CurseCard : public Card
{
public:
	CurseCard(string cardName, string cardDescription)
		: Card(cardName, cardDescription) {
	}
	void playCard(GamePlayer& player, GameInstance& game) override {
		// Implement curse-specific logic
	}
};