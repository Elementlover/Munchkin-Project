#include "CombatManager.h"
#include <iostream>
#include <random>

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

		const auto& loseEffects = monster.getLoseEffects();

		// Check for Escape Roll
		auto escapeIt = loseEffects.find("Escape Roll");
		if (escapeIt != loseEffects.end()) {
			int requiredRoll = escapeIt->second;

			// Simulate dice roll (1–6)
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dist(1, 6);
			int roll = dist(gen);

			std::cout << playerName << " attempts to escape! Needs " << requiredRoll << "+... Rolled a " << roll << ".\n";

			if (roll >= requiredRoll) {
				std::cout << playerName << " escapes successfully with a " << roll << "!\n";
				return; // Avoid applying lose effects
			}
			else {
				std::cout << playerName << " fails to escape with a " << roll << "!\n";
			}
		}

		// Apply all other lose effects
		for (const auto& [effectName, value] : loseEffects) {
			if (effectName != "Escape Roll") { // Skip the escape check effect
				CardEffects::applyEffect(player, effectName, value);
			}
		}
	}
}
