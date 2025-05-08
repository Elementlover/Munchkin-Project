#include "EquipmentItemCard.h"
#include "GamePlayer.h"
#include "GameInstance.h"
#include <iostream>

EquipmentItemCard::EquipmentItemCard(std::string cardName, std::string cardDescription, std::string type,
    int powerBonus, bool twoHanded, EquipmentSlot slot, bool levelRequirement)
    : ItemCard(cardName, cardDescription, type),
    bonusPower(powerBonus),
    isTwoHanded(twoHanded),
    isEquipped(false),
    slotType(slot),
    levelRequirement(levelRequirement) {
}

EquipmentSlot EquipmentItemCard::getSlotType() const {
    return slotType;
}

void EquipmentItemCard::playCard(GamePlayer& player, GameInstance& game) {
    int currentPower = player.getPlayerPower();
    int currentLevel = player.getPlayerLevel();

    // TODO: Level requirements, tag checks, proper logic
    if (!isEquipped) {
        player.setPlayerPower(currentPower + bonusPower);
        isEquipped = true;
        std::cout << player.getPlayerName() << " equipped " << getName()
            << " and gained " << bonusPower << " power (now "
            << player.getPlayerPower() << ").\n";
    }
    else {
        std::cout << player.getPlayerName() << " already has " << getName()
            << " equipped.\n";
    }
}