#pragma once
#include "PluginSDK.h"
#include "Menu.h"
#include "Extensions.h"

inline bool use_Youmuu()
{
	if(Youmuu->IsReady() && Youmuu->IsOwned())
	{
		return true;
	}
	return false;
}
inline  void _Youmuu(IUnit* target)
{
	if (useYoumuu->Enabled())
	{
		if (myHero->IsValidTarget(target, 550))
			Youmuu->CastOnPlayer();
	}
}

inline void Titanic(IUnit* target)
{
	if (Hydra->Enabled() && myHero->IsValidTarget(target, 385))
	{
		if (Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady())
		{
			Titanic_Hydra->CastOnTarget(target);
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
			Tiamat->CastOnTarget(target);
			GOrbwalking->ResetAA();
			return;
		}
	}	
	if (RHydra->Enabled() && myHero->IsValidTarget(target, 385))
	{
		if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
		{
			Ravenous_Hydra->CastOnTarget(target);
			GOrbwalking->ResetAA();
		}
	}
}
inline bool haveitems()
{
	if (Tiamat->IsOwned() && Tiamat->IsReady() || 
		Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady() ||Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
	{
		return true;
	}
	return false;
}

inline void UseItems(IUnit* target)
{
	/*if (Blade_Cutlass->Enabled() && myHero->IsValidTarget(target, 550))
	{
		if (myHero->HealthPercent() < MyHpPreBlade->GetInteger() || target->HealthPercent() < EnemyHpPreBlade->GetInteger())
		{
			if (blade->IsOwned() && blade->IsReady())
				blade->CastOnTarget(target);
			if (Cutlass->IsOwned() && Cutlass->IsReady())
				Cutlass->CastOnTarget(target);
		}
	}*/
	if (Tiamat->IsOwned() && Tiamat->IsReady() && _tiamat->Enabled() && myHero->IsValidTarget(target, 385))
	{
		Tiamat->CastOnPosition(target->GetPosition());
		GOrbwalking->ResetAA();
		return;
	}
	if (Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady() && Hydra->Enabled() && myHero->IsValidTarget(target, 385))
	{
		Titanic_Hydra->CastOnPosition(target->GetPosition());
		GOrbwalking->ResetAA();
		return;
	}
	if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady() && RHydra->Enabled() && myHero->IsValidTarget(target, 385))
	{
		Ravenous_Hydra->CastOnPosition(target->GetPosition());
		GOrbwalking->ResetAA();
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
