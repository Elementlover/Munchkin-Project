#pragma once
#include "Card.h"
#include "EquipmentItemCard.h"
#include <string>
#include <vector>
#include <memory>

class CardManager
{
public:
    static shared_ptr<Card> createCardFromJson(const json& data) { // TODO find why this uses a shared pointer and not a unique pointer 

		bool debug = false; // Set to true for debugging

        string name = data["name"];
        string description = data["description"];
        string type = data["type"];
        vector<string> tags = data["tags"];

        // Debug for values
        if (debug) {
            cout << "Card Name: " << name << endl;
            cout << "Card Type: " << type << endl;
            cout << "Card Description: " << description << endl;
            cout << "Card Tags: ";
            for (const auto& tag : tags) {
                cout << tag << " ";
            }
            cout << endl;
        }

        if (find(tags.begin(), tags.end(), "equipment") != tags.end()) {
			//cout << "Creating Equipment Card: " << name << endl; //debug line
			int powerBonus = data["effects"]["powerBonus"];
            bool twoHanded = data["effects"].value("twoHanded", false); // TODO check what the default value is
			return make_shared<EquipmentItemCard>(name, description, powerBonus, twoHanded);
        }

		if (find(tags.begin(), tags.end(), "curse") != tags.end()) {
			//cout << "Creating Curse Card: " << name << endl; //debug line
			int levelChange = data["effects"]["levelChange"];
			int powerChange = data["effects"].value("powerChange", 0);

			return make_shared<CurseCard>(name, description, levelChange, powerChange);
		}

        if (find(tags.begin(), tags.end(), "monster") != tags.end()) {
			int level = data.value("level", 1); // defaults to level 1 if not specified

            auto winEffects = extractEffects(data.value("WinEffect", json::object())); // passes an empty vector to avoid crashes
            auto loseEffects = extractEffects(data.value("LoseEffect", json::object()));

			return make_shared<MonsterCard>(name, description, level, winEffects, loseEffects);
		}
		if (true) { // debug line
			cout << "Creating Monster Card: " << name << endl; //debug line
        }

        // Add more conditionals for other card types like CurseCard, etc.

        return nullptr;
    }

private:
	// Function to pull effects from JSON data
    static unordered_map<string, int> extractEffects(const json& effectData) {
        unordered_map<string, int> effects;

        for (auto it = effectData.begin(); it != effectData.end(); ++it) {
            // Only keep numeric effects
            if (it.value().is_number_integer()) { // check if integer
                effects[it.key()] = it.value();
            }
        }

        return effects;
    }
};

