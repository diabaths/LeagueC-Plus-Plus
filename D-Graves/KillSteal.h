#pragma once
#include "Extensions.h"

inline void killsteal()
{
	if (GGame->IsChatOpen()) return;
	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
		if (Enemy != nullptr && !Enemy->IsDead())
		{
			if (KillstealQ->Enabled())
			{
				auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotQ);
				if (myHero->IsValidTarget(Enemy, Q->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmg && Q->IsReady())
					{
						Q->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}
			if (KillstealW->Enabled())
			{
				auto dmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotW);
				if (myHero->IsValidTarget(Enemy, W->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmg && W->IsReady())
					{
						W->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}
			if (KillstealR->Enabled() && R->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, R->Range()) && !Enemy->IsInvulnerable())
				{
					auto Rlvl = GEntityList->Player()->GetSpellLevel(kSlotR) - 1;
					auto BaseDamage = std::vector<double>({ 200, 320, 440 }).at(Rlvl);
					auto ADMultiplier = 1.07 * GEntityList->Player()->TotalPhysicalDamage();
					auto TotalD = BaseDamage + ADMultiplier;
					if (Enemy->GetHealth() + 70 <= TotalD)
					{
						R->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}
		}
	}
}
