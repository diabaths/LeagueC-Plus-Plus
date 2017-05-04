#pragma once
#include "Items.h"

inline void jungleclear()
{
	for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
	{
		
		if (JungleQ->Enabled() && Q->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
			{
				Q->CastOnUnit(jMinion);
				return;
			}
		}
		if (W->IsReady() && myHero->HealthPercent()<=2)
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, W->Range()))
			{
				W->CastOnPlayer();
				return;
			}
		}
		if (JungleE->Enabled() && E->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead())
			{
				if (myHero->HasBuff("VladimirE") && myHero->IsValidTarget(jMinion, E->Range()))
				{
					E->CastOnPlayer();
					return;
				}
				if (!myHero->HasBuff("VladimirE") && myHero->IsValidTarget(jMinion, E->Range()))
				{
					E->StartCharging();
					return;
				}
			}
		}
	}
}
