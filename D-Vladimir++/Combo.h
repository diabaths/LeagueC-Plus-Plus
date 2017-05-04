#pragma once
#include "Damage.h"
#include "Menu.h"
#include "Items.h"


inline void Combo()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1500);
	if (Enemy != nullptr && !Enemy->IsDead())
	{
		UseItems();
		if (Ignite != nullptr)
		{
			if (UseIgnitecombo->Enabled() && Ignite->IsReady())
			{
				if (Enemy->IsValidTarget(myHero, 570))
				{
					if (Enemy->GetHealth() <= 1.4 * TotalDamage(Enemy))
					{
						Ignite->CastOnUnit(Enemy);
						return;
					}
				}
			}
		}
		ProtoBelt();
		if (ComboQ->Enabled() && Q->IsReady())
		{
			if (myHero->IsValidTarget(Enemy, Q->Range()))
			{
				Q->CastOnUnit(Enemy);
				return;
			}
		}

		if (ComboE->Enabled() && E->IsReady() && myHero->HealthPercent() > UseEHPC->GetInteger())
		{
			if (myHero->HasBuff("VladimirE") && myHero->IsValidTarget(Enemy, E->Range()))
			{
				E->CastOnPlayer();
				return;
			}
			if (!myHero->HasBuff("VladimirE") && myHero->IsValidTarget(Enemy, E->Range() +100) && Enemy->IsFacing(myHero))
			{
				E->StartCharging();
				return;
			}
			if (!myHero->HasBuff("VladimirE") && myHero->IsValidTarget(Enemy, E->Range()))
			{
				E->StartCharging();
				return;
			}
		}
		if (ComboR->Enabled() && R->IsReady())
		{
			if (Enemy->GetHealth() <1.4* TotalDamage(Enemy))
			{
				AdvPredictionOutput RPred;
				R->RunPrediction(Enemy, true, kCollidesWithNothing, &RPred);
				if (myHero->IsValidTarget(Enemy, R->Range()))
				{
					if (RPred.HitChance >= kHitChanceHigh)
					{
						R->CastOnPosition(RPred.CastPosition);
						return;

					}
				}
			}
		}
		if (ComboRAOE  && R->IsReady())
		{
			int heros = 0;
			Vec3 pos = Vec3();
			R->FindBestCastPosition(false, true, pos, heros);
			if (heros >= ComboRAOEUse->GetInteger())
			{
				R->CastOnPosition(pos);
			}			
		}
	}
}