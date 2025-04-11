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

public:
    GameInstance();
    ~GameInstance();

    void run();
    bool checkWinCondition();
    GamePlayer& GetCurrentPlayer();

private:
    void displayResults();
	void displayPlayerStats(); //TODO
	void displayCardStats(); //TODO
    void runTurn();
};