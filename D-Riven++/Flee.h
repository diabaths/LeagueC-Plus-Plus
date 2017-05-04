#pragma once
#include "Spells.h"

static void Flee()
{

	GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	auto epos = myHero->GetPosition().Extend(GGame->CursorPosition(), 300);
	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
		if (Enemy != nullptr && W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
		{
			W->CastOnPlayer();
		}
	}
	if (Q->IsReady() && !myHero->IsRecalling())
	{
		Q->CastOnPosition(GGame->CursorPosition());
	}
	if (E->IsReady())
	{
		E->CastOnPosition(epos);
		LastE = GGame->CurrentTick();
	}
}
