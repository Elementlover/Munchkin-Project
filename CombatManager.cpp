#include "CombatManager.h"
#include <iostream>

void CombatManager::resolveCombat(GamePlayer& player, MonsterCard& monster, GameInstance& game)
{
	string playerName = player.getPlayerName();

	cout << playerName << " is fighting " << monster.getName() << "!\n";

	int playerPower = player.getPlayerPower();
	int monsterPower = monster.getLevel();

	cout << "-> Player Power: " << playerPower << " vs Monster Power: " << monsterPower << endl;

	// TODO FIX CARD EFFECTS
	// Combat resolution logic
	if (playerPower >= monsterPower) { // Victory
		cout << playerName << " defeated the monster!\n";
		// Apply effects for winning

		for (const auto& tag : monster.getWinTags()) {
			//CardEffects::applyEffect(player, tag); 
		}
	} else {
		cout << playerName << " was defeated by the monster!\n";

		for (const auto& tag : monster.getLoseTags()) {
			//CardEffects::applyEffect(player, tag);
		}
	}
}
