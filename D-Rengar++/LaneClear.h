#pragma once

#include "Extension.h"
#include "Items.h"

inline void laneclear()
{
	for (auto minions : GEntityList->GetAllMinions(false, true, false))
	{
		if (Q->IsReady() && FarmQ->Enabled())
		{
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
			if (myHero->IsValidTarget(minions, Q->Range()))
			{
				if (dmg >= minions->GetHealth())
				{
					Q->CastOnUnit(minions);

				}
				else Q->AttackMinions(4);
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
				}

				if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
				{
					Ravenous_Hydra->CastOnPlayer();
					GOrbwalking->ResetAA();
				}
			}
		}
		if (W->IsReady() && FarmW)
		{
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotW);
			if (myHero->IsValidTarget(minions, W->Range()))
			{
				if (myHero->HealthPercent() < 2 && myHero->IsValidTarget(minions, W->Range()))
				{
					W->CastOnPlayer();
				}
				if (CountminionInRange(W->Range()) >= minminionsW->GetInteger())
				{
					W->CastOnPlayer();
				}
				if (dmg >= minions->GetHealth())
				{
					W->CastOnPlayer();
				}
			}
		}
		if (E->IsReady() && FarmE->Enabled())
		{
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotE);
			if (minions != nullptr && myHero->IsValidTarget(minions, E->Range()))
			{

				if (minions->GetHealth() < dmg)
				{
					E->CastOnUnit(minions);
				}
				else  E->CastOnUnit(minions);
			}
		}
	}
}
