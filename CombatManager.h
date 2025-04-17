#pragma once
#include "GamePlayer.h"
#include "Card.h"
#include "CardEffects.h"
#include "GameInstance.h"

class CombatManager
{
public:
	static void resolveCombat(GamePlayer& player, MonsterCard& monster, GameInstance& game);
};

// TODO add a function to resolve combat with multiple players