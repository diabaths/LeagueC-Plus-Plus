// D-Dias.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"


#include "PluginSDK.h"
#include "Spells.h"
#include  "Menu.h"
#include "Render.h"
#include "Laneclear.h"
#include "JungleClear.h"
#include "Smite.h"
#include "RunForest.h"
#include "OnCreate_OnDelete.h"
#include "Combo.h"
#include "OnProcessCast.h"
#include "Harass.h"
#include "PermaActive.h"
#include "OnCast.h"


PluginSetup("D-Ekko++");

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


PLUGIN_EVENT(void) OnGameUpdate()
{	
	//if (Recallback->Enabled())
	//{
	//recallinlane();
	//}
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
	if (GetAsyncKeyState(FleeKey->GetInteger()))
	{
		runforest();
	}
	if (smitejungle->Enabled())
	{
		Smiteuse();
	}	
	if (Qin2stucks->Enabled())
	{
		Qtoprocpassive();
	}
	killsteal();
	UseItems();
	Usepotion();
	smitestatus();
	
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);
	Menu();
	LoadSpells();
	myHero = GEntityList->Player();

	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
	GEventManager->AddEventHandler(kEventOnSpellCast, OnProcessCast);
	GEventManager->AddEventHandler(kEventOnDoCast, OnCast);
	GEventManager->AddEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->AddEventHandler(kEventOnDestroyObject, OnDestroyObject);
	
	if (strcmp(GEntityList->Player()->ChampionName(), "Ekko") == 0)
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "D-Ekko : Loaded!");
	}
	else
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "You are not playing Ekko...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessCast);
	GEventManager->RemoveEventHandler(kEventOnDoCast, OnCast);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, OnDestroyObject);
	
}