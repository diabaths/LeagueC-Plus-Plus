// D-Caitlyn.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"
#define M_PI 3.14159265358979323846





PluginSetup("D-Caitlyn++");

IMenu* MainMenu;
IMenu* QMenu;
IMenu* EMenu;
IMenu* WMenu;
IMenu* RMenu;
IMenu* ManaMenu;
IMenu* MiscMenu;
IMenu* Drawings;
IMenu* ItemsMenu;
IMenu* PotionMenu;
IMenuOption* ComboQ;
IMenuOption* ComboW;
IMenuOption* ComboE;
IMenuOption* ComboR;
IMenuOption* HarassQ;
IMenuOption* HarassManaPercent;
IMenuOption* FarmQ;
IMenuOption* LastHitQ;
IMenuOption* minminions;
IMenuOption* FarmManaPercent;
IMenuOption* JungleQ;
IMenuOption* JungleE;
IMenuOption* JungleManaPercent;
IMenuOption* KillstealQ;
IMenuOption* KillstealR;
IMenuOption* RMin;
IMenuOption* ImmobileQ;
IMenuOption* ImmobileR;
IMenuOption* Blade_Cutlass;
IMenuOption* MyHpPreBlade;
IMenuOption* EnemyHpPreBlade;
IMenuOption* usepotion;
IMenuOption* AutoEGapcloser;
IMenuOption* usepotionhpper;
IMenuOption* AlwaysQAfterE;
IMenuOption* USEE;
IMenuOption* AutoW;
IMenuOption* AutoWmelee;
IMenuOption* AutoWtele;
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


IInventoryItem* blade;
IInventoryItem* Cutlass;
IInventoryItem* HealthPot;
IInventoryItem* CorruptPot;
IInventoryItem* Biscuit;
IInventoryItem* RefillPot;
IInventoryItem* hunter;

float RRange;
int QCastTime;
int LastWTick;

void  Menu()
{	
	MainMenu = GPluginSDK->AddMenu("D-Caitlyn++");
	QMenu = MainMenu->AddMenu("Q Settings");
	ComboQ = QMenu->CheckBox("Use Q in combo", true);
	HarassQ = QMenu->CheckBox("Use Q harass", true);
	FarmQ = QMenu->CheckBox("Use Q Farm", true);
	minminions = QMenu->AddInteger("Use Q if Hit Minions =>", 1, 6, 3);
	LastHitQ = QMenu->CheckBox("Q Lasthit Out Of AA range", true);
	JungleQ = QMenu->CheckBox("Use Q Jungle", true);
	AlwaysQAfterE = QMenu->CheckBox("Always Q after E", true);
	KillstealQ = QMenu->CheckBox("Use Q to killsteal", true);
	ImmobileQ = QMenu->CheckBox("Use Q Immobile", true);

	WMenu = MainMenu->AddMenu("W Settings");
	ComboW = WMenu->CheckBox("Use W in Combo", true);
	AutoWtele = WMenu->CheckBox("Use W in teleport", true);
	AutoW = WMenu->CheckBox("Use W in stun/snare/knockup", true);
	AutoWmelee = WMenu->CheckBox("Use W on you in Enemy is Melee", true);

	EMenu = MainMenu->AddMenu("E Settings");
	ComboE = EMenu->CheckBox("Use E Combo", true);
	USEE = EMenu->AddKey("Use E to Mouse", 84);
	AutoEGapcloser = EMenu->CheckBox("Use E to Gapcloser", true);
	JungleE = EMenu->CheckBox("Use E Jungle", true);

	RMenu = MainMenu->AddMenu("R Settings");
	ComboR = RMenu->CheckBox("Use R Combo", true);
	KillstealR = RMenu->CheckBox("Use R to killsteal", true);
	RMin = RMenu->AddInteger("MMIn Distance to Use R", 10, 3000, 1500);

	ManaMenu = MainMenu->AddMenu("Mana Settings");
	HarassManaPercent = ManaMenu->AddInteger("Mana Percent for harass", 10, 100, 70);
	FarmManaPercent = ManaMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);
	JungleManaPercent = ManaMenu->AddInteger("Mana Percent for Jungle", 10, 100, 70);
	
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
	DrawE = Drawings->CheckBox("Draw E", false);
	DrawR = Drawings->CheckBox("Draw R", false);
}
void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	Q->SetSkillshot(0.25f, 60.f, 2000.f, 1200.f);

	W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, true, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	W->SetSkillshot(1.00f, 100.f, FLT_MAX, 800.f);

	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, static_cast<eCollisionFlags> (kCollidesWithYasuoWall | kCollidesWithMinions));
	E->SetSkillshot(0.25f, 80.f, 1600.f, 770.f);

	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, false, static_cast<eCollisionFlags>( kCollidesWithYasuoWall |kCollidesWithHeroes));
	R->SetSkillshot(0.25f, 0.f, 1000.f, RRange);

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
void CastQ(IUnit* target)
{
	if (Q->IsReady() && target != nullptr && !target->IsWard())
	{
		if (myHero->IsValidTarget(target, Q->Range()))
		{
			auto dmg = GDamage->GetSpellDamage(myHero, target, kSlotQ);
			AdvPredictionOutput prediction_output;
			Q->RunPrediction(target, true, kCollidesWithYasuoWall, &prediction_output);
			if (prediction_output.HitChance >= kHitChanceHigh && CountEnemiesInRange(400) == 0 && !myHero->GetRealAutoAttackRange(target))
			{
				if (target->GetHealth() < dmg)
				{
					Q->CastOnTarget(target);
				}
				else if (target->HasBuff("caitlynyordletrapinternal") || target->HasBuffOfType(BUFF_Stun) || target->HasBuffOfType(BUFF_Snare))
				{
					Q->CastOnTarget(target);
				}
			}		
		}
	}
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
			
		}
	}
}
void Combo()
{
	if (ComboQ->Enabled())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		CastQ(target);
	}
	if (ComboW->Enabled() && W->IsReady() && GGame->CurrentTick() - LastWTick > 1500)
	{
		if (myHero->GetMana() > Q->ManaCost() + E->ManaCost())
		{
			auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			if (myHero->IsValidTarget(Enemy, W->Range()) && Enemy != nullptr && !Enemy->HasBuff("caitlynyordletrapinternal"))
			{
				AdvPredictionOutput prediction_output;
				W->RunPrediction(Enemy, true, kCollidesWithNothing, &prediction_output);
				if (!Enemy->IsInvulnerable() && prediction_output.HitChance >= kHitChanceHigh)
				{
					W->CastOnTarget(Enemy);
					LastWTick = GGame->CurrentTick();
				}
			}
		}
	}
	if (ComboR->Enabled() && R->IsReady() && GGame->CurrentTick() - QCastTime > 1000)
	{
		auto Rmin = RMin->GetInteger();
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, RRange);
		if (myHero->IsValidTarget(Enemy, RRange) && Enemy != nullptr)
		{
			auto dmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotR);
			if ( Enemy->GetHealth() < dmg && !Enemy->IsInvulnerable() && GetDistance(myHero, Enemy) > Rmin)
			{
				R->CastOnUnit(Enemy);
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
		if (Q->IsReady() && !minions->IsWard())
		{
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
			{
				Vec3 pos;
				int Qhit;
				GPrediction->FindBestCastPosition(Q->Range(), Q->Radius(), true, true, false, pos, Qhit);
				if (FarmQ->Enabled() && Qhit >= minminions->GetInteger())
				{
					Q->CastOnPosition(pos);
				}
				 if (LastHitQ->Enabled() && minions->GetHealth() < dmg && GetDistance(myHero, minions) > myHero->GetRealAutoAttackRange(minions))
				{
					Q->CastOnUnit(minions);
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
			}
		}
		if (JungleE->Enabled() && E->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, E->Range()))
			{
				E->CastOnTarget(jMinion);
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
			if (myHero->IsValidTarget(target, Q->Range()) && target != nullptr && !target->IsWard())
			{
				AdvPredictionOutput prediction_output;
				Q->RunPrediction(target, true, kCollidesWithYasuoWall, &prediction_output);
				if (prediction_output.HitChance >= kHitChanceHigh && CountEnemiesInRange(400) == 0)
				{
					if (!myHero->GetRealAutoAttackRange(target) && (target->HasBuffOfType(BUFF_Stun) || target->HasBuffOfType(BUFF_Slow)))
					{
						Q->CastOnTarget(target);
					}
				}
				if (CountEnemiesInRange(400) == 0)
				{
					Q->CastOnTargetAoE(target, 2, kHitChanceHigh);
				}
			}
		}
	}
}
		

void AutoImmobile()
{

	if (Q->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		if (!target->IsWard() && target != nullptr && myHero->IsValidTarget(target, Q->Range()) && !target->IsInvulnerable())
		{
			if (ImmobileQ->Enabled())
			{
				Q->CastOnTarget(target, kHitChanceImmobile);
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
				auto Rmin = RMin->GetInteger();
				if (myHero->IsValidTarget(Enemy, RRange) && Enemy != nullptr)
				{
					auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotR);
					if (Enemy->GetHealth() <  dmg &&!Enemy->IsInvulnerable() && GetDistance(myHero, Enemy) > Rmin)
					{
						R->CastOnUnit(Enemy);
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
PLUGIN_EVENT(void) OnProcessSpellCast(CastedSpell const& args)
{
	if (args.Caster_ == myHero)
	{
		if (std::string(args.Name_) == "CaitlynPiltoverPeacemaker" || std::string(args.Name_) == "CaitlynEntrapment")
		{
			QCastTime = GGame->CurrentTick();
		}
	}
	if (args.Caster_->IsEnemy(myHero))
	{
		if (std::string(args.Name_) == "summonerflash" && GetDistance(myHero, args.Caster_) < 300 && E->IsReady() && myHero->IsValidTarget(args.Caster_, E->Range()))
		{
			E->CastOnPosition(args.EndPosition_);
		}
	}
	/*if (GSpellData->GetSlot(args.Data_) == kSlotW)
	{
		LastWTick = GGame->TickCount();
		GGame->PrintChat("Last W");
	}*/
}
PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
	if (args.Sender->IsEnemy(myHero) && args.Sender->IsHero())
	{
		if (AutoEGapcloser->Enabled() && E->IsReady() && !args.IsTargeted && myHero->IsValidTarget(args.Sender, 250))
		{
			E->CastOnPosition(args.Sender->ServerPosition());
			GOrbwalking->ResetAA();
		}
	}
}
/*PLUGIN_EVENT(void) OnPlayAnimation(IUnit* Source, std::string const Args)
{
	if (Source == myHero && Args == "Spell3" && Q->IsReady())
	{
		GGame->PrintChat("Q_first");
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		if (target !=nullptr && AlwaysQAfterE->Enabled() && myHero->IsValidTarget(target, Q->Range()))
		{
			Q->CastOnPosition(target->GetPosition());
			GGame->PrintChat("Q Second");
		}
	}
}*/
PLUGIN_EVENT(void) OnAfterAttack(IUnit* source, IUnit* target)
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		if (E->IsReady() && ComboE->Enabled() && target->IsHero())
		{
			if (target != nullptr && myHero->IsValidTarget(target, E->Range()))
			{
				AdvPredictionOutput prediction_output;
				E->RunPrediction(target, true, kCollidesWithYasuoWall | kCollidesWithMinions, &prediction_output);
				if (prediction_output.HitChance >= kHitChanceHigh)
				{
					E->CastOnTarget(target);
					GOrbwalking->ResetAA();
					if (AlwaysQAfterE->Enabled() && Q->IsReady())
					{
						Q->CastOnTarget(target);
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

		if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), RRange); }
	}
	else
	{
		if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

		if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

		if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

		if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), RRange); }
	}
}




PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GGame->IsChatOpen()) return;
	if (myHero->GetSpellBook()->GetLevel(kSlotR) > 0)
	{
		RRange = 1500 + 500 * GEntityList->Player()->GetSpellLevel(kSlotR);
	}
	if (W->IsReady() && GGame->CurrentTick() - LastWTick > 500)
	{
		if ( myHero->GetMana() > Q->ManaCost() + E->ManaCost())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			if (target != nullptr && myHero->IsValidTarget(target, W->Range()) && !target->HasBuff("caitlynyordletrapinternal"))
			{
				if (AutoW->Enabled() && !target->IsDead() && target->HasBuffOfType(BUFF_Stun) || target->HasBuffOfType(BUFF_Snare) || target->HasBuffOfType(BUFF_Knockup)
					|| target->HasBuffOfType(BUFF_Suppression) /*target->IsCastingImportantSpell()*/)
				{
					LastWTick = GGame->CurrentTick();
					W->CastOnPosition(target->ServerPosition());
				}
				if (AutoWtele->Enabled() && target->HasBuff("teleport_target"))
				{
					LastWTick = GGame->CurrentTick();
					W->CastOnPosition(target->ServerPosition());
				}
				if (AutoWmelee->Enabled() && target->IsMelee() && GetDistance(myHero, target) < target->GetRealAutoAttackRange(myHero))
				{
					LastWTick = GGame->CurrentTick();
					W->CastOnPosition(myHero->ServerPosition());
				}
			}
		}
	}
	if (GetAsyncKeyState(USEE->GetInteger()))
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
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);
	Menu();
	LoadSpells();
	myHero = GEntityList->Player();

	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
	//GEventManager->AddEventHandler(kEventOnPlayAnimation, OnPlayAnimation);
	GEventManager->AddEventHandler(kEventOnSpellCast, OnProcessSpellCast);
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);
	
	if (strcmp(GEntityList->Player()->ChampionName(), "Caitlyn") == 0)
	{
		GGame->PrintChat("D-Caitlyn : Loaded");
	}
	else
	{
		GGame->PrintChat("You are not playing Caitlyn...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	//GEventManager->RemoveEventHandler(kEventOnPlayAnimation, OnPlayAnimation);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessSpellCast);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);
}