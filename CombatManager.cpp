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
	// 
	// Could use structured bindings to unpack the effects but using older version of c++
	// Combat resolution logic
	if (playerPower >= monsterPower) { // Victory
		cout << playerName << " defeated the monster!\n";
		// Apply effects for winning

		for (const auto& [effectName, value] : monster.getWinEffects()) {
			CardEffects::applyEffect(player, effectName, value);
		}
	} else {
		cout << playerName << " was defeated by the monster!\n";

		for (const auto& [effectName, value] : monster.getLoseEffects()) {
			CardEffects::applyEffect(player, effectName, value);
		}
	}
}
