#pragma once
#include "Extension.h"

inline void Harass()
{
	if (myHero->ManaPercent() < HarassManaPercent->GetInteger())
		return;
	if (HarassQ->Enabled())
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (myHero->IsValidTarget(target, Q->Range()) && target != nullptr && !target->IsWard())
			{
				AdvPredictionOutput prediction_output;
				Q->RunPrediction(target, true, kCollidesWithYasuoWall, &prediction_output);
				if (prediction_output.HitChance >= kHitChanceHigh && CountEnemiesInRange(400) == 0)
				{
					if (!myHero->GetRealAutoAttackRange(target) && (target->HasBuffOfType(BUFF_Stun) || target->HasBuffOfType(BUFF_Slow)))
					{
						Q->CastOnTarget(target);
					}
				}
				if (CountEnemiesInRange(400) == 0)
				{
					Q->CastOnTargetAoE(target, 2, kHitChanceHigh);
				}
			}
		}
	}
}