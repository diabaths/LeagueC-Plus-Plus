#pragma once
#include "Spells.h"

static void Flee()
{
	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
		auto x = myHero->GetPosition().Extend(GGame->CursorPosition(), 300);
		if (Enemy != nullptr && W->IsReady() && myHero->IsValidTarget(Enemy, Wrange))
		{
			W->CastOnPlayer();
		}
		auto end = GBuffData->GetEndTime(myHero->GetBuffDataByName("RivenTriCleave"));
		auto start = GBuffData->GetStartTime(myHero->GetBuffDataByName("RivenTriCleave"));
		if (GGame->CurrentTick() - LastE > 100 && Q->IsReady() && end - GGame->Time() <= 1.1 * (end - start)  && !myHero->IsRecalling())
		{
			Q->CastOnPosition(GGame->CursorPosition());
		}
		if (E->IsReady() && !myHero->IsDashing())
		{
			E->CastOnPosition(x);
			LastE = GGame->CurrentTick();
		}
	}
}
