// Munchkin Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// test change

#include <iostream>
#include <vector>
#include <algorithm>
#include "GamePlayer.h"
#include "GameInstance.h"
#include <json.hpp>

using namespace std;
using json = nlohmann::json;


int main()
{
	// Ask for player names
	vector<string> playerNames;
	string playerName;
	int numPlayers = 0;

	cout << "Welcome to Munchkin! Please enter up to 4 player names.\n";

	// Loop to get up to 4 player names
	while (numPlayers < 4) {
		cout << "Enter name for player " << numPlayers + 1 << " (or press enter to stop): ";
		getline(cin, playerName);

		// If player name is empty, stop asking for more players
		if (playerName.empty()) {
			break;
		}

		playerNames.push_back(playerName);
		numPlayers++;
	}

	// Ensure we have at least 1 player
	if (playerNames.empty()) {
		cout << "You need at least one player to start the game.\n";
		return 1;
	}

	// Create Active Game Instance and set up the players dynamically
	GameInstance gameInstance;

	// Dynamically add players based on input
	gameInstance.setPlayers(playerNames);

	// Run the game
	cout << endl;

	gameInstance.run();
	// Cleanup
	
	// No need to delete players here, GameInstance destructor handles it
	return 0;



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