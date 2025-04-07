#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "GamePlayer.h"

using namespace std;

class GameInstance
{
private:
    vector<GamePlayer*> activePlayers;

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
        cout << "Welcome to Munchkin!\n";

        do {
            // Game logic (just leveling player 1 for demo)
            activePlayers[0]->addOneLevel();
        } while (!checkWinCondition());

        displayResults();
    }

private:
    bool checkWinCondition() {
        for (auto player : activePlayers) {
            if (player->getPlayerLevel() >= 10) {
                return true;
            }
        }
        return false;
    }

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
};
