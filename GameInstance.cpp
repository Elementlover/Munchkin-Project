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

    for (auto* player : activePlayers) {
        player->setGameInstance(this);
    }
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
        std::cout << "Deck is empty. Restocking...\n";
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

    bool turnInProgress = true;

    while (turnInProgress) {
        auto options = player.getAvailableActions();

        cout << "Choose an action:\n";
        for (size_t i = 0; i < options.size(); ++i) {
            cout << i + 1 << ". " << options[i] << "\n";
        }

        int choice = -1;
        std::string inputLine;
        cout << "Enter your choice: ";
        std::getline(std::cin >> std::ws, inputLine);  // std::ws eats up any leading whitespace
		cout << endl;

        // Reject non-digit input
        if (!std::all_of(inputLine.begin(), inputLine.end(), ::isdigit)) {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        choice = std::stoi(inputLine);

        if (choice < 1 || choice > static_cast<int>(options.size())) {
            cout << "Invalid choice. Try again.\n";
            continue;
        }

        const std::string& selectedAction = options[choice - 1];

        if (selectedAction == "Draw Door Card") {
            auto card = drawDoorCard();
            if (!card) {
                cout << "No card drawn. Skipping turn.\n";
            }
            else {
                cout << player.getPlayerName() << " draws a card: " << card->getName() << endl;
                card->playCard(player, *this);
            }
            turnInProgress = false; // End turn after drawing
        }
        else if (selectedAction == "View Hand") {
            player.listHeldCards();
        }
        else if (selectedAction == "Skip Turn") {
            cout << player.getPlayerName() << " ends their turn.\n";
            turnInProgress = false;
        }
        else {
            cout << "Action not implemented yet: " << selectedAction << "\n";
        }
    }
}