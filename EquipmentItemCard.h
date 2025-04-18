#pragma once
#include "Card.h"
#include <iostream>

class EquipmentItemCard :
    public ItemCard
{
private:
	int bonusPower;
	bool isTwoHanded;
	bool isEquipped;
	bool levelRequirement;

public:
	EquipmentItemCard(string cardName, string cardDescription, string type, int powerBonus, bool twoHanded = false, bool levelRequirement = false)
		: ItemCard(cardName, cardDescription, type), bonusPower(powerBonus), isTwoHanded(twoHanded), isEquipped(false), levelRequirement(false) {
	}

	void playCard(GamePlayer& player, GameInstance& game) override {
		int currentPower = player.getPlayerPower();
		int currentLevel = player.getPlayerLevel();

		// TODO check if player has enough levels to equip item
		

		// TODO IMPORTANT currentPower should be recalculated in the player class, not here?
		// TODO check tags for equip requirements

		if (!isEquipped) {
			player.setPlayerPower(player.getPlayerPower() + bonusPower); // This dynamically changes the player's power, probably best to recalculate the power in the player class instead
			isEquipped = true;
			cout << player.getPlayerName() << " equipped " << getName() << " and gained " << bonusPower << " power (now " << player.getPlayerPower() << ").\n";
		}
		else {
			cout << player.getPlayerName() << " already has " << getName() << " equipped.\n"; // TODO change behavior to unequip item
		}
	}
};

