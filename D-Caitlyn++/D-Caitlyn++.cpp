// D-Caitlyn.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"
#include "Extension.h"
#include "Spells.h"
#include "Items.h"
#include "Farm.h"
#include "Combo.h"
#include "Harass.h"
#include "Auto-Killsteal.h"
#include "Render.h"
#include "AfterAttack.h"
#include "OnProcessSpellCast.h"
#include "OnAnimation.h"
#include "EWQ.h"

#define M_PI 3.14159265358979323846

PluginSetup("D-Caitlyn++");

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

PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
	if (args.Source->IsEnemy(myHero) && args.Source->IsHero())
	{
		if (AutoEGapcloser->Enabled() && E->IsReady() && !args.IsTargeted && myHero->IsValidTarget(args.Source, 250))
		{
			E->CastOnPosition(args.Source->ServerPosition());
			GOrbwalking->ResetAA();
		}
	}
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GGame->IsChatOpen()) return;
	if (myHero->GetSpellBook()->GetLevel(kSlotR) > 0)
	{
		RRange = 1500 + 500 * GEntityList->Player()->GetSpellLevel(kSlotR);
	}
	if (W->IsReady() && GGame->TickCount() - LastWTick > 1500)
	{
		if ( myHero->GetMana() > Q->ManaCost() + E->ManaCost())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			if (target != nullptr && myHero->IsValidTarget(target, W->Range()) && !target->HasBuff("caitlynyordletrapinternal"))
			{
				if (!EWQCombo->GetInteger() && AutoW->Enabled() && !target->IsDead() && target->HasBuffOfType(BUFF_Stun) || target->HasBuffOfType(BUFF_Snare) || target->HasBuffOfType(BUFF_Knockup)
					|| target->HasBuffOfType(BUFF_Suppression) /*target->IsCastingImportantSpell()*/)
				{
					W->CastOnPosition(target->ServerPosition());
				}
				if (AutoWtele->Enabled() && target->HasBuff("teleport_target"))
				{
					W->CastOnPosition(target->ServerPosition());
				}
				if (AutoWmelee->Enabled() && target->IsMelee() && GetDistance(myHero, target) < target->GetRealAutoAttackRange(myHero))
				{
					W->CastOnPosition(myHero->ServerPosition());
				}
			}
		}
	}
	if(GetAsyncKeyState(EWQCombo->GetInteger()))
	{
		burst();
	}
	if (GUtility->IsKeyDown(USEE->GetInteger()))
	{
		auto position = myHero->ServerPosition() - (GGame->CursorPosition() - myHero->ServerPosition());
		E->CastOnPosition(position);
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
	UseItems();
	Usepotion();
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
	GEventManager->AddEventHandler(kEventOnPlayAnimation, OnPlayAnimation);
	GEventManager->AddEventHandler(kEventOnSpellCast, OnProcessSpellCast);
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);
	
	if (strcmp(GEntityList->Player()->ChampionName(), "Caitlyn") == 0)
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "D-Caitlyn : Loaded!");
	}
	else
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "You are not playing Caitlyn...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnPlayAnimation, OnPlayAnimation);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessSpellCast);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);
}