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
	std::vector<std::shared_ptr<Card>> treasureDeck;

public:
    GameInstance();
    ~GameInstance();

    void run();
    bool checkWinCondition();
    GamePlayer& GetCurrentPlayer();

	std::shared_ptr<Card> drawCard();
	void discardCard(std::shared_ptr<Card> card);

private:
    void displayResults();
	void displayPlayerStats(); //TODO
	void displayCardStats(); //TODO
    void runTurn();
};