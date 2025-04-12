#pragma once

#include "Card.h"
#include "CardManager.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

class GamePlayer; // Forward declaration

class DeckManager
{
public:
    std::vector<std::shared_ptr<Card>> loadAllCards(const std::string& filePath);
    std::vector<std::shared_ptr<Card>> loadDoorCards(const std::string& filePath);
    std::vector<std::shared_ptr<Card>> loadTreasureCards(const std::string& filePath);

private:
    // shared internal logic to make more readable functions
    std::vector<std::shared_ptr<Card>> loadCardsByType(const std::string& filePath, const std::string& typeFilter);
};