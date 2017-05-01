#pragma once
#include "Extension.h"


inline void Harass()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1500);
	
	if (Enemy != nullptr && !Enemy->IsDead())
	{
		if (HarassQ->Enabled() && Q->IsReady())
		{
			if (myHero->IsValidTarget(Enemy, Q->Range()))
			{
				Q->CastOnUnit(Enemy);
			}
		}
		if (HarassW->Enabled() && W->IsReady())
		{
			if (Enemy->IsValidTarget(myHero, W->Range()))
			{
				W->CastOnPlayer();
			}
		}
		if (HarassE->Enabled())
		{
			if (E->IsReady() && myHero->IsValidTarget(Enemy, E->Range()))
			{
				AdvPredictionOutput EPred;
				E->RunPrediction(Enemy, true, kCollidesWithYasuoWall | kCollidesWithMinions, &EPred);

				if (EPred.HitChance >= kHitChanceHigh)
				{
					E->CastOnUnit(Enemy);
				}
			}
		}
	}
}
