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
		
		if (nowauto)
		{
			R->CastOnPosition(Enemy->ServerPosition());
		}
			GOrbwalking->ResetAA();
			if (!R->IsReady())
			{
				E->CastOnPosition(Enemy->ServerPosition());
				GOrbwalking->ResetAA();
			}
		if (!E->IsReady() && !R->IsReady())
		{
			Q->CastOnPosition(Enemy->GetPosition());
		}
		if (!Q->IsReady() && !R->IsReady())
		{
			W->CastOnPosition(Enemy->GetPosition());
		}
	}	
}

static void burstAfter(IUnit* source, IUnit* target)
{

	if (target != nullptr && myHero->IsValidTarget(target, Q->Range() - 100))
	{
		auto mana = Q->ManaCost() + E->ManaCost() + R->ManaCost();
		
		if (nowauto)
		{
			R->CastOnPosition(target->ServerPosition());
		}
		if (E->IsReady() && !R->IsReady())
		{
			E->CastOnPosition(target->ServerPosition());
			GOrbwalking->ResetAA();
		}
		if (Q->IsReady() && !R->IsReady())
		{
			Q->CastOnPosition(target->GetPosition());
		}
		if (!Q->IsReady() && W->IsReady() && !R->IsReady())
		{
			W->CastOnPosition(target->GetPosition());
		}
	}
}
