// D-Ezreal.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"




PluginSetup("D-ezreal");

IMenu* MainMenu;
IMenu* ComboMenu;
IMenu* HarassMenu;
IMenu* FarmMenu;
IMenu* JungleMenu;
IMenu* MiscMenu;
IMenu* Drawings;
IMenu* ItemsMenu;
IMenu* PotionMenu;
IMenuOption* SemiR;
IMenuOption* UseIgnitecombo;
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
IMenuOption* JungleQ;
IMenuOption* JungleManaPercent;
IMenuOption* StackTear;
IMenuOption* StackManaPercent;
IMenuOption* UseIgnitekillsteal;
IMenuOption* KillstealQ;
IMenuOption* KillstealW;
IMenuOption* ImmobileQ;
IMenuOption* ImmobileW;
IMenuOption* Blade_Cutlass;
IMenuOption* MyHpPreBlade;
IMenuOption* EnemyHpPreBlade;
IMenuOption* usepotion;
IMenuOption* usepotionhpper;
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
IInventoryItem* blade;
IInventoryItem* Cutlass;
IInventoryItem* HealthPot;
IInventoryItem* CorruptPot;
IInventoryItem* Biscuit;
IInventoryItem* RefillPot;
IInventoryItem* hunter;

void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Ezreal");

	ComboMenu = MainMenu->AddMenu("Combo Settings");
	//UseIgnitecombo = ComboMenu->CheckBox("Use Ignite", true);
	ComboQ = ComboMenu->CheckBox("Use Q", true);
	ComboW = ComboMenu->CheckBox("Use W", true);
	ComboR = ComboMenu->CheckBox("Use R if Is killable", true);
	ComboRAOEuse = ComboMenu->CheckBox("Use R if hit 3 Enemys", false);
	//ComboRAOE = ComboMenu->AddInteger("Use R if hit X Enemys", 1, 5, 3);


	HarassMenu = MainMenu->AddMenu("Harass Setting");
	HarassQ = HarassMenu->CheckBox("Use Q", true);
	HarassW = HarassMenu->CheckBox("Use W", true);
	HarassManaPercent = HarassMenu->AddInteger("Mana Percent for harass", 10, 100, 70);
	Drawings = MainMenu->AddMenu("Drawings");

	FarmMenu = MainMenu->AddMenu("LaneClear Setting");
	FarmQ = FarmMenu->CheckBox("Use Q Farm", true);
	FarmManaPercent = FarmMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	JungleMenu = MainMenu->AddMenu("Jungle Setting");
	JungleQ = JungleMenu->CheckBox("Use Q Jungle", true);
	JungleManaPercent = JungleMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	MiscMenu = MainMenu->AddMenu("Misc Setting");
	//SemiR = MiscMenu->AddKey("Semi-Manual R", 84);
	StackTear = MiscMenu->CheckBox("Stack Tear", true);
	StackManaPercent = MiscMenu->AddInteger("Mana Percent To Stuck", 10, 100, 95);
	//UseIgnitekillsteal = MiscMenu->CheckBox("Use Ignite to killsteal", false);
	KillstealQ = MiscMenu->CheckBox("Use Q to killsteal", true);
	KillstealW = MiscMenu->CheckBox("Use W to killsteal", true);
	ImmobileQ = MiscMenu->CheckBox("Use Q in Immobile", true);
	ImmobileW = MiscMenu->CheckBox("Use W in Immobile", true);

	ItemsMenu = MainMenu->AddMenu("Items Setting");
	Blade_Cutlass = ItemsMenu->CheckBox("Blade-Cutlass", true);
	MyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if my HP <", 10, 100, 35);
	EnemyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if Enemy HP <", 10, 100, 35);

	PotionMenu = MainMenu->AddMenu("Potion Setting");
	usepotion = PotionMenu->CheckBox("Use potions", true);
	usepotionhpper = PotionMenu->AddInteger("Use potions if HP <", 10, 100, 35);

	DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
	DrawQ = Drawings->CheckBox("Draw Q", true);
	DrawW = Drawings->CheckBox("Draw W", false);
	DrawR = Drawings->CheckBox("Draw R", true);
}
void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithYasuoWall));
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

	
	Tear = GPluginSDK->CreateItemForId(3070, 0);
	Manamune = GPluginSDK->CreateItemForId(3004, 0);
	blade = GPluginSDK->CreateItemForId(3153, 550);
	Cutlass = GPluginSDK->CreateItemForId(3144, 550);
	HealthPot = GPluginSDK->CreateItemForId(2003, 0);
	CorruptPot = GPluginSDK->CreateItemForId(2033, 0);
	RefillPot = GPluginSDK->CreateItemForId(2031, 0);
	Biscuit = GPluginSDK->CreateItemForId(2010, 0);
	hunter = GPluginSDK->CreateItemForId(2032, 0);
}

static bool InFountain(IUnit *unit)
{
	//TODO: Implement
	return unit->HasBuff("kappachino");
}

int EnemiesInRange(IUnit* Source, float range)
{
	auto Targets = GEntityList->GetAllHeros(false, true);
	auto enemiesInRange = 0;

	for (auto target : Targets)
	{
		if (target != nullptr)
		{
			auto flDistance = (target->GetPosition() - Source->GetPosition()).Length();
			if (flDistance < range)
			{
				enemiesInRange++;
			}
		}
	}
	return enemiesInRange;
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
	if (CountEnemiesInRange(2000) >= 1 || GGame->IsChatOpen())
		return;
	if(GOrbwalking->GetOrbwalkingMode() == kModeCombo || GOrbwalking->GetOrbwalkingMode() == kModeMixed|| GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
		return;
	if (StackTear->Enabled() && myHero->ManaPercent() > StackManaPercent->GetInteger())
	{
		if ((Tear->IsOwned() || Manamune->IsOwned()) && !myHero->IsRecalling())
		{
			Q->CastOnPosition(myHero->ServerPosition());
		}
	}
}

void UseItems()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
			if (Blade_Cutlass->Enabled() && myHero->IsValidTarget(enemy, 550))
			{
				if (myHero->HealthPercent() < MyHpPreBlade->GetInteger() || enemy->HealthPercent() < EnemyHpPreBlade->GetInteger())
				{
					if (blade->IsOwned() && blade->IsReady())
						blade->CastOnTarget(enemy);
					if (Cutlass->IsOwned() && Cutlass->IsReady())
						Cutlass->CastOnTarget(enemy);
				}
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
			if (myHero->IsValidTarget(target, Q->Range()))
			Q->CastOnTarget(target, kHitChanceHigh);
		}
	}
	if (ComboW->Enabled())
	{
		if (W->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			if (myHero->IsValidTarget(target, W->Range()))
			W->CastOnTarget(target, kHitChanceHigh);
		}
	}

	if (ComboR->Enabled() && R->IsReady())
	{
		for (auto Enemy : GEntityList->GetAllHeros(false, true))
		{
			if (Enemy != nullptr && !Enemy->IsDead())
			{
				auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotR);
				if (myHero->IsValidTarget(Enemy, R->Range()) && !Enemy->IsInvulnerable()
					&& !myHero->IsValidTarget(Enemy, Q->Range()))
				{
					if (Enemy->GetHealth() <= dmg && R->IsReady())
					{
						R->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}
		}
	}

	if (R->IsReady() && ComboRAOEuse->Enabled())
	{
		for (auto Enemy : GEntityList->GetAllHeros(false, true))
		{
			if (Enemy != nullptr && !Enemy->IsDead())
			{
				if (Enemy != nullptr &&  myHero->IsValidTarget(Enemy, R->Range()))
				{
					R->CastOnTargetAoE(Enemy, 3, kHitChanceLow);
				}
			}
		}
	}
}
PLUGIN_EVENT(void) OnAfterAttack(IUnit* source, IUnit* target)
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{		
		if (FarmQ->Enabled() && Q->IsReady())
		{
			int MinionDie = 0;
			for (auto minions : GEntityList->GetAllMinions(false, true, false))
			{
				if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
				{
					auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
					auto dmg1 = GDamage->GetAutoAttackDamage(myHero, minions, true);
					if (!myHero->GetRealAutoAttackRange(minions) || minions->GetHealth() <= dmg || minions->GetHealth() <= dmg1 || minions->GetHealth() <= dmg1 + dmg)
						MinionDie++;
				}
				if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
					return;
				if (MinionDie >1)
					Q->CastOnUnit(minions)|| Q->LastHitMinion();
				auto dmg1 = GDamage->GetAutoAttackDamage(myHero, minions, true);
				if (!myHero->GetRealAutoAttackRange(minions) && minions->GetHealth()<dmg1)
				{
					Q->CastOnUnit(minions);
				}
			}
		}		
		if (JungleQ->Enabled() && Q->IsReady())
		{			
			for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
			{
				if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
				{
					if (myHero->ManaPercent() < JungleManaPercent->GetInteger())
						return;
					Q->CastOnUnit(jMinion);
				}
			}
		}
	}
}
void Harass()
{
	if (myHero->ManaPercent() < HarassManaPercent->GetInteger())
		return;
	if (HarassQ->Enabled())
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (myHero->IsValidTarget(target, Q->Range()))
			Q->CastOnTarget(target, kHitChanceHigh);
		}
	}
	if (HarassW->Enabled())
	{
		if (W->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			if (myHero->IsValidTarget(target, W->Range()))
			W->CastOnTarget(target, kHitChanceHigh);
		}
	}
}

void AutoImmobile()
{
	if (GGame->IsChatOpen()) return;
	if (Q->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		if (target != nullptr && myHero->IsValidTarget(target, Q->Range()) && !target->IsInvulnerable())
		{
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
		if (target != nullptr && myHero->IsValidTarget(target, W->Range()) && !target->IsInvulnerable())
		{
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
	if (GGame->IsChatOpen()) return;
	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
		if (Enemy != nullptr && !Enemy->IsDead())
		{
			if (KillstealQ->Enabled())
			{
				auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotQ);
				if (myHero->IsValidTarget(Enemy, Q->Range()) && !Enemy->IsInvulnerable())
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
				if (myHero->IsValidTarget(Enemy, W->Range()) && !Enemy->IsInvulnerable())
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

void Usepotion()
{
	if (usepotion->Enabled() && !myHero->IsRecalling() && !myHero->IsDead())
	{
		if (CountEnemiesInRange(2000) > 0)
		{
			bool usepotions = myHero->GetHealth() < myHero->GetMaxHealth()* usepotionhpper->GetInteger() / 100;
			if (usepotions)
			{
				if (myHero->GetBuffDataByName("ItemDarkCrystalFlask") || myHero->GetBuffDataByName("ItemMiniRegenPotion")
					|| myHero->GetBuffDataByName("ItemCrystalFlask") || myHero->GetBuffDataByName("RegenerationPotion") || myHero->HasBuff("ItemCrystalFlaskJungle"))
					return;

				if (Biscuit->IsOwned() && !InFountain(myHero) && Biscuit->IsReady())
				{
					Biscuit->CastOnPlayer();
				}
				else if (HealthPot->IsOwned() && !InFountain(myHero) && HealthPot->IsReady())
				{
					HealthPot->CastOnPlayer();
				}
				else if (CorruptPot->IsOwned() && CorruptPot->IsReady())
				{
					CorruptPot->CastOnPlayer();
				}
				else if (RefillPot->IsOwned() && RefillPot->IsReady())
				{
					RefillPot->CastOnPlayer();
				}
				else if (hunter->IsOwned() && hunter->IsReady())
				{
					hunter->CastOnPlayer();
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
	/*if (GetAsyncKeyState(SemiR->GetInteger()) && R->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());
		if (target != nullptr && myHero->IsValidTarget(target, R->Range()))
		{
			R->CastOnTargetAoE(target, 3, kHitChanceHigh);
		}
	}*/
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		Combo();
	}
	
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		Harass();
	}
	AutoImmobile();
	killsteal();
	UseItems();
	stucktear();
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
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);
	if (strcmp(GEntityList->Player()->ChampionName(), "Ezreal") == 0)
	{
		GGame->PrintChat("D-Ezreal : Loaded");
	}
	else
	{
		GGame->PrintChat("You are not playing Ezreal...");
	}
}
	

PLUGIN_API void OnUnload()
{
	MainMenu->Remove();


	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);

}