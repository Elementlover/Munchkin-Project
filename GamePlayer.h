#pragma once
#include "characterClass.h"

using namespace std;

class GamePlayer
{
private:
	int playerLevel;
	int playerPower;
	characterClass activeClass;
    string playerName;
    vector<shared_ptr<Card>> heldCards;

public:
	GamePlayer(string name = "Default Name", int level = 1, int power = 1, characterClass cls = characterClass())
		: playerName(name), playerLevel(level), playerPower(power), activeClass(cls) {}

    // Getters
    int getPlayerLevel() const { return playerLevel; }
    int getPlayerPower() const { return playerPower; }
    characterClass getActiveClass() const { return activeClass; }
    string getPlayerName() const { return playerName; }

    // Setters
    void setPlayerLevel(int level) { playerLevel = level; }
    void setPlayerPower(int power) { playerPower = power; }
    void setPlayerName(string name) { playerName = name; }
    void setActiveClass(characterClass cls) { activeClass = cls; }

	void addOneLevel() { playerLevel++; }

    // card management
    void addCard(shared_ptr<Card> card) {
        heldCards.push_back(card);
    }


    bool removeCard(const string& cardName) {
        for (auto it = heldCards.begin(); it != heldCards.end(); ++it) {
            if ((*it)->getName() == cardName) {
                heldCards.erase(it);
                return true;
            }
        }
        return false; // Not found
    }

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

};

