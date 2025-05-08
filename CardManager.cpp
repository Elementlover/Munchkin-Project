#include "CardManager.h"
#include "Card.h"
#include "EquipmentItemCard.h"

#include <iostream>
#include <algorithm>

using namespace std;
using json = nlohmann::json;

// #define DEBUG_MODE // Uncomment to enable debug logging

shared_ptr<Card> CardManager::createCardFromJson(const json& data) {
    bool debug = false; // Set to true for debugging

    string name = data["name"];
    string description = data["description"];
    string type = data["type"];
    vector<string> tags = data["tags"];

#ifdef DEBUG_MODE // Debugging output
    std::cout << "Card Name: " << name << "\n"
        << "Card Type: " << type << "\n"
        << "Card Description: " << description << "\n"
        << "Card Tags: ";
    for (const auto& tag : tags) {
        std::cout << tag << " ";
    }
    std::cout << std::endl;
#endif

    if (std::find(tags.begin(), tags.end(), "equipment") != tags.end()) {
        //cout << "Creating Equipment Card: " << name << endl; //debug line
        int powerBonus = data["effects"]["powerBonus"];
        bool twoHanded = data["effects"].value("twoHanded", false); // TODO check what the default value is
        return make_shared<EquipmentItemCard>(name, description, type, powerBonus, twoHanded);
    }

    if (std::find(tags.begin(), tags.end(), "curse") != tags.end()) {
        //cout << "Creating Curse Card: " << name << endl; //debug line
        int levelChange = data["effects"]["levelChange"];
        int powerChange = data["effects"].value("powerChange", 0);
        return make_shared<CurseCard>(name, description, type, levelChange, powerChange);
    }

    if (std::find(tags.begin(), tags.end(), "monster") != tags.end()) {
        int level = data.value("level", 1); // defaults to level 1 if not specified

        auto winEffects = extractEffects(data.value("WinEffect", json::object())); // passes an empty vector to avoid crashes
        auto loseEffects = extractEffects(data.value("LoseEffect", json::object()));

        return make_shared<MonsterCard>(name, description, type, level, winEffects, loseEffects);
    }

	// If no card type matches, return nullptr
#ifdef DEBUG_MODE
    std::cout << "Card type not matched. Name: " << name << std::endl;
#endif
    // TODO Add more conditionals for other card types like CurseCard, etc.

    return nullptr;
}

unordered_map<string, int> CardManager::extractEffects(const json& effectData) {
    unordered_map<string, int> effects;

    for (auto it = effectData.begin(); it != effectData.end(); ++it) {
        // Only keep numeric effects
        if (it.value().is_number_integer()) { // check if integer
            effects[it.key()] = it.value();
        }
    }

    return effects;
}