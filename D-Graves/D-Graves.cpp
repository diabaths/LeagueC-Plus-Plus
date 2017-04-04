// D-Graves.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"
#include "Menu.h"
#include "Spells.h"
#include "Farm.h"
#include "Items.h"
#include "Animation.h"
#include "Color.h"
#include "Burst.h"
#include "OnProcessSpellCast.h"
#include "killsteal.h"
#include "Combo.h"
#include "Render.h"
#include "OnCast.h"

PluginSetup("D-Graves");



PLUGIN_EVENT(void) OnAfterAttack(IUnit* source, IUnit* target)
{	
	auto useE = ComboE->Enabled();
	if (source == myHero && target != nullptr && GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{		
		if (useE && !myHero->GetBuffDataByName("GravesBasicAttackAmmo2") && E->IsReady())
		{
			auto t = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (t != nullptr &&  myHero->IsValidTarget(t, Q->Range()))
				E->CastOnPosition(GGame->CursorPosition());
			GOrbwalking->ResetAA();
		}
	}
	if (GetAsyncKeyState(Burst_b->GetInteger()))
	{
		burstAfter(source, target);
	}
}

PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
	if (args.Source->IsEnemy(myHero) && args.Source->IsHero())
	{
		if (GapcloseW->Enabled() && W->IsReady() && !args.IsTargeted)
		{
			auto t = args.Source;
			if (myHero->IsValidTarget(t, W->Range()))
				if (!t->IsMelee())
				{
					W->CastOnTarget(args.Source);
				}
				else W->CastOnPlayer();
		}
	}
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GetAsyncKeyState(Burst_b->GetInteger()))
	{
		burst();
	}
	if (GetAsyncKeyState(SemiR->GetInteger()) && R->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());
		if (target != nullptr && myHero->IsValidTarget(target, R->Range()))
		{
			R->CastOnTarget(target, kHitChanceHigh);
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		Combo();
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		LaneClear();
		JungleClear();
	}
	killsteal();
	UseItems();
	Usepotion();
	if (smitejungle->Enabled())
	{
		Smiteuse();
	}
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);
	Menu();
	LoadSpells();
	myHero = GEntityList->Player();

	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);
	GEventManager->AddEventHandler(kEventOnGapCloser, OnGapcloser);
	GEventManager->AddEventHandler(kEventOnPlayAnimation, OnPlayAnimation);
	//GEventManager->AddEventHandler(kEventOnSpellCast, OnProcessSpellCast);
	GEventManager->AddEventHandler(kEventOnDoCast, OnDoCast);
	
	if (strcmp(GEntityList->Player()->ChampionName(), "Graves") == 0)
	{
		GRender->NotificationEx(Color::Crimson().Get(), 2, true, true, "D-Graves : Loaded!");
	}
	else
	{
		GRender->NotificationEx(Color::Crimson().Get(), 2, true, true, "You are not playing Graves...");
	}	
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);	
	GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapcloser);
	GEventManager->RemoveEventHandler(kEventOnPlayAnimation, OnPlayAnimation);
	//GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessSpellCast);
	GEventManager->RemoveEventHandler(kEventOnDoCast, OnDoCast);
	
}