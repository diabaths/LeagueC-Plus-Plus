// D-Thresh++.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"
#include <map>


PluginSetup("D-Thresh");

IMenu* MainMenu;
IMenu* ComboMenu;
IMenu* HarassMenu;
IMenu* FarmMenu;
IMenu* JungleMenu;
IMenu* MiscMenu;
IMenu* Drawings;
IMenu* ItemsMenu;
IMenu* PotionMenu;
IMenu* EMenu;
IMenu* Wsetting;
IMenuOption* SemiR;
IMenuOption* UseIgnitecombo;
IMenuOption* ComboQ;

IMenuOption* ComboQ2;
IMenuOption* ComboW;
IMenuOption* ComboE;
IMenuOption* ComboR;
IMenuOption* ComboRAOE;
IMenuOption* ComboRAOEuse;
IMenuOption* Epush;
IMenuOption* UseEpush;
IMenuOption* UseEpull;
IMenuOption* HarassQ;
IMenuOption* HarassQ2;
IMenuOption* HarassE;
IMenuOption* HarassManaPercent;
IMenuOption* FarmQ;
IMenuOption* FarmE;
IMenuOption* FarmManaPercent;
IMenuOption* JungleQ;
IMenuOption* JungleE;
IMenuOption* JungleManaPercent;
IMenuOption* StackTear;
IMenuOption* StackManaPercent;
IMenuOption* UseIgnitekillsteal;
IMenuOption* Uselatern;
IMenuOption* KillstealQ;
IMenuOption* ImmobileQ;
IMenuOption* DushQ;
IMenuOption*InterruptE; 
IMenuOption*AutoEGapcloser;
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
IMenuOption* Combormin;
IMenuOption* AutoW;
IMenuOption* Wcharm;
IMenuOption* WCombatdehancer;
IMenuOption* Wfear;
IMenuOption* Wknockback;
IMenuOption* Wknockup;
IMenuOption* Wpolymorph;
IMenuOption* Wsnare;
IMenuOption* Wstun;
IMenuOption* Wsuppression;
IMenuOption* Wtaunt;

IUnit* myHero;

ISpell2* Q;
ISpell2* Q2;
ISpell2* W;
ISpell2* E;
ISpell2* R;

ISpell* Ignite;

std::map<int, IMenuOption*> ChampionuseQ;

IInventoryItem* Tear;
IInventoryItem* Manamune;
IInventoryItem* blade;
IInventoryItem* Cutlass;
IInventoryItem* HealthPot;
IInventoryItem* CorruptPot;
IInventoryItem* Biscuit;
IInventoryItem* RefillPot;
IInventoryItem* hunter;

int lastq;
int lastq2;
void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Thresh");

	ComboMenu = MainMenu->AddMenu("Combo Settings");
	UseIgnitecombo = ComboMenu->CheckBox("Use Ignite", true);
	ComboQ = ComboMenu->CheckBox("Use Q", true);
	ComboQ2 = ComboMenu->CheckBox("Use Q2", true);
	ComboW = ComboMenu->CheckBox("Use W", true);
	ComboE = ComboMenu->CheckBox("Use E", true);
	ComboR = ComboMenu->CheckBox("Use R", true);
	ComboRAOEuse = ComboMenu->CheckBox("Use R if hit X Enemys", true);
	Combormin = ComboMenu->AddInteger("Use R if Hit ", 1, 5, 2);
	Epush = ComboMenu->CheckBox("E Push/Pull (on / off)", false);
	
	HarassMenu = MainMenu->AddMenu("Harass Setting");
	HarassQ = HarassMenu->CheckBox("Use Q", true);
	for (auto Enemys : GEntityList->GetAllHeros(false, true))
	{
		std::string szMenuName = "Use Q on - " + std::string(Enemys->ChampionName());
		ChampionuseQ[Enemys->GetNetworkId()] = HarassMenu->CheckBox(szMenuName.c_str(), false);
	}
	HarassQ2 = HarassMenu->CheckBox("Use Q2", true);
	HarassE = HarassMenu->CheckBox("Use E", true);
	HarassManaPercent = HarassMenu->AddInteger("Mana Percent for harass", 10, 100, 70);

	EMenu = MainMenu->AddMenu("E  Setting");
	UseEpush = EMenu->AddKey("Use E to Push", 75);
	UseEpull = EMenu->AddKey("Use E to Pull", 76);
	
	Wsetting = MainMenu->AddMenu("W Setting");
	Uselatern = Wsetting->AddKey("Use Lantern to Ally", 84);
	AutoW = Wsetting->CheckBox("Use W to Ally if Have CC", true);
	Wcharm = Wsetting->CheckBox("Use W in (Charm)", true);
	WCombatdehancer = Wsetting->CheckBox("Use W in (Dehancer)", true);
	Wfear = Wsetting->CheckBox("Use W W in (Fear)", true);
	Wknockback = Wsetting->CheckBox("Use W  in (KnockBack)", true);
	Wknockup = Wsetting->CheckBox("Use W in (KnockUp)", true);
	Wpolymorph = Wsetting->CheckBox("Use W in (Polymorph)", true);
	Wsnare = Wsetting->CheckBox("Use W in (Snare)", true);
	Wstun = Wsetting->CheckBox("Use W to in (Stun)", true);
	Wsuppression = Wsetting->CheckBox("Use W in (Suppresion)", true);
	Wtaunt = Wsetting->CheckBox("Use W in (Taunt)", true);


	FarmMenu = MainMenu->AddMenu("LaneClear Setting");
	FarmQ = FarmMenu->CheckBox("Use Q Farm", false);
	FarmE = FarmMenu->CheckBox("Use E Farm", true);
	FarmManaPercent = FarmMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	JungleMenu = MainMenu->AddMenu("Jungle Setting");
	JungleQ = JungleMenu->CheckBox("Use Q Jungle", true);
	JungleE = JungleMenu->CheckBox("Use E Jungle", true);
	JungleManaPercent = JungleMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	MiscMenu = MainMenu->AddMenu("Misc Setting");
	UseIgnitekillsteal = MiscMenu->CheckBox("Use Ignite to killsteal", false);
	KillstealQ = MiscMenu->CheckBox("Use Q to killsteal", true);
	ImmobileQ = MiscMenu->CheckBox("Use Q in Immobile", true);
	DushQ = MiscMenu->CheckBox("Use Q On Dush", true);
	InterruptE = MiscMenu->CheckBox("Use E to Interrupt", true);
	AutoEGapcloser = MiscMenu->CheckBox("Use E to Gapcloser", true);
	
	ItemsMenu = MainMenu->AddMenu("Items Setting");
	Blade_Cutlass = ItemsMenu->CheckBox("Blade-Cutlass", true);
	MyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if my HP <", 10, 100, 35);
	EnemyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if Enemy HP <", 10, 100, 35);

	PotionMenu = MainMenu->AddMenu("Potion Setting");
	usepotion = PotionMenu->CheckBox("Use potions", true);
	usepotionhpper = PotionMenu->AddInteger("Use potions if HP <", 10, 100, 35);

	Drawings = MainMenu->AddMenu("Drawings");
	DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
	DrawQ = Drawings->CheckBox("Draw Q", true);
	DrawW = Drawings->CheckBox("Draw W", false);
	DrawE = Drawings->CheckBox("Draw W", false);
	DrawR = Drawings->CheckBox("Draw R", false);
}
void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithHeroes | kCollidesWithMinions | kCollidesWithYasuoWall));
	Q->SetSkillshot(0.50f, 60.f, 1900.f, 1100.f);

	Q2 = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	Q2->SetOverrideRange(1400);

	W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, true, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	W->SetSkillshot(0.50f, 50.f, 2200.f, 950.f);
	
	E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, static_cast<eCollisionFlags> (kCollidesWithYasuoWall));
	E->SetOverrideRange(450);
	
	R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	R->SetOverrideRange(400);
		
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
	 
	blade = GPluginSDK->CreateItemForId(3153, 550);
	Cutlass = GPluginSDK->CreateItemForId(3144, 550);
	HealthPot = GPluginSDK->CreateItemForId(2003, 0);
	CorruptPot = GPluginSDK->CreateItemForId(2033, 0);
	RefillPot = GPluginSDK->CreateItemForId(2031, 0);
	Biscuit = GPluginSDK->CreateItemForId(2010, 0);
	hunter = GPluginSDK->CreateItemForId(2032, 0);
}
inline float GetDistanceVectors(Vec3 from, Vec3 to)
{
	float x1 = from.x;
	float x2 = to.x;
	float y1 = from.y;
	float y2 = to.y;
	float z1 = from.z;
	float z2 = to.z;
	return static_cast<float>(sqrt(pow((x2 - x1), 2.0) + pow((y2 - y1), 2.0) + pow((z2 - z1), 2.0)));
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

int CountallyInRange(float range)
{
	int allys = 0;
	for (auto ally : GEntityList->GetAllHeros(true, false))
	{
		if (ally != nullptr && GetDistance(GEntityList->Player(), ally) <= range)
		{
			allys++;
		}
	}
	return allys;
}
static bool HaveQ1()
{
	if (myHero->GetSpellBook()->GetLevel(kSlotQ) > 0)
	{
		return strcmp(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ), "ThreshQ") == 0;
	}

	return false;
}

static bool HaveQ2()
{
	if (myHero->GetSpellBook()->GetLevel(kSlotQ) > 0)
	{
		return strcmp(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ), "threshqleap") == 0;
	}
	return false;
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
void Push()
{
	auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
	if (target!=nullptr&& target->IsValidTarget() && E->IsReady())
	{
		E->CastOnPosition(target->ServerPosition());
	}
}
void Pull()
{
	auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
	if (target != nullptr && target->IsValidTarget() && E->IsReady())
	{
		E->CastOnPosition(target->GetPosition().Extend(myHero->GetPosition(), GetDistanceVectors(target->GetPosition(), myHero->GetPosition()) + 400));
	}
}
static bool IsImmune(IUnit* target)
{
	return target->HasBuff("BlackShield") || target->HasBuff("SivirE") || target->HasBuff("NocturneShroudofDarkness") ||
		target->HasBuff("deathdefiedbuff");

}
void CastQ(IUnit* target)
{
	AdvPredictionOutput prediction_output;
	Q->RunPrediction(target, true, kCollidesWithYasuoWall | kCollidesWithMinions, &prediction_output);
	if (prediction_output.HitChance >= kHitChanceHigh)
	{
		Q->CastOnTarget(target, kHitChanceCollision);
	}
}
static void CheckRComboCast()
{
	auto min = Combormin->GetInteger();;
	int Enemies2;
	Vec3 pos;
	R->FindBestCastPosition(false, true, pos, Enemies2);
	if (Enemies2 >= min)
	{
		R->CastOnPlayer();
	}
}
void CastW()
{
	for (auto Ally : GEntityList->GetAllHeros(true, false))
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
		if (ComboW->Enabled() && GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			if (Ally != myHero && !Ally->IsDead() && Ally != nullptr && myHero->IsValidTarget(Ally, W->Range() + W->Radius()))
			{
				if (GetDistance(myHero, Ally) >= 250 && target != nullptr && myHero->IsValidTarget(target, Q->Range()) && target->HasBuff("ThreshQ") && GGame->TickCount() - lastq > 80)
				{
					W->CastOnPosition(Ally->ServerPosition());
				}
			}
			if (myHero->IsValidTarget(Ally, W->Range()) && CountEnemiesInRange(2000) > 0 && Q->ManaCost() + W->ManaCost()> myHero->GetMana())
			{
				if (Ally->HealthPercent() <= 10 && !Ally->IsDead() && Ally != myHero && !Ally->IsRecalling())
				{
					W->CastOnPosition(Ally->ServerPosition());
				}
				if (myHero->HealthPercent() <= 10)
				{
					W->CastOnPlayer();
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
	if (ComboQ->Enabled() && Q->IsReady() && HaveQ1())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		if (myHero->IsValidTarget(target, Q->Range()) && !IsImmune(target))
		{
			CastQ(target);
			lastq = GGame->TickCount();
		}
	}
	
	if (ComboQ2->Enabled())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q2->Range());
		if (myHero->IsValidTarget(target, Q2->Range()) && target->HasBuff("threshQ") && GGame->TickCount() - lastq > 100)
		{
			Q2->CastOnPlayer();
			lastq2 = GGame->TickCount();
		}
	}
	if (ComboE->Enabled()  && GGame->TickCount() - lastq2 > 250)
	{
		if (E->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
			if (target != nullptr &&myHero->IsValidTarget(target, E->Range()) && !target->HasBuff("threshQ"))
			{
				if (Epush->Enabled() || myHero->HealthPercent() < 15)
				{
					{
						E->CastOnTarget(target, kHitChanceMedium);
					}
				}
				else E->CastOnPosition(target->GetPosition().Extend(myHero->GetPosition(), GetDistanceVectors(target->GetPosition(), myHero->GetPosition()) + 400));
			}
		}
	}
	
	if (W->IsReady())
	{
		CastW();
	}
	
	if (R->IsReady() && ComboRAOEuse->Enabled())
	{
		for (auto Enemy : GEntityList->GetAllHeros(false, true))
		{
			if (GetDistance(myHero, Enemy) <= R->Range()- 60 && Enemy != nullptr && !Enemy->IsDead() && myHero->IsValidTarget(Enemy, R->Range()))
			{
				CheckRComboCast();
			}
		}
	}
}

void Harass()
{
	if (myHero->ManaPercent() < HarassManaPercent->GetInteger())
		return;
	if (HarassQ->Enabled() && Q->IsReady())
	{
		for (auto Enemys : GEntityList->GetAllHeros(false, true))
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			if (myHero->IsValidTarget(target, Q->Range()) && !IsImmune(target))
			{
				if (ChampionuseQ[Enemys->GetNetworkId()]->Enabled())
				{
					CastQ(target);
					lastq = GGame->CurrentTick();
				}
				if (!ChampionuseQ[Enemys->GetNetworkId()]->Enabled() && CountEnemiesInRange(1500) == 1)
				{
					CastQ(target);
					lastq = GGame->CurrentTick();
				}
			}
		}
	}
	if (HarassQ2->Enabled() && Q2->IsReady() && GGame->CurrentTick() - lastq > 50)
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q2->Range());
		if (myHero->IsValidTarget(target, Q2->Range()) && target->HasBuff("threshQ"))
		{
			Q2->CastOnTarget(target);
			lastq = GGame->CurrentTick();
		}
	}
	if (HarassE->Enabled())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range());
		if (E->IsReady() && GGame->CurrentTick() - lastq > 100)
		{
			if (myHero->IsValidTarget(target, E->Range()))
			{
				E->CastOnPosition(target->ServerPosition());
			}
		}
	}
}
PLUGIN_EVENT(void) OnAfterAttack(IUnit* source, IUnit* target)
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		if (myHero->ManaPercent() > FarmManaPercent->GetInteger())
		{
			for (auto minions : GEntityList->GetAllMinions(false, true, false))
			{
				if (FarmQ->Enabled() && Q->IsReady())
				{
					if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
					{
						Q->CastOnUnit(minions);
						lastq = GGame->CurrentTick();
						if (minions->HasBuff("threshQ") && GGame->CurrentTick() - lastq > 50)
							Q2->CastOnUnit(minions);
						lastq = GGame->CurrentTick();
					}
				}
				if (FarmE->Enabled() && E->IsReady() && GGame->CurrentTick() - lastq > 50)
				{
					if (minions != nullptr && myHero->IsValidTarget(minions, E->Range()))
					{
						E->CastOnTargetAoE(minions, 3, kHitChanceLow) || E->LastHitMinion();
					}
				}

			}
			for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
			{
				if (myHero->ManaPercent() < JungleManaPercent->GetInteger())
					return;
				if (JungleQ->Enabled() && Q->IsReady())
				{
					if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
					{

						Q->CastOnUnit(jMinion);
						lastq = GGame->CurrentTick();
					}
					else if (jMinion->HasBuff("threshQ") && GGame->CurrentTick() - lastq > 50)
						Q2->CastOnUnit(jMinion);
					lastq = GGame->CurrentTick();
				}

				if (JungleE->Enabled() && E->IsReady())
				{
					if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, E->Range()))
					{

						E->CastOnUnit(jMinion);
					}
				}
			}
		}
	}
}
	

void AutoImmobile()
{
	if (GGame->IsChatOpen() || myHero->ManaPercent() < 30) return;
	if (Q->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		if (target != nullptr && myHero->IsValidTarget(target, Q->Range()) && !target->IsInvulnerable())
		{
			if (ImmobileQ->Enabled() && HaveQ1())
			{
				{
					Q->CastOnTarget(target, kHitChanceImmobile);
				}
			}
			if (DushQ->Enabled() && HaveQ1())
			{
				{
					Q->CastOnTarget(target, kHitChanceDashing);
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
						AdvPredictionOutput prediction_output;
						Q->RunPrediction(Enemy, false, kCollidesWithYasuoWall | kCollidesWithMinions, &prediction_output);
						if (prediction_output.HitChance >= kHitChanceHigh)
						{
							Q->CastOnTarget(Enemy, kHitChanceCollision);
							lastq = GGame->CurrentTick();
						}
					}
				}
			}
			if (Ignite != nullptr)
			{
				if (UseIgnitekillsteal->Enabled() && Ignite->IsReady())
				{
					auto dmg = GDamage->GetSpellDamage(myHero, Enemy, kSummonerSpellIgnite);
					if (Enemy->GetHealth() < dmg && Enemy != nullptr)
						Ignite->CastOnUnit(Enemy);
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
static bool HaveCC(IUnit* Ally)
{
	if((Ally->HasBuffOfType(BUFF_Charm)&& Wcharm->Enabled()) || (Ally->HasBuffOfType(BUFF_CombatDehancer) && WCombatdehancer->Enabled())||
		(Ally->HasBuffOfType(BUFF_Fear) && Wfear->Enabled() )|| (Ally->HasBuffOfType(BUFF_Knockback) && Wknockback->Enabled()) ||
		(Ally->HasBuffOfType(BUFF_Knockup) && Wknockup->Enabled())|| (Ally->HasBuffOfType(BUFF_Polymorph) && Wpolymorph->Enabled() )||
		(Ally->HasBuffOfType(BUFF_Snare) && Wsnare->Enabled()) || (Ally->HasBuffOfType(BUFF_Stun) && Wstun->Enabled()) ||
		(Ally->HasBuffOfType(BUFF_Suppression) &&  Wsuppression->Enabled()) || (Ally->HasBuffOfType(BUFF_Taunt) && Wtaunt->Enabled()))
	{
		return true;
	}
	return true;
}
void Lantern()
{
	if (W->IsReady())
	{
		for (auto Ally : GEntityList->GetAllHeros(true, false))
		{
			if (Ally != nullptr && Ally != myHero && !Ally->IsDead() && myHero->IsValidTarget(Ally, W->Range() + W->Radius()))
			{
				if (AutoW->Enabled() && HaveCC(Ally))
				{
					{
						W->CastOnPosition(Ally->ServerPosition());
					}
				}
				if (GetAsyncKeyState(Uselatern->GetInteger()))
				{
					W->CastOnPosition(Ally->ServerPosition());
				}
			}
		}
	}
}

PLUGIN_EVENT(void) OnProcessSpellCast(CastedSpell const& args)
{
	if (args.Caster_ == myHero)
	{
		if (std::string(args.Name_) == "ThreshE")
		{
			GOrbwalking->ResetAA();
		}		
	}
}

PLUGIN_EVENT(void) OnCast(CastedSpell const& args)
{
	if (args.Caster_ == myHero)
	{
		if ((std::string(args.Name_) == "ThreshE" || std::string(args.Name_) == "ThreshQLeap")&& GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
			{
				if (ComboR->Enabled() && R->IsReady())
				{
					for (auto Enemy : GEntityList->GetAllHeros(false, true))
					{
						if (Enemy != nullptr && !Enemy->IsDead())
						{
							auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotR);
							if (myHero->IsValidTarget(Enemy, R->Range()) && !Enemy->IsInvulnerable())

							{
								if (Enemy->GetHealth() <= 1.5* dmg && GetDistance(myHero, Enemy) <= R->Range())
								{
									R->CastOnPlayer();
								}
							}
						}
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

		if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

		if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
	}
	else
	{
		if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

		if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

		if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

		if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
	}
}

/*PLUGIN_EVENT(void) OnPlayAnimation(IUnit* Source, std::string const Args)
{
	if (Source == myHero && Source !=Enemy && Args == "Spell3" && E->IsReady())
	if (hero != null)
	{
		if (hero.Team == Player.Team) return;
		if (hero.ChampionName == "Rengar" && args.Animation == "Spell5" && Player.Distance(hero) <= 725)
		{
			if (
				Config.SubMenu("Misc").SubMenu("Gapclosers").Item("rengarleap").GetValue<bool>())
			{
				_E.Cast(unit.Position);
			}
		}
	}
}*/

PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
	if (args.Source->IsEnemy(myHero) && args.Source->IsHero())
	{
		if (AutoEGapcloser->Enabled() && E->IsReady() && !args.IsTargeted && myHero->IsValidTarget(args.Source, 300))
		{
			E->CastOnPosition(args.Source->ServerPosition());
		}
	}
}
PLUGIN_EVENT(void) OnInterruptable(InterruptibleSpell const& Args)
{
	if(InterruptE->Enabled() && E->IsReady() && myHero->IsValidTarget(Args.Source, 300))
	{
		E->CastOnPosition(Args.Source->ServerPosition());
	}
}
PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GGame->IsChatOpen() || myHero->IsDead() || myHero->IsRecalling()) return;
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
	Usepotion();
	if (GetAsyncKeyState(UseEpush->GetInteger()) && E->IsReady())
	{
		Push();
	}
	if (GetAsyncKeyState(UseEpull->GetInteger()) && E->IsReady())
	{
		Pull();
	}	
	Lantern();
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{	
	PluginSDKSetup(PluginSDK);
	Menu();
	LoadSpells();
	myHero = GEntityList->Player();

	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
	GEventManager->AddEventHandler(kEventOnGapCloser, OnGapcloser);
	GEventManager->AddEventHandler(kEventOnInterruptible, OnInterruptable);
	GEventManager->AddEventHandler(kEventOnSpellCast, OnProcessSpellCast);
	GEventManager->AddEventHandler(kEventOnDoCast, OnCast);
	
	if (strcmp(GEntityList->Player()->ChampionName(), "Thresh") == 0)
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "D-Thresh : Loaded!");
	}
	else
	{
		GRender->NotificationEx(Vec4(220, 20, 60, 255), 2, true, true, "You are not playing Thresh...");
	}	
}


PLUGIN_API void OnUnload()
{	
	
	MainMenu->Remove();
	
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapcloser);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, OnInterruptable);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessSpellCast);
	GEventManager->RemoveEventHandler(kEventOnDoCast, OnCast);
	
}