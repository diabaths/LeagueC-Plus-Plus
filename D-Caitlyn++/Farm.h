#pragma once
#include "Extension.h"
#include "malachite_Extension.h"

inline void laneclear()
{
	for (auto minions : GEntityList->GetAllMinions(false, true, false))
	{
		if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
			return;
		if (Q->IsReady() && !minions->IsWard())
		{
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
			{	//credits malachite
				auto pred = FindBestLineCastPosition(vector<Vec3>{ myHero->GetPosition() }, Q->Range(), Q->Range(), 60, true, false);
				if (pred.HitCount >= minminions->GetInteger() && pred.CastOnUnit != nullptr)
				{
					Q->CastOnUnit(pred.CastOnUnit);
				}

				if (LastHitQ->Enabled() && minions->GetHealth() < dmg && GetDistance(myHero, minions) > myHero->AttackRange())
				{
					Q->CastOnUnit(minions);
					return;
				}
			}
		}
	}
}

inline void jungleclear()
{
	for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
	{
		if (myHero->ManaPercent() < JungleManaPercent->GetInteger())
			return;
		if (strstr(jMinion->GetObjectName(), "mini")) return;
		if (JungleQ->Enabled() && Q->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
			{
				Q->CastOnUnit(jMinion);
			}
		}
		if (JungleE->Enabled() && E->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, E->Range()))
			{
				E->CastOnTarget(jMinion);
			}
		}
	}
}