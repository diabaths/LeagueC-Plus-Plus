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
#include "OnProcessSpellCast.h"
#include "Burst.h"
#include "Flee.h"
#include "Render.h"
#include "Harass.h"
#include "Laneclear.h"
#include "killsteal.h"
#include "Color.h"
#include "AfterAttack.h"
#include "JungleClear.h"
#include "OnCreate_OnDelete.h"

PluginSetup("D-Riven++")

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

void ChangePriority()
{
	if (GetAsyncKeyState(BurstModeChange->GetInteger()) && !GGame->IsChatOpen() && GGame->Time() > keyDown)
	{
		if (BurstMode == 0)
		{
			BurstMode = 1;
			keyDown = GGame->Time() + 0.250;
		}
		else if (BurstMode == 1)
		{
			BurstMode = 2;
			keyDown = GGame->Time() + 0.250;
		}
		else if (BurstMode == 2)
		{
			BurstMode = 3;
			keyDown = GGame->Time() + 0.250;
		}
		else
		{
			BurstMode = 0;
			keyDown = GGame->Time() + 0.250;
		}
	}
}
PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
	if (args.Source->IsEnemy(myHero) && args.Source->IsHero())
	{
		if (WGapcloser->Enabled() && W->IsReady() && !args.IsTargeted && myHero->IsValidTarget(args.Source, 250))
		{
			W->CastOnPlayer();
		}
	}
}

PLUGIN_EVENT(void) OnInterruptable(InterruptibleSpell const& Args)
{
	if (InterruptE->Enabled() && W->IsReady() && myHero->IsValidTarget(Args.Source, 250))
	{
		W->CastOnPlayer();
	}
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (myHero->IsDead())
	{
		Qstack = 0;
		return;
	}
	if (Qstack != 0 && GGame->TickCount() - LastQ > 3800)
	{
		Qstack = 0;
	}
	if (AutoSetDelay->Enabled())
	{
		auto delay = 0;

		if (GGame->Latency() <= 20)
		{
			delay = GGame->Latency();
		}
		else if (GGame->Latency() <= 50)
		{
			delay = GGame->Latency() / 2 + 5;
		}
		else
		{
			delay = GGame->Latency() / 2 - 5;
		}

		if (delay >= 70)
		{
			delay = 70;
		}
		Q1Delay = QDelay1->GetInteger() - GGame->Latency();
		Q2Delay = QDelay2->GetInteger() - GGame->Latency();
		Q3Delay = QDelay3->GetInteger() - GGame->Latency();
		//DelayAA = 170 - GGame->Latency();
	}
	if (!AutoSetDelay->Enabled())
	{
		Q1Delay = QDelay1->GetInteger();
		Q2Delay = QDelay2->GetInteger();
		Q3Delay = QDelay3->GetInteger();
		//DelayAA = AADelay->GetInteger();
	}

	if (isR2())
	{
		W->SetOverrideRange(330);
	} 
	else W->SetOverrideRange(265); 
	
	CheatRito();
	if (GOrbwalking->GetOrbwalkingMode() != kModeCombo && GOrbwalking->GetOrbwalkingMode() != kModeMixed && GOrbwalking->GetOrbwalkingMode() != kModeLaneClear)
	{
		auto end = GBuffData->GetEndTime(myHero->GetBuffDataByName("RivenTriCleave"));
		auto start = GBuffData->GetStartTime(myHero->GetBuffDataByName("RivenTriCleave"));
		if (KeepQ->Enabled() && GEntityList->Player()->HasBuff("RivenTriCleave") && 
			end - GGame->Time() <= 0.1 * (end - start) && !myHero->IsRecalling())
		{
			auto qPosition = GEntityList->Player()->ServerPosition() + GEntityList->Player()->Direction() * (Q->Range() + 100);

			if (CountEnemiesInPositionRange(qPosition, 200) <= 1 && !GUtility->IsPositionUnderTurret(qPosition))
			{
				Q->CastOnPosition(GGame->CursorPosition());
			}
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
	GEventManager->AddEventHandler(kEventOnPlayAnimation, OnPlayAnimation);
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, Afterattack);
	GEventManager->AddEventHandler(kEventOnDoCast, OnDoCast);
	GEventManager->AddEventHandler(kEventOnSpellCast, OnProcessSpellCast);
	GEventManager->AddEventHandler(kEventOnInterruptible, OnInterruptable);
	GEventManager->AddEventHandler(kEventOnGapCloser, OnGapcloser);
	GEventManager->AddEventHandler(kEventOrbwalkOnAttack, OnAttack);
	GEventManager->AddEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->AddEventHandler(kEventOnDestroyObject, OnDestroyObject);
	


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
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, Afterattack);
	GEventManager->RemoveEventHandler(kEventOnDoCast, OnDoCast);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessSpellCast);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, OnInterruptable);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapcloser);
	GEventManager->RemoveEventHandler(kEventOrbwalkOnAttack, OnAttack);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, OnDestroyObject);
}