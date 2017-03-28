#pragma once
#include "Spells.h"

inline void killsteal()
{
	if (GGame->IsChatOpen()) return;
	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
		if (Enemy != nullptr && !Enemy->IsDead())
		{
			if (KillstealW->Enabled() && W->IsReady())
			{
				auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotW);
				if (myHero->IsValidTarget(Enemy, Wrange) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmg && W->IsReady())
					{
						W->CastOnPlayer();
					}
				}
			}
			if (KillstealR->Enabled() && R2->IsReady() && myHero->HasBuff("RivenFengShuiEngine"))
			{
				auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotR);
				if (E->IsReady() && KillstealE->Enabled())
				{
					if (EnemiesInRange(myHero, R2->Range() + E->Range()) < 3 &&
						myHero->HealthPercent() > 50 && myHero->IsValidTarget(Enemy, R->Range() + E->Range() - 100)
						&& GetDistance(myHero, Enemy) >= R2->Range() && Enemy->GetHealth() <= dmg)
					{
						E->CastOnPosition(Enemy->ServerPosition());
						if (myHero->IsValidTarget(Enemy, R2->Range()))
						{
							R2->CastOnUnit(Enemy);
						}
					}
				}
				else
				{
					if (myHero->IsValidTarget(Enemy, R2->Range()) && Enemy->GetHealth() <= dmg)
					{
						R2->CastOnUnit(Enemy);
					}
				}
			}
		}
	}
}
