#include "CombatManager.h"
#include <iostream>
#include <random>
#include <thread>  // For sleep functionality
#include <chrono>  // For time duration

void CombatManager::resolveCombat(GamePlayer& player, MonsterCard& monster, GameInstance& game)
{
	string playerName = player.getPlayerName();

	// Announce the start of the fight with a slight delay
	std::cout << playerName << " is fighting " << monster.getName() << "!\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));  // 1-second delay for dramatic effect
	std::cout << ">> " << monster.getDescription() << "\n\n";  // description of the monster
	std::this_thread::sleep_for(std::chrono::seconds(1));  // Another small delay

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

	// Announce the rolls with a slight pause
	std::cout << playerName << " rolls a d20...\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));  // 2-second delay for suspense
	std::cout << playerName << " rolled a " << playerRoll << "!\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "-> Player Power: " << basePlayerPower << " + d20 (" << playerRoll << ") = " << totalPlayerPower << "\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << monster.getName() << " rolls a d20...\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << monster.getName() << " rolled a " << monsterRoll << "!\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "-> Monster Power: " << baseMonsterPower << " + d20 (" << monsterRoll << ") = " << totalMonsterPower << "\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));  // 2-second delay for suspense

	if (totalPlayerPower >= totalMonsterPower) { // Victory
		cout << playerName << " defeated the monster!\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));  // Pause for dramatic effect

		if (!monster.getWinDescription().empty()) {
			std::cout << ">> " << monster.getWinDescription() << "\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));  // Pause after win description
		}
		// Apply effects for winning

		for (const auto& [effectName, value] : monster.getWinEffects()) {
			CardEffects::applyEffect(player, effectName, value);
		}
	} else { // Defeat
		cout << playerName << " was defeated by the monster!\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));  // Pause for dramatic effect

		if (!monster.getLoseDescription().empty()) {
			std::cout << ">> " << monster.getLoseDescription() << "\n";
			std::this_thread::sleep_for(std::chrono::seconds(3));  // Pause after lose description
			std::cout << endl;
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

			std::cout << playerName << " attempts to escape! Needs a " << requiredRoll << "!!!" << endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));  // Dramatic pause before escape roll result
			std::cout << playerName << " rolled a " << roll << ".\n";

			if (roll >= requiredRoll) {
				std::cout << playerName << " escapes successfully with a " << roll << "!\n";
				return; // Avoid applying lose effects
			}
			else {
				std::cout << playerName << " fails to escape with a " << roll << "!\n";
				std::this_thread::sleep_for(std::chrono::seconds(2));  // Pause after escape failure
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
