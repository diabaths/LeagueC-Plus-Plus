#pragma once
#include "Extension.h"

inline void AutoImmobile()
{

	if (Q->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		if (!target->IsWard() && target != nullptr && myHero->IsValidTarget(target, Q->Range()) && !target->IsInvulnerable())
		{
			if (ImmobileQ->Enabled())
			{
				Q->CastOnTarget(target, kHitChanceImmobile);
			}
		}
	}
}

inline void killsteal()
{
	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
		if (Enemy != nullptr && !Enemy->IsDead())
		{
			if (KillstealQ->Enabled() && Q->IsReady() && !Enemy->IsWard())
			{
				auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotQ);
				if (myHero->IsValidTarget(Enemy, Q->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmg )
					{
						Q->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}
			if (KillstealR->Enabled() && R->IsReady())
			{
				auto Rmin = RMin->GetInteger();
				if (myHero->IsValidTarget(Enemy, RRange) && Enemy != nullptr)
				{
					auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotR);
					if (Enemy->GetHealth() <  dmg &&!Enemy->IsInvulnerable() && GetDistance(myHero, Enemy) > Rmin && CountEnemiesInRange(RMinenemies->GetInteger()) == 0)
					{
						R->CastOnUnit(Enemy);
					}
				}
			}
		}
	}
}
