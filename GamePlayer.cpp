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
    EquipmentSlot slot = equipmentCard->getSlotType();

    auto it = equippedItems.find(slot);
    if (it != equippedItems.end()) {
        std::cout << "Swapping out " << it->second->getName() << " from slot.\n";
        heldCards.push_back(it->second); // Return old equipment to hand
    }

    equippedItems[slot] = equipmentCard;
	recalculatePower(); // Recalculate power after equipping
    std::cout << "Equipped: " << equipmentCard->getName() << "\n";
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
    case EquipmentSlot::OneHand: return "One Hand";
    case EquipmentSlot::TwoHands: return "Two Hands";
    case EquipmentSlot::Hireling: return "Hireling";
    default: return "Unknown";
    }
}

void GamePlayer::recalculatePower() {
    int totalPower = 0;

    // Sum power bonuses from all equipped items
    for (const auto& [slot, card] : equippedItems) {
        if (card) {
            // Cast the card to EquipmentItemCard
            auto equipmentCard = std::dynamic_pointer_cast<EquipmentItemCard>(card);
            if (equipmentCard) {
                totalPower += equipmentCard->getPowerBonus();
            }
        }
    }

    setPlayerPower(totalPower);
}