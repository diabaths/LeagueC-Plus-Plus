// D-Riven.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"

#include "Menu.h"
#include "Spells.h"
#include "Items.h"
#include "Combo.h"
#include "OnCast.h"
#include "OnAnimation.h"
#include "OnAttack.h"
#include "OnProcessSpellCast.h"
#include "Burst.h"
#include "Flee.h"
#include "Render.h"
#include "Harass.h"
#include "Laneclear.h"
#include "killsteal.h"
#include "Color.h"

PluginSetup("D-Riven++")

PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
	if (args.Sender->IsEnemy(myHero) && args.Sender->IsHero())
	{
		if (WGapcloser->Enabled() && W->IsReady() && !args.IsTargeted && myHero->IsValidTarget(args.Sender, 250))
		{
			W->CastOnPlayer();
		}
	}
}

PLUGIN_EVENT(void) OnInterruptable(InterruptibleSpell const& Args)
{
	if (InterruptE->Enabled() && W->IsReady() && myHero->IsValidTarget(Args.Target, 250))
	{
		W->CastOnPlayer();
	}
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GGame->IsChatOpen()) return;
	
	if (myHero->HasBuff("RivenFengShuiEngine"))
	{
		Wrange = 350;
	} 
	else Wrange = 300;

	if (GOrbwalking->GetOrbwalkingMode() != kModeCombo && GOrbwalking->GetOrbwalkingMode() != kModeMixed && GOrbwalking->GetOrbwalkingMode() != kModeLaneClear)
	{
		auto end = GBuffData->GetEndTime(myHero->GetBuffDataByName("RivenTriCleave"));
		auto start = GBuffData->GetStartTime(myHero->GetBuffDataByName("RivenTriCleave"));
		if (end - GGame->Time() <= 0.1 * (end - start) && KeepQ->Enabled() && !myHero->IsRecalling() && myHero->HasBuff("RivenTriCleave"))
		{
			Q->CastOnPosition(GGame->CursorPosition());
			LastQ = GGame->CurrentTick();
		}
	}
	if (GetAsyncKeyState(Burst_b->GetInteger()))
	{
		Burst();
	}
	if (GetAsyncKeyState(Flee_b->GetInteger()))
	{
		Flee();
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
	GEventManager->AddEventHandler(kEventOnPlayAnimation, OnPlayAnimation);
	GEventManager->AddEventHandler(kEventOrbwalkOnAttack, OnAttack);
	GEventManager->AddEventHandler(kEventOnDoCast, OnDoCast);
	GEventManager->AddEventHandler(kEventOnSpellCast, OnProcessSpellCast);
	GEventManager->AddEventHandler(kEventOnInterruptible, OnInterruptable);
	GEventManager->AddEventHandler(kEventOnGapCloser, OnGapcloser);

	if (strcmp(GEntityList->Player()->ChampionName(), "Riven") == 0)
	{
		GRender->NotificationEx(Color::Crimson().Get(), 2, true, true, "D-Riven++ Loaded!");
	}
	else
	{
		GRender->NotificationEx(Color::Crimson().Get(), 2, true, true, "You are not playing Riven...");
	}
}

PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnPlayAnimation, OnPlayAnimation);
	GEventManager->RemoveEventHandler(kEventOrbwalkOnAttack, OnAttack);
	GEventManager->RemoveEventHandler(kEventOnDoCast, OnDoCast);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessSpellCast);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, OnInterruptable);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapcloser);
}