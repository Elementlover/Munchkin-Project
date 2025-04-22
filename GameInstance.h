#pragma once

#include <vector>
#include <memory>
#include <string>

class GamePlayer;
class Card;

class GameInstance {
private:
    std::vector<GamePlayer*> activePlayers;
    int currentPlayerIndex = 0;
    std::vector<std::shared_ptr<Card>> deck;
    std::vector<std::shared_ptr<Card>> initialDeck; // restock
	std::vector<std::shared_ptr<Card>> discardDeck; // discard pile

	std::vector<std::shared_ptr<Card>> doorDeck;
	std::vector<std::shared_ptr<Card>> doorDeckInitial; // restock
	std::vector<std::shared_ptr<Card>> treasureDeck;
	std::vector<std::shared_ptr<Card>> treasureDeckInitial; // restock
	// Game state variables
	bool gameOver = false;
	int turnCounter = 0;

public:
    GameInstance();
    ~GameInstance();

    void run();
    bool checkWinCondition();
    GamePlayer& GetCurrentPlayer();

	std::shared_ptr<Card> drawFromDeck(std::vector<std::shared_ptr<Card>>& targetDeck,
		std::vector<std::shared_ptr<Card>>& initialDeckRef,
		const std::string& deckName);

	std::shared_ptr<Card> drawTreasureCard();
	std::shared_ptr<Card> drawDoorCard();

	void discardCard(std::shared_ptr<Card> card);

private:
    void displayResults();
	void displayPlayerStats(); //TODO
	void displayCardStats(); //TODO
    void runTurn();
};