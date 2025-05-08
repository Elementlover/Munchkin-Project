#include "CardManager.h"
#include "Card.h"
#include "EquipmentItemCard.h"
#include "EquipmentSlot.h"

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

    // Parse handedness
	Handedness handedness = Handedness::OneHanded; //default to OneHanded
    string handStr = data["effects"].value("handedness", "OneHanded");
    if (handStr == "TwoHanded") handedness = Handedness::TwoHanded;

    // Parse slot
	EquipmentSlot slot = EquipmentSlot::Body; // default to Body
    string slotStr = data["effects"].value("slot", "Body");
    if (slotStr == "Head") slot = EquipmentSlot::Head;
    else if (slotStr == "Body") slot = EquipmentSlot::Body;
    else if (slotStr == "Feet") slot = EquipmentSlot::Feet;
    else if (slotStr == "LeftHand") slot = EquipmentSlot::LeftHand;
    else if (slotStr == "RightHand") slot = EquipmentSlot::RightHand;
    else if (slotStr == "TwoHanded") slot = EquipmentSlot::TwoHanded;
    else if (slotStr == "Hireling") slot = EquipmentSlot::Hireling;

    return make_shared<EquipmentItemCard>(
        name, description, type, powerBonus, handedness, slot
    );
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

    auto winJson = data.value("WinEffect", json::object());
    auto loseJson = data.value("Bad Stuff", json::object());

    auto winEffects = extractEffects(data.value("WinEffect", json::object()));
    auto loseEffects = extractEffects(data.value("Bad Stuff", json::object()));

    std::string winDesc = winJson.value("description", "");
    std::string loseDesc = loseJson.value("description", "");

    return make_shared<MonsterCard>(name, description, type, level, winEffects, loseEffects, winDesc, loseDesc);
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