#include "CardManager.h"
#include "Card.h"
#include "EquipmentItemCard.h"

#include <iostream>
#include <algorithm>

using namespace std;
using json = nlohmann::json;

shared_ptr<Card> CardManager::createCardFromJson(const json& data) {
    const string name = data["name"];
    const string description = data["description"];
    const string type = data["type"];
    const vector<string> tags = data["tags"];

#ifdef DEBUG_MODE
    std::cout << "Creating card from JSON: " << name << std::endl;
#endif

    if (std::find(tags.begin(), tags.end(), "equipment") != tags.end()) {
        return createEquipmentCard(data);
    }

    if (std::find(tags.begin(), tags.end(), "curse") != tags.end()) {
        return createCurseCard(data);
    }

    if (std::find(tags.begin(), tags.end(), "monster") != tags.end()) {
        return createMonsterCard(data);
    }

#ifdef DEBUG_MODE
    std::cout << "Card type not matched. Name: " << name << std::endl;
#endif

    return nullptr;
}

shared_ptr<Card> CardManager::createEquipmentCard(const json& data) {
    const string name = data["name"];
    const string description = data["description"];
    const string type = data["type"];

    int powerBonus = data["effects"]["powerBonus"];
    bool twoHanded = data["effects"].value("twoHanded", false); // TODO check what the default value is

    return make_shared<EquipmentItemCard>(name, description, type, powerBonus, twoHanded);
}

shared_ptr<Card> CardManager::createCurseCard(const json& data) {
    const string name = data["name"];
    const string description = data["description"];
    const string type = data["type"];

    int levelChange = data["effects"]["levelChange"];
    int powerChange = data["effects"].value("powerChange", 0);

    return make_shared<CurseCard>(name, description, type, levelChange, powerChange);
}

shared_ptr<Card> CardManager::createMonsterCard(const json& data) {
    const string name = data["name"];
    const string description = data["description"];
    const string type = data["type"];

    int level = data.value("level", 1); // defaults to level 1 if not specified

    auto winEffects = extractEffects(data.value("WinEffect", json::object()));
    auto loseEffects = extractEffects(data.value("LoseEffect", json::object()));

    return make_shared<MonsterCard>(name, description, type, level, winEffects, loseEffects);
}

unordered_map<string, int> CardManager::extractEffects(const json& effectData) {
    unordered_map<string, int> effects;

    for (auto it = effectData.begin(); it != effectData.end(); ++it) {
        if (it.value().is_number_integer()) {
            effects[it.key()] = it.value();
        }
    }

    return effects;
}