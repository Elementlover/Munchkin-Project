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
        string name = data["name"];
        string description = data["description"];
        string type = data["type"];
        vector<string> tags = data["tags"];

        // Debug the values
        cout << "Card Name: " << name << endl;
        cout << "Card Type: " << type << endl;
        cout << "Card Description: " << description << endl;
        cout << "Card Tags: ";
        for (const auto& tag : tags) {
            cout << tag << " ";
        }
        cout << endl;

        if (find(tags.begin(), tags.end(), "equipment") != tags.end()) {
			cout << "Creating Equipment Card: " << name << endl; //debug line
			int powerBonus = data["effects"]["powerBonus"];
            bool twoHanded = data["effects"].value("twoHanded", false); // TODO check what the default value is
			return make_shared<EquipmentItemCard>(name, description, powerBonus, twoHanded);
            /*int boost = data["effects"]["powerBoost"];
            return make_shared<PowerBoostCard>(name, description, type, tags, boost);*/
        }

        // Add more conditionals for other card types like CurseCard, etc.

        return nullptr;
    }
};

