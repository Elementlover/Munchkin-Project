#pragma once

#include "characterClass.h"
#include <string>
#include <vector>
#include <memory>
#include "Card.h" // Needed for shared_ptr<Card> use
#include "EquipmentSlot.h"

class EquipmentItemCard; // Forward declaration
class Card; // Forward declaration
class GameInstance; // Forward declaration


class GamePlayer
{
private:
	GameInstance* gameInstance; // Pointer to the game instance
    int playerLevel;
    int playerPower;
    characterClass activeClass;
    std::string playerName;
    std::vector<std::shared_ptr<Card>> heldCards;
    std::unordered_map<EquipmentSlot, std::shared_ptr<Card>> equippedItems;


public:
    GamePlayer(std::string name = "Default Name", int level = 1, int power = 1, characterClass cls = characterClass());

	~GamePlayer();

    // Getters
    GameInstance* getGameInstance() const;
    int getPlayerLevel() const;
    int getPlayerPower() const;
    characterClass getActiveClass() const;
    std::string getPlayerName() const;

    // Setters
    void setGameInstance(GameInstance* game);
    void setPlayerLevel(int level);
    void setPlayerPower(int power);
    void setPlayerName(std::string name);
    void setActiveClass(characterClass cls);

    void addOneLevel();

    // Card management
    void addCardtoHand(std::shared_ptr<Card> card);
    bool removeCard(const std::string& cardName);
    std::vector<std::shared_ptr<Card>> getHeldCards() const;
    void listHeldCards() const;

	// Card actions
    std::vector<std::string> getAvailableActions() const;
    void equipItem(std::shared_ptr<EquipmentItemCard> equipmentCard);
    void listEquippedItems() const;
};


	// old removeCard function
    //void removeCard(const string& cardName) { 
    //    // TODO
    //    // This remove syntax moves elements to the back of the vector instead of checking and then removing
    //    // Going linearly throught the vector and deleting one copy is prefered
    //    // The .erase function only removes the tail end of a container
    //    heldCards.erase(remove_if(heldCards.begin(), heldCards.end(),
    //        [&](const shared_ptr<Card>& c) { // [&] captures by reference
    //            return c->getName() == cardName;
    //        }), heldCards.end());
    //}