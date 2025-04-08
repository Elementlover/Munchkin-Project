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

        if (data["tags"].contains("equipment")) {
			cout << "Creating Equipment Card: " << name << endl; //debug line
			int powerBonus = data["effects"]["powerBonus"];
			bool twoHanded = data["effects"]["twoHanded"]; // TODO check what the default value is
			return make_shared<EquipmentItemCard>(name, description, powerBonus, twoHanded);
            /*int boost = data["effects"]["powerBoost"];
            return make_shared<PowerBoostCard>(name, description, type, tags, boost);*/
        }

        // Add more conditionals for other card types like CurseCard, etc.

        return nullptr;
    }
};

