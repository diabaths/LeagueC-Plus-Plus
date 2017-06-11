#pragma once
#include "Menu.h"
#include <string>


inline bool use_Youmuu()
{
	if (Youmuu->IsReady() && Youmuu->IsOwned()&& useYoumuu->Enabled())
	{
		return true;
	}
	return false;
}
inline  void _Youmuu(IUnit* target)
{		
		if (myHero->IsValidTarget(target, 550))
		{
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
			Tiamat->CastOnPlayer();
			GOrbwalking->ResetAA();
			return;
		}
	}
	if (RHydra->Enabled() && myHero->IsValidTarget(target, 385))
	{
		if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
		{
			Ravenous_Hydra->CastOnPlayer();
			GOrbwalking->ResetAA();
		}
	}
}
inline bool haveitems()
{
	if (Tiamat->IsOwned() && Tiamat->IsReady() ||
		Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady() || Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
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
		Tiamat->CastOnPlayer();
		return;
	}
	if (Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady() && Hydra->Enabled() && myHero->IsValidTarget(target, 385))
	{
		Titanic_Hydra->CastOnPlayer();
		return;
	}
	if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady() && RHydra->Enabled() && myHero->IsValidTarget(target, 385))
	{
		Ravenous_Hydra->CastOnPlayer();
	}
}

std::function<void()> Item_Delay = [&]() -> void {
	if (menuquicksilver->Enabled() && Quicksilver->IsOwned() && Quicksilver->IsReady())
	{
		Quicksilver->CastOnPlayer();
		return;
	}
	if (menumercurial->Enabled() && Mercurial->IsOwned() && Mercurial->IsReady())
	{
		Mercurial->CastOnPlayer();
		return;
	}
};

PLUGIN_EVENT(void) OnBuffAdd(IUnit* Source)
{
	if (Source->GetNetworkId() == myHero->GetNetworkId() && (Source->HasBuffOfType(BUFF_Charm)
		|| Source->HasBuffOfType(BUFF_Fear) || Source->HasBuffOfType(BUFF_Snare)
		|| Source->HasBuffOfType(BUFF_Stun) || Source->HasBuffOfType(BUFF_Taunt)))
	{
		{
			GPluginSDK->DelayFunctionCall(300, []()
			{
				if (W->IsReady() && AutoW->Enabled() && myHero->GetMana() == 4)
				{
					W->CastOnPlayer();
				}
				if (!W->IsReady() || myHero->GetMana() != 4 || !AutoW->Enabled())
				{
					if (menumercurial->Enabled() && Mercurial->IsOwned() && Mercurial->IsReady())
					{
						Mercurial->CastOnPlayer();
						return;
					}
					if (menuquicksilver->Enabled() && Quicksilver->IsOwned() && Quicksilver->IsReady())
					{
						Quicksilver->CastOnPlayer();
						return;
					}
				}
			});
		}
	}
}
