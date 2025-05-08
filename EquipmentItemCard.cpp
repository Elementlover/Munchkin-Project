#include "EquipmentItemCard.h"
#include "GamePlayer.h"
#include "GameInstance.h"
#include "EquipmentSlot.h"
#include <iostream>

EquipmentItemCard::EquipmentItemCard(std::string cardName, std::string cardDescription, std::string type,
    int powerBonus, Handedness handedness, EquipmentSlot slot, bool levelRequirement)
    : ItemCard(cardName, cardDescription, type),
    bonusPower(powerBonus),
    isEquipped(false),
    levelRequirement(levelRequirement),
    slotType(slot),
    handedness(handedness) {}

EquipmentSlot EquipmentItemCard::getSlotType() const {
    return slotType;
}

int EquipmentItemCard::getPowerBonus() const {
    return bonusPower;
}

Handedness EquipmentItemCard::getHandedness() const {
    return handedness;
}

void EquipmentItemCard::playCard(GamePlayer& player, GameInstance& game) {
    // Check if already equipped via GamePlayer (not this flag alone)
    EquipmentSlot slot = getSlotType();

    auto equipped = player.getEquippedItems();
    if (equipped.find(slot) != equipped.end() && equipped.at(slot)->getName() == this->getName()) {
        std::cout << player.getPlayerName() << " already has " << getName() << " equipped.\n";
        return;
    }

    player.equipItem(std::make_shared<EquipmentItemCard>(*this));
    isEquipped = true;

    std::cout << player.getPlayerName() << " equipped " << getName()
        << " for +" << getPowerBonus() << " power.\n";
}