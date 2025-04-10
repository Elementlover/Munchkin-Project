#include "GameInstance.h"
#include "GamePlayer.h"
#include "DeckManager.h"
#include <iostream>
#include <algorithm>

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
    deck = deckManager.loadCards("cards.json");

    cout << "Welcome to Munchkin!\n";

    if (!deck.empty()) {
        cout << "Deck loaded successfully with " << deck.size() << " cards.\n";

        auto card1 = deck[0];
        auto card2 = deck[1];

        cout << "First card in deck: " << card1->getName() << endl;
        card1->playCard(*activePlayers[0], *this);

        card2->playCard(*activePlayers[1], *this);
    }
    else {
        cout << "Failed to load deck.\n";
        return;
    }

    do {
        activePlayers[0]->addOneLevel();
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