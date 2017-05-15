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


PLUGIN_EVENT(void) OnGameUpdate()
{	
	//if (Recallback->Enabled())
	//{
	//recallinlane();
	//}
	if (GGame->IsChatOpen() || myHero->IsDead() || myHero->IsRecalling()) return;
	for (auto RMisspos : GEntityList->GetAllUnits())
	{
		if (!strcmp(RMisspos->GetObjectName(), "Ekko") && RMisspos->IsVisible())
		{
			Rpos = RMisspos;
		}
	}
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
	CheatRito();	
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