#pragma once
#include "Extension.h"

PLUGIN_EVENT(void) OnCreateObject(IUnit* obj)
{
	/*auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1500);
	if (useYoumuu->Enabled())
	{
		if (UltiOn() && use_Youmuu())
		{
			GPluginSDK->DelayFunctionCall(300, []()
			{
				Youmuu->CastOnPlayer();
			});
		}
	}
	if (Enemy != nullptr && !Enemy->IsDead())
	{
		if (myHero->GetMana() != 4)
		{
			if (E->IsReady() && ComboE->Enabled() && !passiveup)
			{
				if (myHero->IsValidTarget(Enemy, E->Range()))
				{
					E->CastOnTarget(Enemy, kHitChanceHigh);
				}
			}
			if (strcmp(obj->GetObjectName(), "missile") == 0)
			{
			
				if (haveitems() && myHero->IsValidTarget(Enemy, E->Range()))
				{
					if (_tiamat->Enabled())
					{
						if (Tiamat->IsOwned() && Tiamat->IsReady())
						{
							Tiamat->CastOnPlayer();
							GOrbwalking->ResetAA();
							return;
						}
					}
					if (RHydra->Enabled())
					{
						if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
						{
							Ravenous_Hydra->CastOnPlayer();
							GOrbwalking->ResetAA();
						}
					}
				}
			}

			if (Contains(obj->GetObjectName(), "TiamatMelle_itm_active"))
					
			{
				if (W->IsReady() && ComboW->Enabled() && myHero->IsValidTarget(Enemy, W->Range()))
				{
					W->CastOnPlayer();
				}
			}
			if (Contains(obj->GetObjectName(), "Rengar_Base_W_Roar"))
				//E spell
			{
				if (Q->IsReady() && ComboQ->Enabled() && myHero->IsValidTarget(Enemy, Q->Range()))
				{
					Q->CastOnTarget(Enemy, kHitChanceMedium);
				}
			}
		}
		if (myHero->GetMana() == 4)
		{

		}
	}*/
	if (obj != nullptr)
	{
		/*if (strcmp(obj->GetObjectName(), "Rengar_Base_P_Buf.troy") == 0)
		{
			passivedown = false;
			GGame->PrintChat("passive");
		}
		if (strcmp(obj->GetObjectName(), "GlobalCamouflagePersistant.troy") == 0)
		{
			passivedown = false;
		}*/
		if (strcmp(obj->GetObjectName(), "Rengar_Base_P_Buf_Enhanced_Ring.troy") == 0)
		{
			passiveup = true;
		}
	}
}
PLUGIN_EVENT(void) OnDestroyObject(IUnit* obj)
{
	if (obj != nullptr)
	{
		/*if (strcmp(obj->GetObjectName(), "Rengar_Base_P_Buf.troy") == 0)
		{
			passivedown = true;
			GGame->PrintChat("passive");
		}
		if (strcmp(obj->GetObjectName(), "GlobalCamouflagePersistant.troy") == 0)
		{
			passivedown = true;
		}*/
		if (strcmp(obj->GetObjectName(), "Rengar_Base_P_Buf_Enhanced_Ring.troy") == 0)
		{
			passiveup = false;
		}
	}
}