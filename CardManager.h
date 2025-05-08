#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <json.hpp>
#include "Card.h"

class CardManager {
public:
    static std::shared_ptr<Card> createCardFromJson(const nlohmann::json& data);

private:
    static std::shared_ptr<Card> createEquipmentCard(const nlohmann::json& data);
    static std::shared_ptr<Card> createCurseCard(const nlohmann::json& data);
    static std::shared_ptr<Card> createMonsterCard(const nlohmann::json& data);

    static std::unordered_map<std::string, int> extractEffects(const nlohmann::json& effectData);
};