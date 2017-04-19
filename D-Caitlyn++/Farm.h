#pragma once
#include "Extension.h"

inline void laneclear()
{
	for (auto minions : GEntityList->GetAllMinions(false, true, false))
	{
		if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
			return;
		if (Q->IsReady() && !minions->IsWard())
		{
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range())) //&& !minions->IsWard())
			{
				Vec3 pos;
				int Qhit;
				GPrediction->FindBestCastPosition(Q->Range(), Q->Radius(), false, true, false, pos, Qhit);
				if (FarmQ->Enabled() && Qhit >= minminions->GetInteger())
				{
					Q->CastOnPosition(pos);
					return;
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