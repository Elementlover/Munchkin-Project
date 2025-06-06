#include "DeckManager.h"
#include <random>


std::vector<std::shared_ptr<Card>> DeckManager::loadAllCards(const std::string& filePath) {
    return loadCardsByType(filePath, "");
}

std::vector<std::shared_ptr<Card>> DeckManager::loadDoorCards(const std::string& filePath) {
    return loadCardsByType(filePath, "Door");
}

std::vector<std::shared_ptr<Card>> DeckManager::loadTreasureCards(const std::string& filePath) {
    return loadCardsByType(filePath, "Treasure");
}

std::vector<std::shared_ptr<Card>> DeckManager::loadCardsByType(const std::string& filePath, const std::string& typeFilter) {
    //std::cout << "Loading cards from " << filePath << std::endl; //debug line
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Error: Could not open file at " << filePath << std::endl;
        return {};
    }
    else {
        std::cout << "File opened successfully." << std::endl;
    }

    nlohmann::json data;

    try {
        file >> data;

        //cout << "JSON content:" << data << endl; //debug line

        std::vector<std::shared_ptr<Card>> cards;
        for (const auto& cardData : data) {
            auto card = CardManager::createCardFromJson(cardData);
            if (card) {
                if (typeFilter.empty() || card->getType() == typeFilter) {
                    //cout << "Loaded card: " << card->getName() << endl; //debug line
                    cards.push_back(card);
                }
            }
            else {
                std::cout << "Failed to create card from JSON data." << std::endl;
            }
        }

        //Shuffle cards
        std::random_device rd;
        std::shuffle(cards.begin(), cards.end(), std::default_random_engine(rd()));

        std::cout << "Loaded and shuffled " << cards.size() << " card(s) with type filter: \"" << typeFilter << "\"\n";
        return cards;
    }
    catch (const nlohmann::json::parse_error& e) {
        std::cout << "JSON parse error: " << e.what() << std::endl;
        return {};
    }
    catch (const std::ifstream::failure& e) {
        std::cout << "File read error: " << e.what() << std::endl;
        return {};
    }
}