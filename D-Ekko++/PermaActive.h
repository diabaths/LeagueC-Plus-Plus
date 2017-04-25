#pragma once
#include "Extension.h"


inline void killsteal()
{
	if (GGame->IsChatOpen()) return;
	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
		if (Enemy != nullptr && !Enemy->IsDead())
		{
			if (KillstealQ->Enabled())
			{
				auto dmgQ = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotQ);
				if (myHero->IsValidTarget(Enemy, Q->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmgQ && Q->IsReady())
					{
						Q->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}

			if (KillstealE->Enabled() && E->IsReady())
			{
				auto dmgE = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotE);
				if (myHero->IsValidTarget(Enemy, E->Range() + 475) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmgE)
					{
						E->CastOnPosition(Enemy->GetPosition());
					}
				}
			}
			if (KillstealR->Enabled() && R->IsReady())
			{

				auto dmgR = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotR);
				if (Rpos != nullptr)
				{
					if (Enemy->IsValidTarget(Rpos, R->Range()) && !Enemy->IsInvulnerable())
					{
						if (Enemy->GetHealth() <= dmgR)
						{
							if (GetDistance(Rpos, Enemy) <= R->Range())
							{
								R->CastOnPlayer();
							}
						}
					}
				}
			}
		}
	}
}
inline void Qtoprocpassive()
{
	if (Q->IsReady())
	{
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range() + Q->Radius());
		if (Enemy != nullptr && myHero->IsValidTarget(Enemy, Q->Range() + Q->Radius()))
		{
			if (HittoPassive(Enemy))
			{
				Q->CastOnTarget(Enemy, kHitChanceHigh);
			}
		}
	}
}
inline void recallinlane()
{
	if (R->IsReady())
	{
		auto end = GBuffData->GetEndTime(myHero->GetBuffDataByName("Recall"));
		auto start = GBuffData->GetStartTime(myHero->GetBuffDataByName("Recall"));
		if (end)
		{
			lastrecall = GGame->CurrentTick();
			GGame->PrintChat("STAGTE_1");
		}
		if (GUtility->IsPositionInFountain(myHero->GetPosition()) && GGame->CurrentTick() - lastrecall >3900)
		{
			R->CastOnPlayer();
			GGame->PrintChat("STAGTE_2");
		}
	}
}