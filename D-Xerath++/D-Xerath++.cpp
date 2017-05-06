

#include "PluginSDK.h"
#include "Spells.h"
#include  "Menu.h"
#include "Render.h"
#include "Potions.h"
#include "Combo.h"
#include "OnCreate_OnDelete.h"



PluginSetup("D-Xerath++");

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


PLUGIN_EVENT(void) OnGameUpdate()
{

	if (GGame->IsChatOpen() || myHero->IsDead() || myHero->IsRecalling()) return;
	if (myHero->GetSpellLevel(kSlotR) > 0)
	{
		float range = 2000 + myHero->GetSpellLevel(kSlotR) * 1200;
		R->SetOverrideRange(range);
	}
	if (Q->IsCharging() || UltiIsUp)
	{
		GOrbwalking->SetAttacksAllowed(false);
	}
	else GOrbwalking->SetAttacksAllowed(true);
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		Combo();
	}

	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		//Harass();
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		//laneclear();
		//jungleclear();
	}
	
	//killsteal();
	CheatRito();
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
	//GEventManager->AddEventHandler(kEventOnBuffAdd, OnBuffAdd);
	//GEventManager->AddEventHandler(kEventOnSpellCast, OnProcessCast);
	GEventManager->AddEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->AddEventHandler(kEventOnDestroyObject, OnDestroyObject);
	//GEventManager->AddEventHandler(kEventOnDoCast, OnCast);

	if (strcmp(GEntityList->Player()->ChampionName(), "Xerath") == 0)
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "D-Xerath : Loaded!");
	}
	else
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "You are not playing Xerath...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	//GEventManager->RemoveEventHandler(kEventOnBuffAdd, OnBuffAdd);
	//GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessCast);
	GEventManager->RemoveEventHandler(kEventOnCreateObject, OnCreateObject);
	GEventManager->RemoveEventHandler(kEventOnDestroyObject, OnDestroyObject);
	//GEventManager->RemoveEventHandler(kEventOnDoCast, OnCast);

}