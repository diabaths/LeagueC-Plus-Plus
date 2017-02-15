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
IMenuOption* StackTear;
IMenuOption* StackManaPercent;
IMenuOption* UseIgnitekillsteal;
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

ISpell* Ignite;

IInventoryItem* Tear;
IInventoryItem* Manamune;

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
	StackTear = MiscMenu->CheckBox("Stack Tear", true);
	StackManaPercent = MiscMenu->AddInteger("Mana Percent To Stuck", 10, 100, 95);
	UseIgnitekillsteal = MiscMenu->CheckBox("Use Ignite to killsteal", true);
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
	E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall | kCollidesWithMinions));

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

	Ignite = GPluginSDK->CreateSpell(GEntityList->Player()->GetSpellSlot("summonerdot"), 600);
	Tear = GPluginSDK->CreateItemForId(3070, 0);
	Manamune = GPluginSDK->CreateItemForId(3004, 0);
}

float GetDistance(IUnit* Player, IUnit* target)
{
	return (Player->GetPosition() - target->GetPosition()).Length2D();
}

int CountEnemiesInRange(float range)
{
	int enemies = 0;
	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && GetDistance(GEntityList->Player(), enemy) <= range)
		{
			enemies++;
		}
	}
	return enemies;
}
void stucktear()
{
	if (StackTear->Enabled() && myHero->ManaPercent() > StackManaPercent->GetInteger())
	{
		if(Tear->IsOwned() || Manamune->IsOwned() && !myHero->IsRecalling() && CountEnemiesInRange(1000) <= 0)
		{
			Q->CastOnPosition(myHero->ServerPosition());
		}
	}
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
			int MinionDie = 0;
			for (auto minions : GEntityList->GetAllMinions(false, true, false))
			{
				if (minions != nullptr && minions->IsValidTarget(myHero, Q->Range()))
				{
					auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
					auto dmg1 = GDamage->GetAutoAttackDamage(myHero, minions, false);
					if (minions->GetHealth() <= dmg || minions->GetHealth() <= dmg1 || minions->GetHealth() <= dmg + dmg1)
						MinionDie++;
				}
				if (MinionDie >= 1)
					Q->CastOnTarget(minions, kHitChanceMedium);
			}
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
				if (myHero->IsValidTarget(jMinion, Q->Range()))
				{
					Q->CastOnTarget(jMinion, kHitChanceMedium);
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
				auto dmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotW);
				if (Enemy->IsValidTarget(myHero, W->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmg && W->IsReady())
					{
						W->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}
			if (UseIgnitekillsteal->Enabled() && Ignite->GetSpellSlot() != kSlotUnknown && Enemy->IsVisible())
			{
				auto dmg = GDamage->GetSpellDamage(myHero, Enemy, kSummonerSpellIgnite);
				if (Enemy->GetHealth() <= dmg && Enemy->IsValidTarget(myHero, Ignite->GetSpellRange()) && Enemy->IsValidTarget())
				{
					Ignite->CastOnUnit(Enemy);
				}
			}
		}
	}
}

/*void Usepotion()
{
	if (AutoPotion->Enabled() && !myHero->IsRecalling() && !myHero->IsDead())
	{
		if (Biscuit->IsReady() && !myHero->GetBuffDataByName("ItemMiniRegenPotion") && !myHero->GetBuffDataByName("ItemCrystalFlask"))
		{
			if (myHero->GetMaxHealth() > myHero->GetHealth() + 170 && myHero->GetMaxMana() > myHero->GetMana() + 10 && CountEnemiesInRange(1000) > 0
				&& myHero->GetHealth() < GEntityList->Player()->GetMaxHealth() * 0.75)
			{
				Biscuit->CastOnPlayer();
			}
			else if (myHero->GetMaxHealth() > myHero->GetHealth() + 170 && myHero->GetMaxMana() > myHero->GetMana() + 10 && CountEnemiesInRange(1000) == 0
				&& myHero->GetHealth() < myHero->GetMaxHealth() * 0.6)
			{
				Biscuit->CastOnPlayer();
			}
		}
		else if (HealthPot->IsReady() && !myHero->GetBuffDataByName("RegenerationPotion") && !myHero->GetBuffDataByName("ItemCrystalFlask"))
		{
			if (myHero->GetMaxHealth() > myHero->GetHealth() + 150 && CountEnemiesInRange(1000) > 0 &&
				myHero->GetHealth() < myHero->GetMaxHealth() * 0.75)
			{
				HealthPot->CastOnPlayer();
			}
			else if (myHero->GetMaxHealth() > myHero->GetHealth() + 150 && CountEnemiesInRange(1000) == 0 &&
				myHero->GetHealth() < myHero->GetMaxHealth() * 0.6)
			{
				HealthPot->CastOnPlayer();
			}
		}
		else if (CorruptPot->IsReady() && !myHero->GetBuffDataByName("ItemDarkCrystalFlask") && !myHero->GetBuffDataByName("RegenerationPotion")
			&& !myHero->GetBuffDataByName("ItemCrystalFlask") && !myHero->GetBuffDataByName("ItemMiniRegenPotion"))
		{
			if (myHero->GetMaxHealth() > myHero->GetHealth() + 120 && myHero->GetMaxMana() > myHero->GetMana() + 60 && CountEnemiesInRange(1000) > 0
				&& (myHero->GetHealth() < myHero->GetMaxHealth() * 0.7 || myHero->GetMana() < myHero->GetMaxMana() * 0.5))
			{
				CorruptPot->CastOnPlayer();
			}
			else if (myHero->GetMaxHealth() > myHero->GetHealth() + 120 && myHero->GetMaxMana() > myHero->GetMana() + 60 && CountEnemiesInRange(1000) == 0
				&& (myHero->GetHealth() < myHero->GetMaxHealth() * 0.7 || myHero->GetMana() < myHero->GetMaxMana() * 0.5))
			{
				CorruptPot->CastOnPlayer();
			}
		}
	}
}*/

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

/*void SkinChanger()
{
	if (myHero->GetSkinId() != ChangeSkin->GetInteger())
	{
		myHero->SetSkinId(ChangeSkin->GetInteger());
	}
}

PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
	if (args.Sender->IsEnemy(myHero) && args.Sender->IsHero())
	{
		if (AutoEGapcloser->Enabled() && E->IsReady() && !args.IsTargeted)
		{
			E->CastOnPosition(args.Sender->ServerPosition(GapCloserSpell, E->Range()));
		}
	}
}*/

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		Combo();
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		Farm();
		JungleClear();
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		Harass();
	}
	AutoImmobile();
	killsteal();
	if (GOrbwalking->GetOrbwalkingMode() == kModeNone)
	{
		stucktear();
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


}

PLUGIN_API void OnUnload()
{
	MainMenu->Remove();


	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);

}