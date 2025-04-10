#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "GamePlayer.h"
#include "DeckManager.h"

using namespace std;

class GameInstance
{
private:
    vector<GamePlayer*> activePlayers;
	int currentPlayerIndex = 0;
	vector<shared_ptr<Card>> deck; // should be removed later
    vector<shared_ptr<Card>> DoorDeck;


public:
    GameInstance() {
        // Initialize players
        activePlayers.push_back(new GamePlayer("Alice"));
        activePlayers.push_back(new GamePlayer("Ben"));
        activePlayers.push_back(new GamePlayer("Cathy"));
    }

    ~GameInstance() {
        for (auto player : activePlayers) {
            delete player;
        }
    }

    void run() {

        DeckManager deckManager;
		auto deck = deckManager.loadCards("cards.json");

        cout << "Welcome to Munchkin!\n";

		if (!deck.empty()) { // TODO abstract this check to DeckManager
			cout << "Deck loaded successfully with " << deck.size() << " cards.\n";

            auto card = deck[0];
			auto card2 = deck[1];


			cout << "First card in deck: " << card->getName() << endl;
			card->playCard(*activePlayers[0], *this); // Play a card test
            
			card2->playCard(*activePlayers[1], *this); // Play a card test 2

		}
		else {
			cout << "Failed to load deck.\n";
			return;
		}

        do {
            // Game logic (just leveling player 1 for demo)
            runTurn();
            currentPlayerIndex = (currentPlayerIndex + 1) % activePlayers.size();
        } while (!checkWinCondition());

        displayResults();
    }

    bool checkWinCondition() {
        for (auto player : activePlayers) {
            if (player->getPlayerLevel() >= 10) {
                return true;
            }
        }
        return false;
    }

	GamePlayer& GetCurrentPlayer() {
		return *activePlayers[currentPlayerIndex];
	}

private:

    void displayResults() {
        sort(activePlayers.begin(), activePlayers.end(),
            [](const GamePlayer* a, const GamePlayer* b) {
                return a->getPlayerLevel() > b->getPlayerLevel();
            });

        cout << "The Winner of the game is " << activePlayers[0]->getPlayerName() << "!\n";

        for (auto player : activePlayers) {
            cout << player->getPlayerName() << ": Level " << player->getPlayerLevel() << endl;
        }
    }


    // Runs the turn of the current player, drawing a card from the deck
    void runTurn() {
        GamePlayer& player = *activePlayers[currentPlayerIndex];
        cout << "\n--- " << player.getPlayerName() << "'s turn ---\n";

        // Draw card
        if (!deck.empty()) {
            auto card = deck.back();
            deck.pop_back();
            cout << player.getPlayerName() << " draws a card: " << card->getName() << endl;
            card->playCard(player, *this);
        }
        else {
            cout << "No cards left to draw!\n";
        }

        player.addOneLevel();
 }
};
