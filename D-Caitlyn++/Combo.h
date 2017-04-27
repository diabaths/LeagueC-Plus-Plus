#pragma once
#include "Extension.h"

inline void Combo()
{
	if (ComboQ->Enabled())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		CastQ(target);
	}
	if (ComboW->Enabled() && W->IsReady() && GGame->CurrentTick() - LastWTick > 1500)
	{
		if (myHero->GetMana() > Q->ManaCost() + E->ManaCost())
		{
			auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			if (myHero->IsValidTarget(Enemy, W->Range()) && Enemy != nullptr && !Enemy->HasBuff("caitlynyordletrapinternal"))
			{
				AdvPredictionOutput prediction_output;
				W->RunPrediction(Enemy, true, kCollidesWithNothing, &prediction_output);
				if (!Enemy->IsInvulnerable() && prediction_output.HitChance >= kHitChanceHigh)
				{
					W->CastOnTarget(Enemy);
					LastWTick = GGame->CurrentTick();
				}
			}
		}
	}
	if (ComboR->Enabled() && R->IsReady() && GGame->CurrentTick() - QCastTime > 1000)
	{
		auto Rmin = RMin->GetInteger();
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, RRange);
		if (myHero->IsValidTarget(Enemy, RRange) && Enemy != nullptr)
		{
			auto dmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotR);
			if (Enemy->GetHealth() < dmg && !Enemy->IsInvulnerable() && GetDistance(myHero, Enemy) > Rmin &&  CountEnemiesInRange(RMinenemies->GetInteger()) == 0)
			{
				R->CastOnUnit(Enemy);
			}
		}
	}
}