#include "Card.h"
#include <string>
#include <iostream>
#include "GamePlayer.h" // included for now but should be move into a .cpp file to avoid circular dependencies
#include "GameInstance.h"
#include "CombatManager.h"

// Base Card
Card::Card(string cardName, string cardDescription, string cardType, vector<string> cardTags)
	: name(cardName), description(cardDescription), type(cardType), tags(cardTags) {}

//Destructor
Card::~Card() {
	// Cleanup code if needed
}

string Card::getName() const { return name; }
string Card::getType() const { return type; }
string Card::getDescription() const { return description; }
vector<string> Card::getTags() const { return tags; }

void Card::setName(string cardName) { name = cardName; }
void Card::setDescription(string cardDescription) { description = cardDescription; }

// Card Types
// Derived classes for specific card types


ItemCard::ItemCard(string cardName, string cardDescription, string type)
	: Card(cardName, cardDescription, type) {
	}

void ItemCard::playCard(GamePlayer& player, GameInstance& game) {
	// Implement item-specific logic
}

MonsterCard::MonsterCard(string cardName, string cardDescription, string type, int level, unordered_map<string, int> WinEffects, unordered_map<string, int> LoseEffects,
	std::string winDesc, std::string loseDesc)
	: Card(cardName, cardDescription, type), level(level), WinEffects(WinEffects), LoseEffects(LoseEffects),
	winDescription(winDesc),
	loseDescription(loseDesc) {
}
void MonsterCard::playCard(GamePlayer& player, GameInstance& game) {
	// Implement monster-specific logic
	CombatManager::resolveCombat(player, *this, game);
}


CurseCard::CurseCard(string cardName, string cardDescription, string type, int levelChange, int powerChange)
	: Card(cardName, cardDescription, type), levelChange(levelChange), powerChange(powerChange)  {
}
void CurseCard::playCard(GamePlayer& player, GameInstance& game) {
	// Implement curse-specific logic
	int currentLevel = player.getPlayerLevel();
	int currentPower = player.getPlayerPower();
	player.setPlayerLevel(currentLevel + levelChange);
	player.setPlayerPower(currentPower + powerChange);
	cout << player.getPlayerName() << " is cursed! You lost " << levelChange << " levels and " << powerChange << " power.\n";
}
