#pragma once
#include "Items.h"

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
				return;
			}
		}

		if (E->IsReady() && HarassE->Enabled() && myHero->HealthPercent() > UseEHPH->GetInteger())
		{
			if (myHero->IsValidTarget(Enemy, E->Range() + 100))
			{
				E->CastOnPlayer();
				return;
			}
			if (myHero->HasBuff("VladimirE") && myHero->IsValidTarget(Enemy, E->Range()))
			{
				E->StartCharging();
			}
		}
	}
}
