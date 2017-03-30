#pragma once
#include "Extensions.h"

inline  void burst()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1000);
	GGame->IssueOrder(myHero, kAttackUnit, GGame->CursorPosition());
	GOrbwalking->Orbwalk(Enemy, GGame->CursorPosition());
	auto mana = Q->ManaCost() + E->ManaCost() + R->ManaCost();
	if (Enemy != nullptr && myHero->IsValidTarget(Enemy, Q->Range() - 100) && myHero->GetMana() >= mana)
	{
		UseItems();
		E->CastOnPosition(Enemy->ServerPosition());
		R->CastOnPosition(Enemy->ServerPosition());
		GOrbwalking->ResetAA();
		if (!R->IsReady())
		{
			Q->CastOnPosition(Enemy->GetPosition());
		}
		if (!Q->IsReady())
		{
			W->CastOnPosition(Enemy->GetPosition());
		}
	}
	
}
