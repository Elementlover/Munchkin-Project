#pragma once
#include <string>

class GamePlayer; // Forward declaration

namespace CardEffects
{	
	// Function to apply a card effect to a player
	void applyEffect(GamePlayer& player, const std::string& effectType, int value);

	// Function to apply a tag effect to a player
	// void applyEffect(GamePlayer& player, const string& tag);
};

