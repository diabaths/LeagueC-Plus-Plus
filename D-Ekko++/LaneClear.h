#pragma once

#include "Extension.h"


inline void laneclear()
{
		for (auto minions : GEntityList->GetAllMinions(false, true, false))
		{
			if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
				return;
			if (Q->IsReady())
			{
				auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
				if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
				{

					Q->AttackMinions(3);
					return;
				}
				if (FarmQ->Enabled() && minions->GetHealth() < dmg && !myHero->GetRealAutoAttackRange(minions))
				{
					Q->CastOnUnit(minions);
					return;
				}
			}

			if (E->IsReady())
			{
				auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotE);
				if (minions != nullptr && myHero->IsValidTarget(minions, E->Range()))
				{

					if (FarmE->Enabled() && minions->GetHealth() < dmg)
					{
						E->CastOnPosition(minions->GetPosition());
						GGame->IssueOrder(myHero, kAttackUnit, GGame->CursorPosition());
						return;
					}
				}
			}
		}
	}
