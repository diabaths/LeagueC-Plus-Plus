#pragma once

#include "Extension.h"


inline void laneclear()
{
	for (auto minions : GEntityList->GetAllMinions(false, true, false))
	{
		if (Q->IsReady())
		{
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
			if (FarmQ->Enabled() && minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
			{

				Q->CastOnUnit(minions);
				return;
			}
			if (LastHitQ->Enabled() && minions->GetHealth() < dmg && myHero->IsValidTarget(minions, Q->Range()))
			{
				Q->CastOnUnit(minions);
				return;
			}
		}

		if (FarmE->Enabled() && E->IsReady() && myHero->IsValidTarget(minions, E->Range()))
		{
			if (myHero->HealthPercent() > UseEHP->GetInteger())
			{
				if (CountminionInRange(E->Range()) >= minminionsE->GetInteger())
				{
					if (myHero->HasBuff("VladimirE") && myHero->IsValidTarget(minions, E->Range()))
					{
						E->CastOnPlayer();
						return;
					}
					if (!myHero->HasBuff("VladimirE") && myHero->IsValidTarget(minions, E->Range()))
					{
						E->StartCharging();
						return;
					}
				}
			}
		}
	}
}
