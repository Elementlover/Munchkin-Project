#include "CardEffects.h"
#include <iostream>

// Could be re-implemented as a hashmap? lookup is less efficient than a switch statement or lookup table
void CardEffects::applyEffect(GamePlayer& player, const std::string& effectType, int value) {
	if (effectType == "levelChange") {
		player.setPlayerLevel(player.getPlayerLevel() + value);
		std::cout << player.getPlayerName() << " gained " << value << " levels!\n"; //TODO use ternary statement to check if value is positive or negative
	}
	else if (effectType == "powerChange") {
		player.setPlayerPower(player.getPlayerPower() + value);
		std::cout << player.getPlayerName() << " gained " << value << " power!\n";
	}
	else if (effectType == "curse") {
		std::cout << player.getPlayerName() << " is cursed! Lost " << value << " levels!\n";
	}
	else if (effectType == "equip") {
		// Implement equip logic here
		std::cout << player.getPlayerName() << " equipped an item!\n";
	}
	else if (effectType == "unequip") {
		// Implement unequip logic here
		std::cout << player.getPlayerName() << " unequipped an item!\n";
	}
	else if (effectType == "discard") {
		// Implement discard logic here
		std::cout << player.getPlayerName() << " discarded a card!\n";
	}
	else if (effectType == "draw") {
		// Implement draw logic here
		std::cout << player.getPlayerName() << " drew a card!\n";
	}
	else if (effectType == "steal") {
		// Implement steal logic here
		std::cout << player.getPlayerName() << " stole a card!\n";
	}
	else if (effectType == "trade") {
		// Implement trade logic here
		std::cout << player.getPlayerName() << " traded a card!\n";
	}
	else {
		std::cout << "Unknown effect type: " << effectType << "\n";
	}
	// Add more effect types as needed
}