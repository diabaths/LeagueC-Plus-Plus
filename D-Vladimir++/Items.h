#pragma once
#include "Extension.h"

inline void UseItems()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (Blade_Cutlass->Enabled() && myHero->IsValidTarget(enemy, 550))
			{
				if (myHero->HealthPercent() < MyHpPreBlade->GetInteger() || enemy->HealthPercent() < EnemyHpPreBlade->GetInteger())
				{
					if (Hextech->IsOwned() && Hextech->IsReady())
						Hextech->CastOnTarget(enemy);
					if (Cutlass->IsOwned() && Cutlass->IsReady())
						Cutlass->CastOnTarget(enemy);
				}
			}

		}
	}
}
inline void ProtoBelt()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (UseProto->Enabled() && myHero->IsValidTarget(enemy, 600))
			{
				if (protobelt->IsOwned() && protobelt->IsReady())
					protobelt->CastOnPosition(enemy->GetPosition());
			}
		}

	}
}
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