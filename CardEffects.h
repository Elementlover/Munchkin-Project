#pragma once
#include "GamePlayer.h"
#include <string>

namespace CardEffects
{	
	// Function to apply a card effect to a player
	void applyEffect(GamePlayer& player, const string& effectType, int value);

	// Function to apply a tag effect to a player
	//void applyEffect(GamePlayer& player, const string& tag);
};

