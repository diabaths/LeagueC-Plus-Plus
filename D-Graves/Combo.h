#pragma once
#include "Extensions.h"

inline void Combo()
{
	auto useQ = ComboQ->Enabled();
	auto useW = ComboW->Enabled();
	smitetarget();
	if (useQ)
	{
		if (Q->IsReady())
		{
			auto t = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, QRange->GetInteger());
			if (t != nullptr &&  myHero->IsValidTarget(t, Q->Range()))
				Q->CastOnTarget(t, kHitChanceHigh);
		}
	}
	if (useW && !E->IsReady())
	{
		if (W->IsReady())
		{
			auto t = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			if (t != nullptr &&  myHero->IsValidTarget(t, W->Range()))
				W->CastOnTarget(t, kHitChanceHigh);
		}
	}
	if (ComboR->Enabled() && R->IsReady())
	{
		for (auto Enemy : GEntityList->GetAllHeros(false, true))
		{
			if (Enemy != nullptr && !Enemy->IsDead())
			{
				auto Rlvl = GEntityList->Player()->GetSpellLevel(kSlotR) - 1;
				auto BaseDamage = std::vector<double>({ 200, 320, 440 }).at(Rlvl);
				auto ADMultiplier = 1.1 * GEntityList->Player()->TotalPhysicalDamage();
				auto TotalD = BaseDamage + ADMultiplier;
				if (myHero->IsValidTarget(Enemy, R->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() + 70 <= TotalD)
					{
						R->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}
		}
	}

	if (R->IsReady() && ComboRAOEuse->Enabled())
	{
		for (auto target : GEntityList->GetAllHeros(false, true))
			if (target != nullptr &&  myHero->IsValidTarget(target, R->Range()))
			{
				R->CastOnTargetAoE(target, 3, kHitChanceLow);
			}
	}
}