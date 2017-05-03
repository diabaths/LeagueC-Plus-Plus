

//#include "stdafx.h"
#include "PluginSDK.h"
#include "Extension.h"
#include "Spells.h"
#include "Items.h"
#include "LaneClear.h"
#include "Combo.h"
#include "Render.h"
//#include "AfterAttack.h"
#include "OnProcessCast.h"
#include "JungleClear.h"
#include "Harass.h"
#include "OnCast.h"
#include "killsteal.h"
#include "Burst.h"


#define M_PI 3.14159265358979323846

PluginSetup("D-Vladimir++");


PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
	if (args.Source->IsEnemy(myHero) && args.Source->IsHero())
	{
		if (AutoEGapcloser->Enabled() && E->IsReady() && !args.IsTargeted && myHero->IsValidTarget(args.Source, 250))
		{
			E->CastOnPosition(args.Source->ServerPosition());
		}
	}
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GGame->IsChatOpen() || myHero->IsDead() || myHero->IsRecalling()) return;
	
	if (myHero->HasBuff("VladimirE")|| myHero->HasBuff("VladimirSanguinePool"))
	{
		GOrbwalking->SetMovementAllowed(true);
		GOrbwalking->SetAttacksAllowed(false);
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	}
	else GOrbwalking->SetAttacksAllowed(true);

	if (GetAsyncKeyState(Burst->GetInteger()))
	{
		burst();
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
	killsteal();
	Usepotion();
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
		
	if (strcmp(GEntityList->Player()->ChampionName(), "Vladimir") == 0)
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "D-Vladimir : Loaded!");
	}
	else
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "You are not playing Vladimir...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessCast);
	GEventManager->RemoveEventHandler(kEventOnDoCast, OnCast);

}