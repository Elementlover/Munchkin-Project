// Munchkin Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// test change

#include <iostream>
#include <vector>
#include <algorithm>
#include "GamePlayer.h"

using namespace std;

static bool checkWinCondition(vector<GamePlayer*> playerVector);

int main()
{
    // Create Active Game Instance (struct?)
    vector<GamePlayer*> activePlayers;

    GamePlayer* player1 = new GamePlayer("Alice");
    GamePlayer* player2 = new GamePlayer("Ben");
    GamePlayer* player3 = new GamePlayer("Cathy");

    activePlayers.push_back(player1);
    activePlayers.push_back(player2);
    activePlayers.push_back(player3);
    
    std::cout << "Welcome to Munchkin!\n";


    do {
        player1->addOneLevel();
    } while (!checkWinCondition(activePlayers));

    // End Game

    // Display Results

    sort(activePlayers.begin(), activePlayers.end(), [](const GamePlayer* a, const GamePlayer* b) {
        return a->getPlayerLevel() > b->getPlayerLevel();
        });
    
    cout << "The Winner of the game is " << activePlayers[0]->getPlayerName() << "!" << endl;

    for (GamePlayer* player : activePlayers) {
        cout << player->getPlayerName() << ": Level " << player->getPlayerLevel() << endl;
    }


}

static int Menu() {

}


bool checkWinCondition(vector<GamePlayer*> playerVector)
{
    for (GamePlayer* player : playerVector) {
        if (player->getPlayerLevel() >= 10) return true;
    }
    return false;
}

// to do list


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file