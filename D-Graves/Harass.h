#pragma once
#include "Extensions.h"

inline void Harass()
{
	if (myHero->ManaPercent() < HarassManaPercent->GetInteger())
		return;
	if (HarassQ->Enabled())
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (target->IsValidTarget(myHero, Q->Range()))
				Q->CastOnTarget(target, kHitChanceHigh);
		}
	}
	if (HarassW->Enabled())
	{
		if (W->IsReady() && !Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			if (target->IsValidTarget(myHero, W->Range()))
				W->CastOnTarget(target, kHitChanceHigh);
		}
	}
}
