#pragma once
#include "PluginSDK.h"
#include "Menu.h"
#include "Extensions.h"

inline  void _Youmuu(IUnit* target)
{
	if (useYoumuu->Enabled() && Youmuu->IsReady() && Youmuu->IsOwned())
	{
		if (myHero->IsValidTarget(target, 550))
			Youmuu->CastOnPlayer();
	}
}
inline bool canusetiamate()
{
	if (Tiamat->IsOwned() && Tiamat->IsReady() || Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady() || (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady()))
		return true;
	else return false;
	
}
inline void Titanic(IUnit* target)
{
	if (Hydra->Enabled() && myHero->IsValidTarget(target, 385))
	{
		if (Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady())
		{
			Titanic_Hydra->CastOnPlayer();
			GOrbwalking->ResetAA();
		}
	}
}

inline void Tiamat_hydra(IUnit* target)
{
	if (_tiamat->Enabled() && myHero->IsValidTarget(target, 385))
	{
		if (Tiamat->IsOwned() && Tiamat->IsReady())
		{
			Tiamat->CastOnPlayer();
			GOrbwalking->ResetAA();
		}
	}	
	else if (RHydra->Enabled() && myHero->IsValidTarget(target, 385))
	{
		if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
		{
			Ravenous_Hydra->CastOnPlayer();
			GOrbwalking->ResetAA();
		}
	}
}

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
					if (blade->IsOwned() && blade->IsReady())
						blade->CastOnTarget(enemy);
					if (Cutlass->IsOwned() && Cutlass->IsReady())
						Cutlass->CastOnTarget(enemy);
				}
			}
			if (_tiamat->Enabled() && myHero->IsValidTarget(enemy, 385))
			{
				if (Tiamat->IsOwned() && Tiamat->IsReady())
					Tiamat->CastOnPlayer();
			}
			if (Hydra->Enabled() && myHero->IsValidTarget(enemy, 385))
			{
				if (Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady())
					Titanic_Hydra->CastOnPlayer();
			}
			if (RHydra->Enabled() && myHero->IsValidTarget(enemy, 385))
			{
				if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
					Ravenous_Hydra->CastOnPlayer();
			}
			if (useYoumuu->Enabled() && Youmuu->IsReady() && Youmuu->IsOwned())
			{
				if (myHero->IsValidTarget(enemy, 550))
					Youmuu->CastOnPlayer();
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

				if (Biscuit->IsOwned() && !InFountain(myHero) && Biscuit->IsReady())
				{
					Biscuit->CastOnPlayer();
				}
				else if (HealthPot->IsOwned() && !InFountain(myHero) && HealthPot->IsReady())
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
