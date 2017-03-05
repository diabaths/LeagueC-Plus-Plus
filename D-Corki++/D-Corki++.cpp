// D-Corki.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"
#define M_PI 3.14159265358979323846





PluginSetup("D-Corki");

IMenu* MainMenu;
IMenu* ComboMenu;
IMenu* HarassMenu;
IMenu* FarmMenu;
IMenu* JungleMenu;
IMenu* MiscMenu;
IMenu* Drawings;
IMenu* ItemsMenu;
IMenu* PotionMenu;
IMenuOption* UseIgnitecombo;
IMenuOption* ComboQ;
IMenuOption* ComboE;
IMenuOption* ComboR;
IMenuOption* HarassQ;
IMenuOption* HarassE;
IMenuOption* HarassR;
IMenuOption* Harassammo;
IMenuOption* HarassManaPercent;
IMenuOption* FarmQ;
IMenuOption* FarmE;
IMenuOption* FarmR;
IMenuOption* Farmammo;
IMenuOption* FarmManaPercent;
IMenuOption* JungleQ;
IMenuOption* JungleE;
IMenuOption* JungleR;
IMenuOption* Jungleammo;
IMenuOption* JungleManaPercent;
IMenuOption* UseIgnitekillsteal;
IMenuOption* KillstealQ;
IMenuOption* KillstealR;
IMenuOption* ImmobileQ;
IMenuOption* ImmobileR;
IMenuOption* Blade_Cutlass;
IMenuOption* MyHpPreBlade;
IMenuOption* EnemyHpPreBlade;
IMenuOption*hextechuse;
IMenuOption*MyHpPrehextech; 
IMenuOption*EnemyHpPrehextech; 
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

IInventoryItem* hextech;
IInventoryItem* blade;
IInventoryItem* Cutlass;
IInventoryItem* HealthPot;
IInventoryItem* CorruptPot;
IInventoryItem* Biscuit;
IInventoryItem* RefillPot;
IInventoryItem* hunter;

int lastq;
int lastr;
void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Corki");

	ComboMenu = MainMenu->AddMenu("Combo Settings");
	UseIgnitecombo = ComboMenu->CheckBox("Use Ignite", true);
	ComboQ = ComboMenu->CheckBox("Use Q", true);
	ComboE = ComboMenu->CheckBox("Use E", true);
	ComboR = ComboMenu->CheckBox("Use R", true);
	

	HarassMenu = MainMenu->AddMenu("Harass Setting");
	HarassQ = HarassMenu->CheckBox("Use Q", true);
	HarassE = HarassMenu->CheckBox("Use E", true);
	HarassR = HarassMenu->CheckBox("Use E", true);
	Harassammo = HarassMenu->AddInteger("R Ammount to use R >", 1, 7, 3);
	HarassManaPercent = HarassMenu->AddInteger("Mana Percent for harass", 10, 100, 70);
	
	FarmMenu = MainMenu->AddMenu("LaneClear Setting");
	FarmQ = FarmMenu->CheckBox("Use Q Farm", true);
	FarmE = FarmMenu->CheckBox("Use E Farm", false);
	FarmR = FarmMenu->CheckBox("Use R Farm", true);
	Farmammo = FarmMenu->AddInteger("R Ammount to use R >", 1, 7, 3);
	FarmManaPercent = FarmMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	JungleMenu = MainMenu->AddMenu("Jungle Setting");
	JungleQ = JungleMenu->CheckBox("Use Q Jungle", true);
	JungleE = JungleMenu->CheckBox("Use E Jungle", true);
	JungleR = JungleMenu->CheckBox("Use R Jungle", true);
	Jungleammo = JungleMenu->AddInteger("R Ammount to use R >", 1, 7, 3);
	JungleManaPercent = JungleMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	MiscMenu = MainMenu->AddMenu("Misc Setting");
	KillstealQ = MiscMenu->CheckBox("Use Q to killsteal", true);
	KillstealR = MiscMenu->CheckBox("Use R to killsteal", true);
	ImmobileQ = MiscMenu->CheckBox("Use Q Immobile", true);
	ImmobileR = MiscMenu->CheckBox("Use R Immobile", true);
	

	ItemsMenu = MainMenu->AddMenu("Items Setting");
	Blade_Cutlass = ItemsMenu->CheckBox("Blade-Cutlass", true);
	MyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if my HP <", 10, 100, 35);
	EnemyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if Enemy HP <", 10, 100, 35);
	hextechuse = ItemsMenu->CheckBox("hextech", true);
	MyHpPrehextech = ItemsMenu->AddInteger("Use hextech if my HP <", 10, 100, 35);
	EnemyHpPrehextech = ItemsMenu->AddInteger("Use hextech if Enemy HP <", 10, 100, 35);

	PotionMenu = MainMenu->AddMenu("Potion Setting");
	usepotion = PotionMenu->CheckBox("Use potions", true);
	usepotionhpper = PotionMenu->AddInteger("Use potions if HP <", 10, 100, 35);

	Drawings = MainMenu->AddMenu("Drawings");
	DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
	DrawQ = Drawings->CheckBox("Draw Q", true);
	DrawW = Drawings->CheckBox("Draw W", false);
	DrawR = Drawings->CheckBox("Draw R", false);
}
void LoadSpells()
{	
	Q = GPluginSDK->CreateSpell2(kSlotQ, kCircleCast, true, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	Q->SetSkillshot(0.35f, 250.f, 1000.f, 825.f);
	
	W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, true, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	Q->SetSkillshot(0.35f, 250.f, 1000.f, 800.f);

	E = GPluginSDK->CreateSpell2(kSlotE, kConeCast, false, true, static_cast<eCollisionFlags> (kCollidesWithYasuoWall));
	E->SetSkillshot(0.0f, (45 * M_PI / 180.0), 1500.f, 600.f);
	
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithYasuoWall));
	R->SetSkillshot(0.20f, 40.f, 2000.f, 1300.f);
	
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

	hextech = GPluginSDK->CreateItemForId(3146, 700);
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
int ultiammo()
{
	if (myHero->GetSpellBook()->GetLevel(kSlotR) > 0)
	{		
			return myHero->GetSpellBook()->GetAmmo(kSlotR);
	}
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
			if (hextechuse->Enabled() && myHero->IsValidTarget(enemy, 700))
			{
				if (myHero->HealthPercent() < MyHpPrehextech->GetInteger() || enemy->HealthPercent() < EnemyHpPrehextech->GetInteger())
				{
					if (hextech->IsOwned() && hextech->IsReady())
						hextech->CastOnTarget(enemy);

				}
			}
		}
	}
}
void Combo()
{
	if (Ignite != nullptr)
	{
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
		if (UseIgnitecombo->Enabled() && Ignite->IsReady())
		{
			if (Enemy != nullptr && Enemy->IsValidTarget(myHero, 570))
			{
				if (Enemy->HealthPercent() <= 30)
				{
					Ignite->CastOnUnit(Enemy);
				}
			}
		}
	}

	if (ComboQ->Enabled() && GGame->CurrentTick() - lastr >100)
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (myHero->IsValidTarget(target, Q->Range()) &&  target != nullptr)
			{
				AdvPredictionOutput prediction_output;
				Q->RunPrediction(target, true, kCollidesWithYasuoWall, &prediction_output);
				if (prediction_output.HitChance >= kHitChanceHigh)
					Q->CastOnTarget(target);
				lastq = GGame->CurrentTick();
			}
		}
	}
	if (ComboE->Enabled())
	{
		if (E->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
			if (target != nullptr)
			{
				if (myHero->IsValidTarget(target, E->Range()))
					E->CastOnPlayer();
			}
		}
	}

	if (ComboR->Enabled() && R->IsReady() && GGame->CurrentTick() -lastq >100)
	{
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());
		if (myHero->IsValidTarget(Enemy, R->Range()) &&  Enemy != nullptr)
		{
			AdvPredictionOutput prediction_output;
			R->RunPrediction(Enemy, true, kCollidesWithYasuoWall || kCollidesWithMinions, &prediction_output);
			if (!Enemy->IsInvulnerable() && prediction_output.HitChance >= kHitChanceHigh)
			{
				if (GPrediction->GetCollisionFlagsForPoint(Enemy->GetPosition()) == 0)
				R->CastOnTarget(Enemy);
				lastr = GGame->CurrentTick();
			}
		}
	}
}

void laneclear()
{
	for (auto minions : GEntityList->GetAllMinions(false, true, false))
	{
		if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
			return;
		if (FarmQ->Enabled() && Q->IsReady() && GGame->CurrentTick() - lastq >100)
		{
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
			{
				Vec3 pos;
				int hit;
				GPrediction->FindBestCastPosition(Q->Range(), Q->Radius(), true, false, false, pos, hit);
				if (hit >= 2)
				{
					Q->CastOnUnit(minions);
					lastq = GGame->CurrentTick();
					return;
				}
				if (minions->GetHealth() < dmg)
				{
					Q->CastOnUnit(minions);
					lastq = GGame->CurrentTick();
					return;
				}
			}
		}
		if (FarmE->Enabled() && E->IsReady())
		{
			Vec3 pos;
			int hit;
			GPrediction->FindBestCastPosition(E->Range(), E->Radius(), true, true, false, pos, hit);
			if (hit >= 3)
			{
				E->CastOnPlayer();
				return;
			}
		}
		if (FarmR->Enabled() && R->IsReady() && ultiammo() > Farmammo->GetInteger() && GGame->CurrentTick() - lastq >100)
		{
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotR);
			if (minions != nullptr && myHero->IsValidTarget(minions, R->Range()))
			{
				Vec3 pos;
				int hit;
				GPrediction->FindBestCastPosition(R->Range(), R->Radius(), true, true, false, pos, hit);
				if (hit >= 3)
				{
					R->CastOnPosition(pos);
					lastr = GGame->CurrentTick();
					return;
				}
				if (minions->GetHealth() < dmg && GetDistance(myHero, minions) > myHero->GetRealAutoAttackRange(minions))
				{
					R->CastOnUnit(minions);
					lastr = GGame->CurrentTick();
					return;
				}
			}
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
		if (JungleQ->Enabled() && Q->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
			{
				Q->CastOnUnit(jMinion);
				lastq = GGame->CurrentTick();
				return;
			}
		}
		if (JungleE->Enabled() && E->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, E->Range()))
			{
				E->CastOnPlayer();
				return;
			}
		}
		if (JungleR->Enabled() && R->IsReady() && ultiammo() > Jungleammo->GetInteger())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, R->Range()))
			{
				R->CastOnUnit(jMinion);
				return;
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
		if (Q->IsReady() &&  GGame->CurrentTick() - lastr >100)
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (myHero->IsValidTarget(target, Q->Range()) && target != nullptr)
			{
				AdvPredictionOutput prediction_output;
				Q->RunPrediction(target, true, kCollidesWithYasuoWall, &prediction_output);
				if (prediction_output.HitChance >= kHitChanceHigh)
					Q->CastOnTarget(target);
				lastq = GGame->CurrentTick();
			}
		}
	}
	if (HarassE->Enabled())
	{
		if (E->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
			if (target != nullptr)
			{
				if (myHero->IsValidTarget(target, E->Range()))
					E->CastOnPlayer();
			}
		}
	}

	if (HarassR->Enabled() && R->IsReady() && ultiammo()> Harassammo->GetInteger() && GGame->CurrentTick()- lastq >100)
	{
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());
		if (myHero->IsValidTarget(Enemy, R->Range()) && Enemy != nullptr)
		{
			AdvPredictionOutput prediction_output;
			Q->RunPrediction(Enemy, true, kCollidesWithYasuoWall | kCollidesWithMinions, &prediction_output);
			if (!Enemy->IsInvulnerable() && prediction_output.HitChance >= kHitChanceHigh)
			{
				if (GPrediction->GetCollisionFlagsForPoint(Enemy->GetPosition()) == 0)
				R->CastOnTarget(Enemy);
				lastr = GGame->CurrentTick();
			}
		}
	}
}

void AutoImmobile()
{
	if (GGame->IsChatOpen()) return;
	if (Q->IsReady() && GGame->CurrentTick()- lastr >100)
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		if (target != nullptr && myHero->IsValidTarget(target, Q->Range()) && !target->IsInvulnerable())
		{
			if (ImmobileQ->Enabled())
			{
				{
					Q->CastOnTarget(target, kHitChanceImmobile);
					lastq = GGame->CurrentTick();
				}
			}
		}
	}
	if (R->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());
		if (target != nullptr && myHero->IsValidTarget(target, R->Range()) && !target->IsInvulnerable())
		{
			if (ImmobileR->Enabled() && GGame->CurrentTick() - lastq >100)
			{
				if (GPrediction->GetCollisionFlagsForPoint(target->GetPosition()) == 0)
				{
					R->CastOnTarget(target, kHitChanceImmobile);
					lastr = GGame->CurrentTick();
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
			if (KillstealQ->Enabled() && Q->IsReady())
			{
				auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotQ);
				if (myHero->IsValidTarget(Enemy, Q->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmg)
					{
						Q->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}
			if (KillstealR->Enabled() && R->IsReady())
			{
				auto dmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotR);
				if (myHero->IsValidTarget(Enemy, R->Range()) && !Enemy->IsInvulnerable())
				{
					if(GPrediction->GetCollisionFlagsForPoint(Enemy->GetPosition()) == 0)
					if (Enemy->GetHealth() <= dmg)
					{
						R->CastOnTarget(Enemy, kHitChanceHigh);
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




PLUGIN_EVENT(void) OnGameUpdate()
{
	/*if (myHero->HasBuff("CorkiMissileBarrageCounterBig") || myHero->GetBuffCount("CorkiMissileBarrageCounterBig"))
	{
		R->SetOverrideRange(1500);
	}
	else R->SetOverrideRange(1300);*/

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
	if (strcmp(GEntityList->Player()->ChampionName(), "Corki") == 0)
	{
		GGame->PrintChat("D-Corki : Loaded");
	}
	else
	{
		GGame->PrintChat("You are not playing Corki...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	
}