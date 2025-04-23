#include "CardEffects.h"
#include "GamePlayer.h"
#include "GameInstance.h"
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
	else if (effectType == "TreasureDraw") {
		GameInstance* game = player.getGameInstance();
		if (game) {
			for (int i = 0; i < value; i++) {
				auto card = game->drawTreasureCard();
				if (card) {
					player.addCardtoHand(card);
					std::cout << player.getPlayerName() << " drew a treasure card: " << card->getName() << "\n";
				}
				else {
					std::cout << "No more treasure cards to draw!\n";
					break; // Exit loop if no more cards
				}
			}
		}
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
	else if (effectType == "curse") {
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