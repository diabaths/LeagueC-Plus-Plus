// D-Tristana.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"
#include <map>
#define M_PI 3.14159265358979323846





PluginSetup("D-Tristana++");

IMenu* MainMenu;
IMenu* QMenu;
IMenu* EMenu;
IMenu* RMenu;
IMenu* ManaMenu;
IMenu* MiscMenu;
IMenu* Drawings;
IMenu* ItemsMenu;
IMenu* PotionMenu;
IMenuOption* ComboQ;
IMenuOption* ComboE;
IMenuOption* HarassE;
IMenuOption* HarassQ;
IMenuOption* HarassManaPercent;
IMenuOption* FarmQ;
IMenuOption* FarmE;
IMenuOption* minminions;
IMenuOption* FarmManaPercent;
IMenuOption* JungleQ;
IMenuOption* JungleE;
IMenuOption* TurrentE;
IMenuOption* JungleManaPercent;

IMenuOption* KillstealR;
IMenuOption* UseRoverkill;
IMenuOption* GapglocerR;
IMenuOption* Int_R;

IMenuOption* useYoumuu;
IMenuOption* Blade_Cutlass;
IMenuOption* MyHpPreBlade;
IMenuOption* EnemyHpPreBlade;
IMenuOption* usepotion;
IMenuOption* usepotionhpper;
IMenuOption* AlwaysQAfterE;

IMenuOption* DrawReady;
IMenuOption* DrawE;
IMenuOption* DrawR;
IMenuOption* eRangeColor;
IMenuOption* rRangeColor;


IUnit* myHero;

ISpell2* Q;
ISpell2* E;
ISpell2* R;


ISpell* Ignite;

IInventoryItem* Youmuu;
IInventoryItem* blade;
IInventoryItem* Cutlass;
IInventoryItem* HealthPot;
IInventoryItem* CorruptPot;
IInventoryItem* Biscuit;
IInventoryItem* RefillPot;
IInventoryItem* hunter;

std::map<int, IMenuOption*> ChampionuseE;

float RRange;
float ERange;

void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Tristana++");
	QMenu = MainMenu->AddMenu("Q Settings");
	ComboQ = QMenu->CheckBox("Use Q in combo", true);
	FarmQ = QMenu->CheckBox("Use Q Farm", true);
	minminions = QMenu->AddInteger("Min Minions to Use Qor E", 1, 6, 4);
	JungleQ = QMenu->CheckBox("Use Q Jungle", true);
		

	EMenu = MainMenu->AddMenu("E Settings");
	ComboE = EMenu->CheckBox("Use E Combo", true);
	HarassE = EMenu->CheckBox("Use E harass", true);
	for (auto Enemys : GEntityList->GetAllHeros(false, true))
	{
		std::string szMenuName = "Use E on - " + std::string(Enemys->ChampionName());
		ChampionuseE[Enemys->GetNetworkId()] = EMenu->CheckBox(szMenuName.c_str(), false);
	}
	FarmE = EMenu->CheckBox("Use E LaneClear", true);
	JungleE = EMenu->CheckBox("Use E Jungle", true);
	TurrentE = EMenu->CheckBox("Use E In Turrents", true);

	RMenu = MainMenu->AddMenu("R Settings");
	KillstealR = RMenu->CheckBox("Use R to killsteal", true);
	UseRoverkill = RMenu->CheckBox("R if  (R+E+AUTO)Dmg > Enemy->health", true);
	Int_R = RMenu->CheckBox("Use R to Interrupter", true);
	GapglocerR = RMenu->CheckBox("Use R to AntiGapcloser", true);

	ManaMenu = MainMenu->AddMenu("Mana Settings");
	HarassManaPercent = ManaMenu->AddInteger("Mana Percent for harass", 10, 100, 70);
	FarmManaPercent = ManaMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);
	JungleManaPercent = ManaMenu->AddInteger("Mana Percent for Jungle", 10, 100, 70);

	ItemsMenu = MainMenu->AddMenu("Items Setting");
	useYoumuu = ItemsMenu->CheckBox("Use Youmuu's", true);
	Blade_Cutlass = ItemsMenu->CheckBox("Blade-Cutlass", true);
	MyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if my HP <", 10, 100, 35);
	EnemyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if Enemy HP <", 10, 100, 35);


	PotionMenu = MainMenu->AddMenu("Potion Setting");
	usepotion = PotionMenu->CheckBox("Use potions", true);
	usepotionhpper = PotionMenu->AddInteger("Use potions if HP <", 10, 100, 35);

	Drawings = MainMenu->AddMenu("Drawings");
	DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
	DrawE = Drawings->CheckBox("Draw E", false);
	eRangeColor = Drawings->AddColor("E Range Color", 50.f, 200.f, 150.f, 255.f);
	DrawR = Drawings->CheckBox("Draw R", false);
	rRangeColor = Drawings->AddColor("R Range Color", 50.f, 200.f, 150.f, 255.f);
}
void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));

	E->SetOverrideRange(ERange);
	R->SetOverrideRange(RRange);



	auto slot1 = GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1);
	auto slot2 = GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2);

	if (strcmp(slot1, "SummonerDot") == 0)
	{
		Ignite = GPluginSDK->CreateSpell(kSummonerSlot1, 600);
	}
	if (strcmp(slot2, "SummonerDot") == 0)
	{
		Ignite = GPluginSDK->CreateSpell(kSummonerSlot2, 600);
	}
	else Ignite == nullptr;

	Youmuu = GPluginSDK->CreateItemForId(3142, 0);
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
int CountMinionInRange(float range)
{
	int minions = 0;
	for (auto minion : GEntityList->GetAllMinions(false, true, false))
	{
		if (minion != nullptr && GetDistance(GEntityList->Player(), minion) <= range)
		{
			minions++;
		}
	}
	return minions;
}

float DamageE(IUnit* target)
{
	float damage = 0;
	if (target->HasBuff("tristanaecharge"))
	{
		damage += GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE) + (GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE)* target->GetBuffCount("tristanaechargesound") * 0.30);
	}
	return damage;
}

void UseItems()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
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
			if (useYoumuu->Enabled() && Youmuu->IsReady() && Youmuu->IsOwned())
			{
				if (myHero->IsValidTarget(enemy, 550))
					Youmuu->CastOnPlayer();
			}

		}
	}
}
void Combo()
{
	if (ComboE->Enabled())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, ERange);
		if (E->IsReady())
		{
			if (target != nullptr && myHero->IsValidTarget(target, ERange))
				E->CastOnTarget(target);
			return;
		}
		if (target != nullptr && target->HasBuff("tristanaecharge") && myHero->IsValidTarget(target, ERange))
		{
			GOrbwalking->SetOverrideTarget(target);
		}
	}
}

void laneclear()
{
	for (auto minions : GEntityList->GetAllMinions(false, true, false))
	{
		if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
			return;
		auto Qmin = minminions->GetInteger();
		if (E->IsReady() && FarmE->Enabled() && CountMinionInRange(ERange) > Qmin)
		{
			if (minions != nullptr && !minions->IsDead() && myHero->IsValidTarget(minions, ERange))
			{
				E->CastOnTarget(minions);
				return;
			}
		}
		if (minions->HasBuff("tristanaecharge") && myHero->IsValidTarget(minions, ERange))
		{
			GOrbwalking->SetOverrideTarget(minions);
		}
	}
}
void jungleclear()
{
	for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
	{
		if (myHero->ManaPercent() < JungleManaPercent->GetInteger())
			return;
		if (strstr(jMinion->GetObjectName(), "mini")) return;

		if (JungleE->Enabled() && E->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, ERange))
			{
				E->CastOnTarget(jMinion);
				return;
			}
		}
		/*if (jMinion->HasBuff("tristanaecharge") && myHero->IsValidTarget(jMinion, ERange))
		{
			GOrbwalking->SetOverrideTarget(jMinion);
		}*/
	}
}

void Harass()
{
	if (myHero->ManaPercent() < HarassManaPercent->GetInteger())
		return;
	if (E->IsReady() && HarassE->Enabled())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, ERange);
		for (auto Enemys : GEntityList->GetAllHeros(false, true))
		{
			if (target != nullptr && myHero->IsValidTarget(target, ERange))
			{
				if (ChampionuseE[Enemys->GetNetworkId()]->Enabled())
				{
					E->CastOnTarget(target);
					return;
				}
				if (!ChampionuseE[Enemys->GetNetworkId()]->Enabled() && CountEnemiesInRange(1500) == 1)
				{
					E->CastOnTarget(target);
					return;
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
			if (KillstealR->Enabled() && R->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, RRange) && Enemy != nullptr)
				{
					auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotR);
					auto autodamage = GDamage->GetAutoAttackDamage(GEntityList->Player(), Enemy, false);
					if (DamageE(Enemy) + dmg + autodamage > Enemy->GetHealth() && UseRoverkill->Enabled())
					{
						R->CastOnTarget(Enemy);
						return;
					}
					else if (Enemy->GetHealth() < DamageE(Enemy) ) return;
					if (Enemy->GetHealth() < dmg &&!Enemy->IsInvulnerable())
					{
						R->CastOnTarget(Enemy);
						return;
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

PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
	if (args.Source->IsEnemy(myHero) && args.Source->IsHero())
	{
		if (GapglocerR->Enabled() && R->IsReady() && !args.IsTargeted && myHero->IsValidTarget(args.Source, 200))
		{
			R->CastOnTarget(args.Source);
		}
	}
}
PLUGIN_EVENT(void) OnInterruptable(InterruptibleSpell const& Args)
{
	if (Int_R->Enabled() && R->IsReady() && Args.DangerLevel >= kHighDanger
		&& myHero->IsValidTarget(Args.Source, R->Range()) && (myHero->GetPosition() - Args.Source->GetPosition()).Length() < RRange)
	{
		R->CastOnTarget(Args.Source);
	}
}

void Eturrent()
{
	for (auto turrent : GEntityList->GetAllTurrets(false, true))
	{		
		if (turrent->GetHealth() >= 100 && turrent != nullptr && CountEnemiesInRange(1000) == 0 && myHero->IsValidTarget(turrent, ERange))
		{			
			E->CastOnUnit(turrent);
			return;
		}
	}
}
PLUGIN_EVENT(void) OnAfterAttack(IUnit* source, IUnit* target)
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
			return;
		if (E->IsReady() && TurrentE->Enabled() && GetDistance(myHero, target) <= E->Range())
		{
			Eturrent();
			return;
		}
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, ERange);
		if (Enemy != nullptr && Enemy->HasBuff("tristanaecharge") && myHero->IsValidTarget(Enemy, ERange))
		{
			GOrbwalking->SetOverrideTarget(Enemy);
		}
	}
}

PLUGIN_EVENT(void) OnBeforeAttack(IUnit* source, IUnit* target)
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && Q->IsReady() && ComboQ->Enabled())
	{
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, ERange);

		if (Enemy != nullptr && myHero->IsValidTarget(Enemy, myHero->GetRealAutoAttackRange(Enemy)))
		{
			Q->CastOnPlayer();
			return;
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		for (auto minions : GEntityList->GetAllMinions(false, true, false))
		{
			auto Qmin = minminions->GetInteger();
			if (Q->IsReady() && FarmQ->Enabled() && myHero->IsValidTarget(minions, myHero->GetRealAutoAttackRange(minions)))
			{
				if (CountMinionInRange(myHero->GetRealAutoAttackRange(minions)) > Qmin)
				{					
					Q->CastOnPlayer();
					return;
				}
			}
		}

		for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
		{
			if (JungleQ->Enabled() && Q->IsReady())
			{
				if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, myHero->GetRealAutoAttackRange(jMinion)))
				{
					Q->CastOnPlayer();
					return;
				}
			}
		}
	}
}
PLUGIN_EVENT(void) OnRender()
{
	Vec4 colore;
	Vec4 colorr;
	eRangeColor->GetColor(&colore);
	rRangeColor->GetColor(&colorr);
	if (DrawReady->Enabled())
	{
		if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colore, ERange); }

		if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorr, RRange); }
	}
	else
	{
		if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colore, ERange); }

		if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorr, RRange); }
	}
}


PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GGame->IsChatOpen()) return;
	auto lvl = (7 * (myHero->GetLevel() - 1));
	RRange = 620 + lvl;
	ERange = 620 + lvl;
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
	GEventManager->AddEventHandler(kEventOrbwalkBeforeAttack, OnBeforeAttack);
	if (strcmp(GEntityList->Player()->ChampionName(), "Tristana") == 0)
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "D-Tristana++ Loaded!");
	}
	else
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "You are not playing Tristana...");
	}	
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();
		
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);
	GEventManager->RemoveEventHandler(kEventOrbwalkBeforeAttack, OnBeforeAttack);
}