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
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
			{
				Vec3 pos;
				int Qhit;
				GPrediction->FindBestCastPosition(Q->Range(), Q->Radius(), false, true, false, pos, Qhit);
				if (FarmQ->Enabled() && Qhit >= minminions->GetInteger())
				{
					Q->CastOnPosition(pos);
					return;
				}

				AdvPredictionOutput prediction_output;
				Q->RunPrediction(target, true, kCollidesWithYasuoWall, &prediction_output);
				if (harassFarmQ->Enabled() && Qhit >= 2 && prediction_output.HitChance >= kHitChanceHigh)
				{
					Q->CastOnUnit(target);
					return;
				}
				if (!minions->IsWard() && LastHitQ->Enabled() && minions->GetHealth() < dmg && GetDistance(myHero, minions) > myHero->AttackRange())
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