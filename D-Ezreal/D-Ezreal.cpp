// D-Ezreal.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"




PluginSetup("D-ezreal");

IMenu* MainMenu;
IMenu* ComboMenu;
IMenu* HarassMenu;
IMenu* FarmMenu;
IMenu* MiscMenu;
IMenu* Drawings;
IMenuOption* ComboQ;
IMenuOption* ComboW;
IMenuOption* ComboR;
IMenuOption* ComboRAOE;
IMenuOption* ComboRAOEuse;
IMenuOption* RRange;
IMenuOption* HarassQ;
IMenuOption* HarassW;
IMenuOption* HarassManaPercent;
IMenuOption* FarmQ;
IMenuOption* FarmManaPercent;
IMenuOption* KillstealQ;
IMenuOption* KillstealW;
IMenuOption* ImmobileQ;
IMenuOption* ImmobileW;
IMenuOption* DrawReady;
IMenuOption* DrawQ;
IMenuOption* DrawW;
IMenuOption* DrawE;
IMenuOption* DrawR;

IUnit* myHero;

ISpell2* Q;
ISpell2* W;
ISpell2* E;
ISpell2* R;

void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Ezreal");

	ComboMenu = MainMenu->AddMenu("Combo Settings");
	ComboQ = ComboMenu->CheckBox("Use Q", true);
	ComboW = ComboMenu->CheckBox("Use W", true);
	ComboR = ComboMenu->CheckBox("Use R if Is killable", true);
	ComboRAOEuse = ComboMenu->CheckBox("Use R if hit x Enemys", false);
	ComboRAOE = ComboMenu->AddInteger("Use R if hit X Enemys", 1, 5, 3);


	HarassMenu = MainMenu->AddMenu("Harass Setting");
	HarassQ = HarassMenu->CheckBox("Use Q", true);
	HarassW = HarassMenu->CheckBox("Use W", true);
	HarassManaPercent = HarassMenu->AddInteger("Mana Percent for harass", 10, 100, 70);
	Drawings = MainMenu->AddMenu("Drawings");

	FarmMenu = MainMenu->AddMenu("Farm/Jungle Setting");
	FarmQ = FarmMenu->CheckBox("Use Q Farm", true);
	FarmManaPercent = FarmMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	MiscMenu = MainMenu->AddMenu("Misc Setting");
	KillstealQ = MiscMenu->CheckBox("Use Q to killsteal", true);
	KillstealW = MiscMenu->CheckBox("Use W to killsteal", true);
	ImmobileQ = MiscMenu->CheckBox("Use Q in Immobile", true);
	ImmobileW = MiscMenu->CheckBox("Use W in Immobile", true);

	DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
	DrawQ = Drawings->CheckBox("Draw Q", true);
	DrawW = Drawings->CheckBox("Draw W", false);
	DrawR = Drawings->CheckBox("Draw R", true);
}
void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithMinions | kCollidesWithYasuoWall));
	W = GPluginSDK->CreateSpell2(kSlotW, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));

	Q->SetOverrideRange(1150);
	W->SetOverrideRange(950);
	R->SetOverrideRange(3000);

	Q->SetOverrideDelay(0.25);
	W->SetOverrideDelay(0.25);
	R->SetOverrideDelay(1.1);

	Q->SetOverrideRadius(60);
	W->SetOverrideRadius(80);
	R->SetOverrideRadius(160);
	Q->SetOverrideSpeed(2000);
	W->SetOverrideSpeed(1600);
	R->SetOverrideSpeed(2000);

}


void Combo()
{
	if (ComboQ->Enabled())
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			Q->CastOnTarget(target, kHitChanceHigh);
		}
	}
	if (ComboW->Enabled())
	{
		if (W->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			W->CastOnTarget(target, kHitChanceHigh);
		}
	}

	if (ComboR->Enabled() && R->IsReady())
	{
		for (auto Enemy : GEntityList->GetAllHeros(false, true))
		{
			if (Enemy != nullptr && !Enemy->IsDead())
			{
				if (ComboR->Enabled())
				{
					auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotR);
					if (Enemy->IsValidTarget(myHero, R->Range()) && !Enemy->IsInvulnerable()
						&& !GEntityList->Player()->IsValidTarget(Enemy, Q->Range()))
					{
						if (Enemy->GetHealth() <= dmg && R->IsReady())
						{
							R->CastOnTarget(Enemy, kHitChanceHigh);
						}
					}
				}
			}
		}
	}

	/*if (R->IsReady() && ComboRAOEuse->Enabled())
	{
	auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, float(RRange->GetInteger()));
	if (target != nullptr &&  GEntityList->Player()->IsValidTarget(target, RRange->GetInteger()))
	{
	int enemies = 0;
	Vec3 pos = Vec3();
	R->FindBestCastPosition(false, true, pos, enemies);
	if (enemies >= ComboRAOE->GetInteger())
	R->CastOnPosition(pos);
	}
	}*/
}

void Farm()
{
	if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
		return;
	if (FarmQ->Enabled())
	{
		if (Q->IsReady())
		{
			Q->AttackMinions();

			Q->LastHitMinion();
		}
	}
}

void JungleClear()
{
	if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
		return;
	if (FarmQ->Enabled() && Q->IsReady())
		for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
		{
			if (jMinion != nullptr && !jMinion->IsDead())
			{
				if (FarmQ->Enabled() && Q->IsReady() && myHero->IsValidTarget(jMinion, Q->Range()))
				{
					Q->CastOnUnit(jMinion);
				}

			}
		}
}

void Harass()
{
	if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
		return;
	if (HarassQ->Enabled())
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			Q->CastOnTarget(target, kHitChanceHigh);
		}
	}
	if (HarassW->Enabled())
	{
		if (W->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			W->CastOnTarget(target, kHitChanceHigh);
		}
	}
}

void AutoImmobile()
{
	if (Q->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		if (target != nullptr && target->IsValidTarget(myHero, Q->Range()) && !target->IsInvulnerable()) {
			if (ImmobileQ->Enabled())
			{
				{
					Q->CastOnTarget(target, kHitChanceImmobile);
				}
			}
		}
	}
	if (W->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
		if (target != nullptr && target->IsValidTarget(myHero, W->Range()) && !target->IsInvulnerable()) {
			if (ImmobileW->Enabled())
			{
				{
					W->CastOnTarget(target, kHitChanceImmobile);
				}
			}
		}
	}
}
void killsteal()
{
	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
		if (Enemy != nullptr && !Enemy->IsDead())
		{
			if (KillstealQ->Enabled())
			{
				auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotQ);
				if (Enemy->IsValidTarget(myHero, Q->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmg && Q->IsReady())
					{
						Q->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}
			if (KillstealW->Enabled())
			{
				auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotW);
				if (Enemy->IsValidTarget(myHero, W->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmg && W->IsReady())
					{
						W->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}
		}
	}
}


PLUGIN_EVENT(void) OnRender()
{
	if (DrawReady->Enabled())
	{
		if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

		if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

		if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
	}
	else
	{
		if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

		if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

		if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
	}
}
PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		Combo();
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		Farm();
		//JungleClear();
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		Harass();
	}
	AutoImmobile();
	killsteal();
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);
	Menu();
	LoadSpells();
	myHero = GEntityList->Player();

	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);


}

PLUGIN_API void OnUnload()
{
	MainMenu->Remove();


	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);

}