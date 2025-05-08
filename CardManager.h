#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <json.hpp>

// Forward declarations to avoid circular includes
class Card;

class CardManager {
public:
    static std::shared_ptr<Card> createCardFromJson(const nlohmann::json& data); // TODO find why this uses a shared pointer and not a unique pointer

private:
    static std::unordered_map<std::string, int> extractEffects(const nlohmann::json& effectData); // Function to pull effects from JSON data
};