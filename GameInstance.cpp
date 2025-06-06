#include "GameInstance.h"
#include "GamePlayer.h"
#include "DeckManager.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

GameInstance::GameInstance() {
    //activePlayers.push_back(new GamePlayer("Alice"));
    //activePlayers.push_back(new GamePlayer("Ben"));
    //activePlayers.push_back(new GamePlayer("Cathy"));

    //for (auto* player : activePlayers) {
    //    player->setGameInstance(this);
    //}
}

GameInstance::~GameInstance() {
    for (auto player : activePlayers) {
        delete player;
    }
}

void GameInstance::setPlayers(const vector<string>& playerNames) {
    // Clear any existing players
    activePlayers.clear();

    // Create players based on the input list of names
    for (const string& name : playerNames) {
        activePlayers.push_back(new GamePlayer(name));
    }

    // Set the game instance for each player
    for (auto* player : activePlayers) {
        player->setGameInstance(this);
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

	// Hand out 4 treasure and 4 Door cards to each player
    for (auto* player : activePlayers) {
        for (int i = 0; i < 4; ++i) {
            auto doorCard = drawDoorCard();
            if (doorCard) {
                player->addCardtoHand(doorCard);
            }

            auto treasureCard = drawTreasureCard();
            if (treasureCard) {
                player->addCardtoHand(treasureCard);
            }
        }
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
    displayTitleCard(player);

    bool turnInProgress = true;

    while (turnInProgress) {
        auto options = player.getAvailableActions();

        cout << endl;
        cout << "Choose an action:\n";
        for (size_t i = 0; i < options.size(); ++i) {
            cout << i + 1 << ". " << options[i] << "\n";
        }

        int choice = getValidatedNumericInput(1, static_cast<int>(options.size()), "Enter your choice: ");
        const std::string& selectedAction = options[choice - 1];

        if (selectedAction == "Draw Door Card") {
            auto card = drawDoorCard();
            if (!card) {
                cout << "No card drawn. Skipping turn.\n";
            }
            else {
                cout << player.getPlayerName() << " draws a card: " << card->getName() << endl;
                cout << endl;

                // Use dynamic_cast to check if the card is a MonsterCard
                MonsterCard* monsterCard = dynamic_cast<MonsterCard*>(card.get()); // Cast to MonsterCard
                if (monsterCard) {  // If the cast succeeds, it's a MonsterCard
                    cout << player.getPlayerName() << " encounters a monster: " << card->getName() << endl;
                    monsterCard->playCard(player, *this);  // Resolve combat with the monster
                    turnInProgress = false;  // End the turn after fighting the monster
                }
                else {
                    card->playCard(player, *this);  // Otherwise, just play the card normally
                }
            }
        }
        else if (selectedAction == "View Hand") {
            while (true) {
                player.listHeldCards();

                // check for empty hand
                if (player.getHeldCards().empty()) {
                    break;
                }

                int cardChoice = getValidatedNumericInput(0, static_cast<int>(player.getHeldCards().size()),
                    "Enter the number of a card to play it, or 0 to go back: ");

                cout << endl;

                if (cardChoice == 0) {
                    break; // Go back to action selection
                }

                // Play the selected card
                auto selectedCard = player.getHeldCards()[cardChoice - 1];
                cout << "Playing card: " << selectedCard->getName() << endl;
                selectedCard->playCard(player, *this);

				// End the turn if it's a monster card


                // Only remove the card from hand if it�s still there (e.g., not equipped or discarded during playCard)
                const auto& hand = player.getHeldCards();
                if (std::find(hand.begin(), hand.end(), selectedCard) != hand.end()) {
                    player.removeCard(selectedCard->getName());
                }
            }

            displayTitleCard(player);
            continue; // Go back to action selection after playing a card
        }
        else if (selectedAction == "Skip Turn") {
            cout << player.getPlayerName() << " ends their turn.\n";
            turnInProgress = false;
        }
        else if (selectedAction == "View Equipped Items") {
            player.listEquippedItems();
            continue; // Stay in the action loop
        }
        else {
            cout << "Action not implemented yet: " << selectedAction << "\n";
        }
    }
}

int GameInstance::getValidatedNumericInput(int min, int max, const std::string& prompt) {
    std::string inputLine;
    int choice = -1;

    while (true) {
		std::cout << prompt;
		std::getline(std::cin >> std::ws, inputLine);  // std::ws eats up any leading whitespace
		std::cout << std::endl;

		// Reject non-digit input
		if (!std::all_of(inputLine.begin(), inputLine.end(), ::isdigit)) {
			std::cout << "Invalid input. Please enter a number.\n";
			continue;
		}

		// Convert to integer and check range
		choice = std::stoi(inputLine);
		if (choice < min || choice > max) {
			std::cout << "Invalid choice. Try again.\n";
			continue;
		}

	    return choice;
	}
}

void GameInstance::displayTitleCard(GamePlayer& player) {
    cout << "\n--- " << player.getPlayerName() << "'s Turn ---\n";
    cout << player.getPlayerName() << "'s Level: " << player.getPlayerLevel() << endl;
}