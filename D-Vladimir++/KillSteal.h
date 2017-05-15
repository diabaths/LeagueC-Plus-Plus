#pragma once
#include "Extension.h"


inline void killsteal()
{
	if (GGame->IsChatOpen()) return;
	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
		if (Enemy != nullptr && !Enemy->IsDead())
		{
			if (KillstealQ->Enabled() && Q->IsReady())
			{
				auto dmgQ = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotQ);
				if (myHero->IsValidTarget(Enemy, Q->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmgQ)
					{
						Q->CastOnUnit(Enemy);
						return;
					}
				}
			}

			if (KillstealE->Enabled() && E->IsReady())
			{
				auto dmgE = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotE);
				if (myHero->IsValidTarget(Enemy, E->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmgE)
					{
						E->CastOnPlayer();
						return;
					}
				}
			}

			if (KillstealR->Enabled() && R->IsReady())
			{
				AdvPredictionOutput RPred;
				R->RunPrediction(Enemy, true, kCollidesWithNothing, &RPred);
				if (myHero->IsValidTarget(Enemy, R->Range()) && !Enemy->IsInvulnerable())
				{
					if (RPred.HitChance >= kHitChanceHigh)
					{
						if (Enemy->GetHealth() < RDamage(Enemy))
						{
							R->CastOnPosition(RPred.CastPosition);
							return;
						}
					}
				}
			}
		}
	}
}