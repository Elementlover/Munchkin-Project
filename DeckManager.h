#pragma once
#include "Card.h"
#include "CardManager.h"
#include <fstream>


class DeckManager
{
private:
	vector<shared_ptr<Card>> deck; // Vector to hold the deck of cards
	int currentCardIndex; // index, used for drawing cards and functionality can change

public:

    vector<shared_ptr<Card>> loadCards(const string& filePath) {
        ifstream file(filePath);
        nlohmann::json data;
        file >> data;

        vector<shared_ptr<Card>> cards;
        for (const auto& cardData : data) {
            auto card = CardManager::createCardFromJson(cardData);
            if (card) {
                cards.push_back(card);
            }
        }

        return cards;
    }
};

