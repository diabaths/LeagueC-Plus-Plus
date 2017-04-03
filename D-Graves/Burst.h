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
		//if (!myHero->GetBuffDataByName("GravesBasicAttackAmmo2"))
		//{
			E->CastOnPosition(Enemy->ServerPosition());
		//}
		GOrbwalking->ResetAA();
		if (!E->IsReady() && GGame->CurrentTick() - lastE > 0.01f)
		{
			R->CastOnPosition(Enemy->ServerPosition());
		}
		if (!R->IsReady() && GGame->CurrentTick() - lastR > 0.01f)
		{
			Q->CastOnPosition(Enemy->GetPosition());
		}
		if (!Q->IsReady())
		{
			W->CastOnPosition(Enemy->GetPosition());
		}
	}
	
}
