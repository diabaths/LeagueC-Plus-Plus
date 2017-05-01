#pragma once

#include "Extension.h"
#include "Items.h"

inline void jungleclear()
{
	for (auto minions : GEntityList->GetAllMinions(false, false, true))
	{ 
		if (Q->IsReady() && JungleQ->Enabled())
		{
			if (myHero->IsValidTarget(minions, Q->Range()))
			{
				Q->CastOnUnit(minions);
			}
		}
		if (Itemsinlane->Enabled())
		{
			if (haveitems() && myHero->IsValidTarget(minions, 375))
			{
				if (Tiamat->IsOwned() && Tiamat->IsReady())
				{
					Tiamat->CastOnPlayer();
					GOrbwalking->ResetAA();
					return;
				}

				if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
				{
					Ravenous_Hydra->CastOnPlayer();
					GOrbwalking->ResetAA();
				}
			}
		}
		if (W->IsReady() && JungleW)
		{
			if (myHero->HealthPercent() < 2 && myHero->IsValidTarget(minions, W->Range()))
			{
				W->CastOnPlayer();
				return;
			}
			if (myHero->IsValidTarget(minions, W->Range()))
			{
				W->CastOnPlayer();
				return;
			}
		}
		if (E->IsReady() && JungleE->Enabled())
		{
			if (minions != nullptr && myHero->IsValidTarget(minions, E->Range()))
			{
				E->CastOnUnit(minions);
				return;
			}
		}
	}
}
