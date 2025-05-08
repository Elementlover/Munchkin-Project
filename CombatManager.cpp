#include "CombatManager.h"
#include <iostream>
#include <random>

void CombatManager::resolveCombat(GamePlayer& player, MonsterCard& monster, GameInstance& game)
{
	string playerName = player.getPlayerName();

	cout << playerName << " is fighting " << monster.getName() << "!\n";
	cout << ">> " << monster.getDescription() << "\n\n"; // description of the monster

	int basePlayerPower = player.getPlayerPower();
	int baseMonsterPower = monster.getLevel();


	// Roll d20 for both player and monster
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> d20(1, 20);

	int playerRoll = d20(gen);
	int monsterRoll = d20(gen);

	int totalPlayerPower = basePlayerPower + playerRoll;
	int totalMonsterPower = baseMonsterPower + monsterRoll;

	std::cout << "-> Player Power: " << basePlayerPower << " + d20 (" << playerRoll << ") = " << totalPlayerPower << "\n";
	std::cout << "-> Monster Power: " << baseMonsterPower << " + d20 (" << monsterRoll << ") = " << totalMonsterPower << "\n";

	if (totalPlayerPower >= totalMonsterPower) { // Victory
		cout << playerName << " defeated the monster!\n";
		if (!monster.getWinDescription().empty()) {
			std::cout << ">> " << monster.getWinDescription() << "\n";
		}
		// Apply effects for winning

		for (const auto& [effectName, value] : monster.getWinEffects()) {
			CardEffects::applyEffect(player, effectName, value);
		}
	} else { // Defeat
		cout << playerName << " was defeated by the monster!\n";
		if (!monster.getLoseDescription().empty()) {
			std::cout << ">> " << monster.getLoseDescription() << "\n";
		}

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
