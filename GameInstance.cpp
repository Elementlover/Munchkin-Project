#include "GameInstance.h"
#include "GamePlayer.h"
#include "DeckManager.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

GameInstance::GameInstance() {
    activePlayers.push_back(new GamePlayer("Alice"));
    activePlayers.push_back(new GamePlayer("Ben"));
    activePlayers.push_back(new GamePlayer("Cathy"));
}

GameInstance::~GameInstance() {
    for (auto player : activePlayers) {
        delete player;
    }
}

void GameInstance::run() {
    DeckManager deckManager;

    //deck = deckManager.loadAllCards("cards.json"); // depreciated
	//initialDeck = deck; // Store the initial deck for restocking

	doorDeck = deckManager.loadDoorCards("cards.json");
	doorDeckInitial = doorDeck;
    treasureDeck = deckManager.loadTreasureCards("cards.json");
	treasureDeckInitial = treasureDeck;

    cout << "Welcome to Munchkin!\n";

    if (!doorDeck.empty() && !treasureDeck.empty()) {
        cout << "Door Deck loaded successfully with " << doorDeck.size() << " cards.\n";
        cout << "Treasure Deck loaded successfully with " << treasureDeck.size() << " cards.\n";
    }
    else {
        cout << "Failed to load deck.\n";
        return;
    }

    do {
        runTurn();
        currentPlayerIndex = (currentPlayerIndex + 1) % activePlayers.size(); // change this to have a turn counter
    } while (!checkWinCondition());

    displayResults();
}

bool GameInstance::checkWinCondition() {
    for (auto player : activePlayers) {
        if (player->getPlayerLevel() >= 10) {
            return true;
        }
    }
    return false;
}

GamePlayer& GameInstance::GetCurrentPlayer() {
    return *activePlayers[currentPlayerIndex];
}

std::shared_ptr<Card> GameInstance::drawFromDeck(std::vector<std::shared_ptr<Card>>& targetDeck,
    std::vector<std::shared_ptr<Card>>& initialDeckRef,
    const std::string& deckName)
{
    if (targetDeck.empty()) {
        std::cout << "Deck is empty. Restocking from initialDeck.\n";
        targetDeck = initialDeckRef;
         // Reshuffle deck
		std::random_device rd;
        std::shuffle(targetDeck.begin(), targetDeck.end(), std::default_random_engine(rd()));
    }

    // safety check
    if (targetDeck.empty()) {
        std::cout << "No cards left to draw even after restocking!\n";
        return nullptr;
    }

    //draw card
    auto card = targetDeck.back();
    targetDeck.pop_back();
    return card;
}

std::shared_ptr<Card> GameInstance::drawTreasureCard() {
    return drawFromDeck(treasureDeck, treasureDeckInitial, "Treasure Deck");
}

std::shared_ptr<Card> GameInstance::drawDoorCard() {
    return drawFromDeck(doorDeck, doorDeckInitial, "Door Deck");
}

void GameInstance::discardCard(std::shared_ptr<Card> card)
{
	discardDeck.push_back(card);
	//cout << "Discarded card: " << card->getName() << endl; // debug
}

void GameInstance::displayResults() {
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
void GameInstance::runTurn() {
    GamePlayer& player = *activePlayers[currentPlayerIndex];
    cout << "\n--- " << player.getPlayerName() << "'s turn ---\n";

    // Draw card
	auto card = drawDoorCard();
     
    // big learning point
	// Check if card is valid
    if (!card) {
        cout << "No card drawn. Skipping turn.\n";
        return;
    }

    cout << player.getPlayerName() << " draws a card: " << card->getName() << endl;
    card->playCard(player, *this);
    //player.addOneLevel();
}