#pragma once

#include "Card.h"
#include "EquipmentSlot.h"

class GamePlayer;       // Forward declaration
class GameInstance;     // Forward declaration

class EquipmentItemCard : public ItemCard {
private:
    int bonusPower;
    bool isTwoHanded;
    bool isEquipped;
    bool levelRequirement;
    EquipmentSlot slotType;
	Handedness handedness;

public:
    EquipmentItemCard(std::string cardName, std::string cardDescription, std::string type,
        int powerBonus, Handedness handedness = Handedness::OneHanded,
        EquipmentSlot slot = EquipmentSlot::LeftHand,
        bool levelRequirement = false);

    EquipmentSlot getSlotType() const;
    int getPowerBonus() const;
	Handedness getHandedness() const;
    void playCard(GamePlayer& player, GameInstance& game) override;
};