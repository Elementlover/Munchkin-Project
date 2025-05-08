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

int EquipmentItemCard::getPowerBonus() const {
    return bonusPower;
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