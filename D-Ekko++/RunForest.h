#pragma once
#include "Extension.h"
inline void runforest()
{
	auto Qmana = Q->ManaCost();
	auto Wmana = W->ManaCost();
	auto Emana = E->ManaCost();
	auto mana = Qmana + Wmana + Emana;
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
	GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	if (Enemy != nullptr)
	{
		if (myHero->IsValidTarget(Enemy, W->Range()) && mana)
		{
			if (W->IsReady())
			{
				W->CastOnPosition(myHero->GetPosition());
			}
			if (Q->IsReady() && myHero->IsValidTarget(Enemy, Q->Range()))
			{
				Q->CastOnTarget(Enemy, kHitChanceHigh);
			}
		}
		if(E->IsReady() && myHero->IsValidTarget(Enemy, Q->Range()))
		{
			E->CastOnPosition(myHero->GetPosition().Extend(GGame->CursorPosition(), E->Range()));
		}
		if (protobelt->IsOwned() && protobelt->IsReady())
		{
			protobelt->CastOnPosition(myHero->GetPosition().Extend(GGame->CursorPosition(), 600));
		}
	}
} 