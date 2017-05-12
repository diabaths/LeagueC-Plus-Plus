#pragma once
#include "Extensions.h"

inline void Usepotion()
{
	if (usepotion->Enabled() && !myHero->IsRecalling() && !myHero->IsDead())
	{
		if (CountEnemiesInRange(2000) > 0)
		{
			bool usepotions = myHero->GetHealth() < myHero->GetMaxHealth()* usepotionhpper->GetInteger() / 100;
			if (usepotions)
			{
				if (myHero->GetBuffDataByName("ItemDarkCrystalFlask") || myHero->GetBuffDataByName("ItemMiniRegenPotion")
					|| myHero->GetBuffDataByName("ItemCrystalFlask") || myHero->GetBuffDataByName("RegenerationPotion") || myHero->HasBuff("ItemCrystalFlaskJungle"))
					return;

				if (Biscuit->IsOwned() && !GUtility->IsPositionInFountain(myHero->GetPosition()) && Biscuit->IsReady())
				{
					Biscuit->CastOnPlayer();
				}
				else if (HealthPot->IsOwned() && !GUtility->IsPositionInFountain(myHero->GetPosition()) && HealthPot->IsReady())
				{
					HealthPot->CastOnPlayer();
				}
				else if (CorruptPot->IsOwned() && CorruptPot->IsReady())
				{
					CorruptPot->CastOnPlayer();
				}
				else if (RefillPot->IsOwned() && RefillPot->IsReady())
				{
					RefillPot->CastOnPlayer();
				}
				else if (hunter->IsOwned() && hunter->IsReady())
				{
					hunter->CastOnPlayer();
				}
			}
		}
	}
}

inline void UseItems()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (enemy != nullptr)
			{
				if (Blade_Cutlass->Enabled() && myHero->IsValidTarget(enemy, 550))
				{
					if (myHero->HealthPercent() < MyHpPreBlade->GetInteger() || enemy->HealthPercent() < EnemyHpPreBlade->GetInteger())
					{
						if (blade->IsOwned() && blade->IsReady())
							blade->CastOnTarget(enemy);
						if (Cutlass->IsOwned() && Cutlass->IsReady())
							Cutlass->CastOnTarget(enemy);
					}
				}
				if (useYoumuu->Enabled() && Youmuu->IsReady() && Youmuu->IsOwned())
				{
					if (myHero->IsValidTarget(enemy, 550))
						Youmuu->CastOnPlayer();
				}
			}
		}
	}
}