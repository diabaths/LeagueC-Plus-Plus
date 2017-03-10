// D-Thresh++.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"



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
IMenuOption* SemiR;
IMenuOption* UseIgnitecombo;
IMenuOption* ComboQ;
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

IUnit* myHero;

ISpell2* Q;
ISpell2* Q2;
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

int lastq;

void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Thresh");

	ComboMenu = MainMenu->AddMenu("Combo Settings");
	UseIgnitecombo = ComboMenu->CheckBox("Use Ignite", true);
	ComboQ = ComboMenu->CheckBox("Use Q", true);
	ComboW = ComboMenu->CheckBox("Use W", true);
	ComboE = ComboMenu->CheckBox("Use E", true);
	ComboR = ComboMenu->CheckBox("Use R", true);
	ComboRAOEuse = ComboMenu->CheckBox("Use R if hit 3 Enemys", false);
	Epush = ComboMenu->CheckBox("E Push/Pull (on / off)", false);
	
	HarassMenu = MainMenu->AddMenu("Harass Setting");
	HarassQ = HarassMenu->CheckBox("Use Q", true);
	HarassQ2 = HarassMenu->CheckBox("Use Q2", true);
	HarassE = HarassMenu->CheckBox("Use E", true);
	HarassManaPercent = HarassMenu->AddInteger("Mana Percent for harass", 10, 100, 70);

	EMenu = MainMenu->AddMenu("E  Setting");
	UseEpush = EMenu->AddKey("Use E to Push", 75);
	UseEpull = EMenu->AddKey("Use E to Pull", 76);
	
	FarmMenu = MainMenu->AddMenu("LaneClear Setting");
	FarmQ = FarmMenu->CheckBox("Use Q Farm", false);
	FarmE = FarmMenu->CheckBox("Use E Farm", true);
	FarmManaPercent = FarmMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	JungleMenu = MainMenu->AddMenu("Jungle Setting");
	JungleQ = JungleMenu->CheckBox("Use Q Jungle", true);
	JungleE = JungleMenu->CheckBox("Use E Jungle", true);
	JungleManaPercent = JungleMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	MiscMenu = MainMenu->AddMenu("Misc Setting");
	Uselatern = MiscMenu->AddKey("Use Latern to Ally", 84);
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
	if (ComboQ->Enabled())
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (myHero->IsValidTarget(target, Q->Range()))
			{
				AdvPredictionOutput prediction_output;
				Q->RunPrediction(target, false, kCollidesWithYasuoWall|kCollidesWithMinions, &prediction_output);
				if (prediction_output.HitChance >= kHitChanceHigh)
				{
					Q->CastOnUnit(target);
					lastq = GGame->CurrentTick();
				}
				if (myHero->IsValidTarget(target, Q2->Range()) && target->HasBuff("threshQ") && GGame->CurrentTick() - lastq > 80)
				{
					Q2->CastOnTarget(target);
					lastq = GGame->CurrentTick();
				}
			}
		}
	}
	if (ComboE->Enabled() && GGame->CurrentTick()-lastq>100)
	{
		if (E->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
			if (target != nullptr &&myHero->IsValidTarget(target, E->Range()))
			{
				if (Epush->Enabled())
				{
					E->CastOnTarget(target, kHitChanceMedium);
				}
				else E->CastOnPosition(target->GetPosition().Extend(myHero->GetPosition(), GetDistanceVectors(target->GetPosition(), myHero->GetPosition()) + 400));
			}
		}
	}
	if (ComboW->Enabled())
	{
		if (W->IsReady())
		{
			for (auto ally : GEntityList->GetAllHeros(true, false))
			{
				if (myHero->IsValidTarget(ally, W->Range()) && CountEnemiesInRange(2000) > 0)
				{
					if (ally->HealthPercent() <= 30)
						W->CastOnTarget(ally);
					else if (myHero->HealthPercent() <= 30) W->CastOnPlayer();
				}
			}
		}
	}
	if (ComboR->Enabled() && R->IsReady())
	{
		for (auto Enemy : GEntityList->GetAllHeros(false, true))
		{
			if (Enemy != nullptr && !Enemy->IsDead())
			{
				auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotR);
				if (myHero->IsValidTarget(Enemy, R->Range()) && !Enemy->IsInvulnerable())
				
				{
					if (Enemy->GetHealth() <= dmg)
					{
						R->CastOnPlayer();
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
					R->CastOnTargetAoE(Enemy, 2, kHitChanceLow);
				}
			}
		}
	}
}

void ThrowLantern()
{
	for (auto ally : GEntityList->GetAllHeros(true, false))
	{
		if (myHero->IsValidTarget(ally, W->Range()))
		{
			W->CastOnTarget(ally);
		}
	}	
}
void Harass()
{
	if (myHero->ManaPercent() < HarassManaPercent->GetInteger())
		return;
	auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
	{
		if (HarassQ->Enabled())
		{
			if (Q->IsReady())
			{
				if (GPrediction->GetCollisionFlagsForPoint(target->GetPosition()) == 0)
				if (myHero->IsValidTarget(target, Q->Range()))
					Q->CastOnTarget(target, kHitChanceHigh);
				lastq = GGame->CurrentTick();
			}
		}
		if (HarassQ2->Enabled() && GGame->CurrentTick() - lastq > 50)
		{
			if (myHero->IsValidTarget(target, Q2->Range()) && target->HasBuff("threshQ"))
				Q2->CastOnTarget(target);
			lastq = GGame->CurrentTick();

		}
	}
	if (HarassE->Enabled())
	{
		if (E->IsReady() && GGame->CurrentTick()-lastq>100)
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
			if (ImmobileQ->Enabled())
			{
				{
					Q->CastOnTarget(target, kHitChanceImmobile);
				}
			}
			if (DushQ->Enabled())
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
						Q->CastOnTarget(Enemy, kHitChanceHigh);
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

/*void SkinChanger()
{
if (myHero->GetSkinId() != ChangeSkin->GetInteger())
{
myHero->SetSkinId(ChangeSkin->GetInteger());
}
}*/

PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
	if (args.Sender->IsEnemy(myHero) && args.Sender->IsHero())
	{
		if (AutoEGapcloser->Enabled() && E->IsReady() && !args.IsTargeted && myHero->IsValidTarget(args.Sender, 300))
		{
			E->CastOnPosition(args.Sender->ServerPosition());
		}
	}
}
PLUGIN_EVENT(void) OnInterruptable(InterruptibleSpell const& Args)
{
	if(InterruptE->Enabled() && E->IsReady() && myHero->IsValidTarget(Args.Target, 300))
	{
		E->CastOnPosition(Args.Target->ServerPosition());
	}
}
PLUGIN_EVENT(void) OnGameUpdate()
{
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
	if (GetAsyncKeyState(Uselatern->GetInteger()) && W->IsReady())
	{
		ThrowLantern();
	}
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
	if (strcmp(GEntityList->Player()->ChampionName(), "Thresh") == 0)
	{
		GGame->PrintChat("D-Thresh : Loaded");
	}
	else
	{
		GGame->PrintChat("You are not playing Thresh...");
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
	
}