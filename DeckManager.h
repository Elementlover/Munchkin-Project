#pragma once
#include "Card.h"
#include "CardManager.h"
#include <fstream>

#include <direct.h>
#include <iostream>

class DeckManager
{
private:
	vector<shared_ptr<Card>> deck; // Vector to hold the deck of cards
	int currentCardIndex; // index, used for drawing cards and functionality can change

public:

    vector<shared_ptr<Card>> loadCards(const string& filePath) {
		cout << "Loading cards from " << filePath << endl; //debug line
        ifstream file(filePath);

        if (!file.is_open()) { //debug
            cout << "Error: Could not open file at " << filePath << endl;
            return {};
        }
        else {
			cout << "File opened successfully." << endl;
        }

        json data;

        try {
            file >> data;

			cout << "JSON content:" << data << endl; //debug line

            vector<shared_ptr<Card>> cards;
            for (const auto& cardData : data) {
                auto card = CardManager::createCardFromJson(cardData);
                if (card) {
					cout << "Loaded card: " << card->getName() << endl; //debug line
                    cards.push_back(card);
				}
                else {
                    cout << "Failed to create card from JSON data." << endl;
                }
            }
            return cards;
		}
		catch (const json::parse_error& e) {
			cout << "JSON parse error: " << e.what() << endl;
			return {};
		}
        catch (const ifstream::failure& e) {
            cout << "File read error: " << e.what() << endl;
            return {};
        }
    }
};

