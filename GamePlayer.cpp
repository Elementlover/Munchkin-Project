#include "GamePlayer.h"
#include "GameInstance.h"
#include "Card.h" // Needed for shared_ptr<Card> use
#include "EquipmentItemCard.h"

// Forward declare slotToString
std::string slotToString(EquipmentSlot slot);

GamePlayer::GamePlayer(std::string name, int level, int power, characterClass cls)  
   : playerName(name), playerLevel(level), playerPower(power), activeClass(cls), gameInstance(nullptr) {  
}

GamePlayer::~GamePlayer() {
	// Destructor logic if needed
}

GameInstance* GamePlayer::getGameInstance() const {
	return gameInstance;
}

int GamePlayer::getPlayerLevel() const {
    return playerLevel;
}

int GamePlayer::getPlayerPower() const {
    return playerPower;
}

characterClass GamePlayer::getActiveClass() const {
    return activeClass;
}

std::string GamePlayer::getPlayerName() const {
    return playerName;
}

std::vector<std::shared_ptr<Card>> GamePlayer::getHeldCards() const {
	return heldCards;
}

const std::unordered_map<EquipmentSlot, std::shared_ptr<EquipmentItemCard>>& GamePlayer::getEquippedItems() const {
    return equippedItems;
}

void GamePlayer::setGameInstance(GameInstance* game) {
	gameInstance = game;
}

void GamePlayer::setPlayerLevel(int level) {
    playerLevel = level;
}

void GamePlayer::setPlayerPower(int power) {
    playerPower = power;
}

void GamePlayer::setPlayerName(std::string name) {
    playerName = name;
}

void GamePlayer::setActiveClass(characterClass cls) {
    activeClass = cls;
}

void GamePlayer::addOneLevel() {
    playerLevel++;
}

void GamePlayer::addCardtoHand(std::shared_ptr<Card> card) {
    heldCards.push_back(card);
}

bool GamePlayer::removeCard(const std::string& cardName) {
    for (auto it = heldCards.begin(); it != heldCards.end(); ++it) {
        if ((*it)->getName() == cardName) {
            heldCards.erase(it);
            return true;
        }
    }
    return false;
}

void GamePlayer::listHeldCards() const
{
	if (heldCards.empty()) {
		cout << "No cards in hand." << endl;
		return;
	}

	cout << "Held Cards:" << endl;
    for (size_t i = 0; i < heldCards.size(); ++i) {
        //cout << endl; // syntax
        cout << i + 1 << ": " << heldCards[i]->getName() << " - " << heldCards[i]->getDescription() << endl;
	}
	cout << endl;
}

// -------- Card Actions -------- //

std::vector<std::string> GamePlayer::getAvailableActions() const {
    return {
        "Draw Door Card",
        "View Hand",
        "View Equipped Items",
        "Skip Turn"
		// TODO check for other actions based on held cards
    };
}

void GamePlayer::equipItem(std::shared_ptr<EquipmentItemCard> equipmentCard) {

    // Prevent equipping the same card again
    for (const auto& [slotKey, equippedCard] : equippedItems) {
        if (equippedCard == equipmentCard) {
            std::cout << "This item is already equipped.\n";
            return;
        }
    }

    EquipmentSlot slot = equipmentCard->getSlotType();
    Handedness handType = equipmentCard->getHandedness();

    if (slot == EquipmentSlot::LeftHand || slot == EquipmentSlot::RightHand || slot == EquipmentSlot::TwoHanded) {
        if (handType == Handedness::TwoHanded) {
            // Unequip both hands if anything is in them
            for (EquipmentSlot hand : {EquipmentSlot::LeftHand, EquipmentSlot::RightHand}) {
                auto it = equippedItems.find(hand);
                if (it != equippedItems.end()) {
                    std::cout << "Unequipping " << slotToString(hand) << ": " << it->second->getName() << "\n";
                    heldCards.push_back(it->second);
                    equippedItems.erase(it);
                }
            }

            // Also unequip any other two-handed item
            auto it = equippedItems.find(EquipmentSlot::TwoHanded);
            if (it != equippedItems.end()) {
                std::cout << "Swapping out two-handed item: " << it->second->getName() << "\n";
                heldCards.push_back(it->second);
            }

            equippedItems[EquipmentSlot::TwoHanded] = equipmentCard;
            std::cout << "Equipped two-handed item: " << equipmentCard->getName() << "\n";
        }
        else {
            // Unequip two-handed item if present
            auto twoHandIt = equippedItems.find(EquipmentSlot::TwoHanded);
            if (twoHandIt != equippedItems.end()) {
                std::cout << "Unequipping two-handed item: " << twoHandIt->second->getName() << "\n";
                heldCards.push_back(twoHandIt->second);
                equippedItems.erase(twoHandIt);
            }

            // Determine which hand is free
            if (equippedItems.find(EquipmentSlot::LeftHand) == equippedItems.end()) {
                equippedItems[EquipmentSlot::LeftHand] = equipmentCard;
                std::cout << "Equipped in Left Hand: " << equipmentCard->getName() << "\n";
            }
            else if (equippedItems.find(EquipmentSlot::RightHand) == equippedItems.end()) {
                equippedItems[EquipmentSlot::RightHand] = equipmentCard;
                std::cout << "Equipped in Right Hand: " << equipmentCard->getName() << "\n";
            }
            else {
                std::cout << "Both hands are full. Cannot equip: " << equipmentCard->getName() << "\n";
                heldCards.push_back(equipmentCard); // Return to hand
            }
        }
    }
    else {
        // For non-hand slots: Body, Head, Feet, etc.
        auto it = equippedItems.find(slot);
        if (it != equippedItems.end()) {
            std::cout << "Unequipping " << slotToString(slot) << ": " << it->second->getName() << "\n";
            heldCards.push_back(it->second);
            equippedItems.erase(it);
        }

        equippedItems[slot] = equipmentCard;
        std::cout << "Equipped " << slotToString(slot) << ": " << equipmentCard->getName() << "\n";
    }


    std::cout << "Equipped: " << equipmentCard->getName() << "\n";
	recalculatePower(); // Recalculate power after equipping
    std::cout << playerName << "'s now has " << getPlayerPower() << " power!" << "\n";
}

void GamePlayer::listEquippedItems() const {
    if (equippedItems.empty()) {
        std::cout << "No equipment currently equipped.\n";
        return;
    }

    std::cout << "Equipped Items:\n";
    for (const auto& [slot, card] : equippedItems) {
        std::cout << slotToString(slot) << ": " << card->getName() << " - " << card->getDescription() << "\n";
    }
}

std::string slotToString(EquipmentSlot slot) {
    switch (slot) {
    case EquipmentSlot::Head: return "Head";
    case EquipmentSlot::Body: return "Body";
    case EquipmentSlot::Feet: return "Feet";
    case EquipmentSlot::LeftHand: return "Left Hand";
    case EquipmentSlot::RightHand: return "Right Hand";
	case EquipmentSlot::TwoHanded: return "Two Handed";
    case EquipmentSlot::Hireling: return "Hireling";
    default: return "Unknown";
    }
}

void GamePlayer::recalculatePower() {
    int totalPower = 0;

	totalPower += playerLevel; // Base power from level

    // Sum power bonuses from all equipped items
    for (const auto& [slot, card] : equippedItems) {
        if (card) {
            totalPower += card->getPowerBonus();
        }
    }

    setPlayerPower(totalPower);
}