// D-Dias.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"


#include "PluginSDK.h"
#include "Spells.h"
#include  "Menu.h"
#include "Render.h"
#include "Potions.h"
#include "Items.h"
#include "Smite.h"
#include "Combo.h"
#include "OnProcessCast.h"
#include "OnCreate_OnDelete.h"
#include "Laneclear.h"
#include "JungleClear.h"
#include "Harass.h"
#include "Flee.h"


PluginSetup("D-Rengar++");

static void CheatRito()
{
	if (ChangeSkin->Enabled())
	{
		if (myHero->GetSkinId() != SkinChangeid->GetInteger())
		{
			myHero->SetSkinId(SkinChangeid->GetInteger());
		}
	}
	else
	{
		myHero->SetSkinId(myHero->GetSkinId());
	}
}
/*PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
if (args.Source->IsEnemy(myHero) && args.Source->IsHero())
{
if (AutoEGapcloser->Enabled() && E->IsReady() && !args.IsTargeted && myHero->IsValidTarget(args.Source, 250))
{
E->CastOnPosition(args.Source->ServerPosition());
GOrbwalking->ResetAA();
}
}
}*/

void ChangePriority()
{
	if (GetAsyncKeyState(Comboprio->GetInteger()) && !GGame->IsChatOpen() && GGame->Time() > CombokeyDown)
	{
		if (ComboMode == 0)
		{
			ComboMode = 1;
			CombokeyDown = GGame->Time() + 0.250;
		}
		else if (ComboMode == 1)
		{
			ComboMode = 2;
			CombokeyDown = GGame->Time() + 0.250;
		}		
		else
		{
			ComboMode = 0;
			CombokeyDown = GGame->Time() + 0.250;
		}
	}
}
PLUGIN_EVENT(void) OnGameUpdate()
{
	
	if (GGame->IsChatOpen() || myHero->IsDead() || myHero->IsRecalling()) return;

	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		Combo();
	}

	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		Harass();
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		laneclear();
		jungleclear();
	}
	
	if (smitejungle->Enabled())
	{
		Smiteuse();
	}
	
	//killsteal();
	CheatRito();
	Usepotion();
	smitestatus();
	ChangePriority();

}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);
	Menu();
	LoadSpells();
	myHero = GEntityList->Player();

	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
	GEventManager->AddEventHandler(kEventOnBuffAdd, OnBuffAdd);
	GEventManager->AddEventHandler(kEventOnSpellCast, OnProcessCast);
	GEventManager->AddEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->AddEventHandler(kEventOnDestroyObject, OnDestroyObject);
	//GEventManager->AddEventHandler(kEventOnDoCast, OnCast);
	
	if (strcmp(GEntityList->Player()->ChampionName(), "Rengar") == 0)
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "D-Rengar : Loaded!");
	}
	else
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "You are not playing Rengar...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnBuffAdd, OnBuffAdd);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessCast);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, OnDestroyObject);
	//GEventManager->RemoveEventHandler(kEventOnDoCast, OnCast);
	
}