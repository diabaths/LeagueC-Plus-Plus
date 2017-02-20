// D-Graves.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"




PluginSetup("D-Graves");

IMenu* MainMenu;
IMenu* ComboMenu;
IMenu* HarassMenu;
IMenu* Smitemenu;
IMenu* FarmMenu;
IMenu* MiscMenu;
IMenu* Drawings;
IMenu* ItemsMenu;
IMenu* PotionMenu;
IMenuOption* ComboQ;
IMenuOption* ComboW;
IMenuOption* ComboE;
IMenuOption* ComboR;
IMenuOption* ComboRAOE;
IMenuOption* ComboRAOEuse;
IMenuOption* RRange;
IMenuOption* HarassQ;
IMenuOption* HarassW;
IMenuOption* HarassManaPercent;
IMenuOption* usesmitetarget;
IMenuOption* usesmitejungle;
IMenuOption* FarmQ;
IMenuOption* FarmW;
IMenuOption* FarmE;
IMenuOption* FarmManaPercent;
IMenuOption* SemiR;
IMenuOption* KillstealQ;
IMenuOption* KillstealW;
IMenuOption* GapcloseW;
IMenuOption* Blade_Cutlass;
IMenuOption* MyHpPreBlade;
IMenuOption* EnemyHpPreBlade;
IMenuOption* useYoumuu;
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

ISpell* smite;


IInventoryItem* blade;
IInventoryItem* Cutlass;
IInventoryItem* Youmuu;
IInventoryItem* HealthPot;
IInventoryItem* CorruptPot;
IInventoryItem* Biscuit;
IInventoryItem* RefillPot;
IInventoryItem* hunter;

void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Graves");

	ComboMenu = MainMenu->AddMenu("Combo Settings");
	ComboQ = ComboMenu->CheckBox("Use Q", true);
	ComboW = ComboMenu->CheckBox("Use W", true);
	ComboE = ComboMenu->CheckBox("Use E", true);
	ComboR = ComboMenu->CheckBox("Use R if Is killable", true);
	ComboRAOEuse = ComboMenu->CheckBox("Use R if hit 3 Enemys", false);
	SemiR = ComboMenu->AddKey("Semi-Manual R", 84);
	
	HarassMenu = MainMenu->AddMenu("Harass Setting");
	HarassQ = HarassMenu->CheckBox("Use Q", true);
	HarassW = HarassMenu->CheckBox("Use W", true);
	HarassManaPercent = HarassMenu->AddInteger("Mana Percent for harass", 10, 100, 70);
	Drawings = MainMenu->AddMenu("Drawings");

	Smitemenu = MainMenu->AddMenu("Smite Setting");
	usesmitetarget = Smitemenu->CheckBox("Use Smite on target", true);
	usesmitejungle = Smitemenu->AddInteger("Smite 0=Smite all Monsters, 1=Smite only Epic", 0, 1, 0);

	FarmMenu = MainMenu->AddMenu("Farm/Jungle Setting");
	FarmQ = FarmMenu->CheckBox("Use Q Farm", true);
	FarmW = FarmMenu->CheckBox("Use W Farm", true);
	FarmE = FarmMenu->CheckBox("Use E(reload) Jungle only", true);
	FarmManaPercent = FarmMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	MiscMenu = MainMenu->AddMenu("Misc Setting");
	KillstealQ = MiscMenu->CheckBox("Use Q to killsteal", true);
	KillstealW = MiscMenu->CheckBox("Use W to killsteal", true);
	GapcloseW = MiscMenu->CheckBox("Use W to Gapclose", true);
	//Gapclose E = MiscMenu->CheckBox("Use E to Gapclose", true);

	ItemsMenu = MainMenu->AddMenu("Items Setting");
	Blade_Cutlass = ItemsMenu->CheckBox("Blade-Cutlass", true);
	MyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if my HP <", 10, 100, 35);
	EnemyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if Enemy HP <", 10, 100, 35);
	useYoumuu = ItemsMenu->CheckBox("Use Youmuu's", true);

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
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithWalls | kCollidesWithYasuoWall));
	W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, true, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall | kCollidesWithMinions));
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));

	Q->SetOverrideRange(950);
	W->SetOverrideRange(950);
	E->SetOverrideRange(450);
	R->SetOverrideRange(1500);

	Q->SetOverrideDelay(0.25);
	W->SetOverrideDelay(0.35);
	R->SetOverrideDelay(0.25);

	Q->SetOverrideRadius(60);
	W->SetOverrideRadius(150);
	R->SetOverrideRadius(100);
	Q->SetOverrideSpeed(2000);
	W->SetOverrideSpeed(1650);
	R->SetOverrideSpeed(2100);

	
	auto slot1 = GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1);
	auto slot2 = GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2);
	if (strcmp(slot1, "SummonerSmite") == 0)
	{
	smite = GPluginSDK->CreateSpell(kSummonerSlot2, 570);
	}
	if (strcmp(slot2, "SummonerSmite") == 0)
	{
	smite = GPluginSDK->CreateSpell(kSummonerSlot2, 570);
	}

	blade = GPluginSDK->CreateItemForId(3153, 550);
	Cutlass = GPluginSDK->CreateItemForId(3144, 550);
	Youmuu = GPluginSDK->CreateItemForId(3142, 0);
	
	HealthPot = GPluginSDK->CreateItemForId(2003, 0);
	CorruptPot = GPluginSDK->CreateItemForId(2033, 0);
	RefillPot = GPluginSDK->CreateItemForId(2031, 0);
	Biscuit = GPluginSDK->CreateItemForId(2010, 0);
	hunter = GPluginSDK->CreateItemForId(2032, 0);
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

void smitetarget()
{
	if (smite->GetSpellSlot() == kSlotUnknown) return;
	if (!usesmitetarget->Enabled() || !smite->IsReady()) return;
	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && myHero->IsValidTarget(enemy, 570))
		{
			auto Dmg = GDamage->GetSummonerSpellDamage(myHero, enemy, kSummonerSpellSmite);

			smite->CastOnUnit(enemy);
		}
	}
}
void Smiteuse()
{
	if (smite->GetSpellSlot() != kSlotUnknown && smite->IsReady())
	{
		auto minions = GEntityList->GetAllMinions(false, false, true);
		for (IUnit* minion : minions)
		{
			auto smitestage = usesmitejungle->GetInteger();
			if (smitestage == 0)
			{
				if (strstr(minion->GetObjectName(), "Blue") || strstr(minion->GetObjectName(), "Gromp")
					|| strstr(minion->GetObjectName(), "Murkwolf") || strstr(minion->GetObjectName(), "Razorbeak")
					|| strstr(minion->GetObjectName(), "RiftHerald") || strstr(minion->GetObjectName(), "Red")
					|| strstr(minion->GetObjectName(), "Krug") || strstr(minion->GetObjectName(), "Dragon")
					|| strstr(minion->GetObjectName(), "Baron"))
				{
					auto Dmg = GDamage->GetSummonerSpellDamage(myHero, minion, kSummonerSpellSmite);
					if (minion != nullptr && !minion->IsDead() && minion->GetHealth() <= Dmg && myHero->IsValidTarget(minion, 570))
					{
						smite->CastOnUnit(minion);
					}
				}
			}
			if (smitestage == 1)
			{
				if (strstr(minion->GetObjectName(), "RiftHerald") || strstr(minion->GetObjectName(), "Dragon")
					|| strstr(minion->GetObjectName(), "Baron"))
				{
					auto Dmg = GDamage->GetSummonerSpellDamage(myHero, minion, kSummonerSpellSmite);
					if (minion != nullptr && !minion->IsDead() && minion->GetHealth() <= Dmg && myHero->IsValidTarget(minion, 570))
					{
						smite->CastOnUnit(minion);
					}
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
			if (enemy != nullptr)
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
}

void Combo()
{
	smitetarget();
	if (ComboR->Enabled() && R->IsReady())
	{
		for (auto Enemy : GEntityList->GetAllHeros(false, true))
		{
			if (Enemy != nullptr && !Enemy->IsDead())
			{
				auto Rlvl = GEntityList->Player()->GetSpellLevel(kSlotR) - 1;
				auto BaseDamage = std::vector<double>({ 250, 400, 550 }).at(Rlvl);
				auto ADMultiplier = 1.25 * GEntityList->Player()->BonusDamage();
				auto TotalD = BaseDamage + ADMultiplier;
				if (myHero->IsValidTarget(Enemy, R->Range()) && !Enemy->IsInvulnerable()
					&& GetDistance(myHero, Enemy) >= 800)
				{
					if (Enemy->GetHealth() <= TotalD && R->IsReady())
					{
						R->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}
		}
	}

	if (R->IsReady() && ComboRAOEuse->Enabled())
	{
		for (auto target : GEntityList->GetAllHeros(false, true))
			if (target != nullptr &&  myHero->IsValidTarget(target, R->Range()))
			{
				R->CastOnTargetAoE(target, 3, kHitChanceLow);
			}
	}
}

PLUGIN_EVENT(void) OnAfterAttack(IUnit* source, IUnit* target)
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo )
	{
		if (source == myHero || target != nullptr)
		{
			auto useQ = ComboQ->Enabled();
			auto useW = ComboW->Enabled();
			if (useQ)
			{
				if (Q->IsReady())
				{
					auto t = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
					if (t != nullptr &&  myHero->IsValidTarget(t, Q->Range()))
						Q->CastOnTarget(t, kHitChanceHigh);
				}
			}
			if (useW)
			{
				if (W->IsReady())
				{
					auto t = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
					if (t != nullptr &&  myHero->IsValidTarget(t, W->Range()))
						W->CastOnTarget(t, kHitChanceHigh);
				}
			}
		}		
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed && myHero->ManaPercent() > HarassManaPercent->GetInteger())
	{
		if (source == myHero || target != nullptr)
		{
			auto useQ = HarassQ->Enabled();
			auto useW = HarassW->Enabled();
			if (useQ)
			{
				if (Q->IsReady())
				{
					auto t = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
					if (t != nullptr &&  myHero->IsValidTarget(t, Q->Range()))
						Q->CastOnTarget(t, kHitChanceHigh);
				}
			}
			if (useW)
			{
				if (W->IsReady())
				{
					auto t = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
					if (t != nullptr &&  myHero->IsValidTarget(t, W->Range()))
						W->CastOnTarget(t, kHitChanceHigh);
				}
			}
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && ComboE->Enabled())
	{
		if (source == myHero || target != nullptr)
		if (!myHero->GetBuffDataByName("GravesBasicAttackAmmo2") && E->IsReady())
		{
			auto t = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (t != nullptr &&  myHero->IsValidTarget(t, Q->Range()))
			E->CastOnPosition(GGame->CursorPosition());
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
			return;
		for (auto minions : GEntityList->GetAllMinions(false, true, false))
		{
			if (FarmQ->Enabled() && Q->IsReady())
			{
				if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
				{
					Q->CastOnUnit(minions);
				}
				else Q->LastHitMinion();
			}
			if (FarmW->Enabled() && W->IsReady())
			{
				if (minions != nullptr && myHero->IsValidTarget(minions, W->Range()))
				{
					W->CastOnUnit(minions);
				}
				else W->LastHitMinion();
			}
		}
		for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
		{
			if (FarmQ->Enabled() && Q->IsReady())
			{
				if (jMinion != nullptr && myHero->IsValidTarget(jMinion, Q->Range()))
				{
					Q->CastOnUnit(jMinion);
				}
			}
			if (FarmW->Enabled() && W->IsReady())
			{
				if (jMinion != nullptr && myHero->IsValidTarget(jMinion, W->Range()))
				{
					W->CastOnUnit(jMinion);
				}
			}
			if (FarmE->Enabled() && E->IsReady())
			{
				if (jMinion != nullptr && myHero->IsValidTarget(jMinion, 500))
				{
					E->CastOnPosition(GGame->CursorPosition());
				}
			}
		}
	}
}
/*void Harass()
{
	if (myHero->ManaPercent() < HarassManaPercent->GetInteger())
		return;
	if (HarassQ->Enabled())
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (target->IsValidTarget(myHero, Q->Range()))
				Q->CastOnTarget(target, kHitChanceHigh);
		}
	}
	if (HarassW->Enabled())
	{
		if (W->IsReady() && !Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			if (target->IsValidTarget(myHero, W->Range()))
				W->CastOnTarget(target, kHitChanceHigh);
		}
	}
}*/

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

static bool InFountain(IUnit *unit)
{
	//TODO: Implement
	return unit->HasBuff("kappachino");
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


PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
	if (args.Sender->IsEnemy(myHero) && args.Sender->IsHero())
	{
		if (GapcloseW->Enabled() && W->IsReady() && !args.IsTargeted)
		{
			auto t = args.Sender;
			if (myHero->IsValidTarget(t, W->Range()))
				if (!t->IsMelee())
				{
					W->CastOnTarget(args.Sender);
				}
				else W->CastOnPlayer();
		}
	}
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GetAsyncKeyState(SemiR->GetInteger()) && R->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());
		if (target != nullptr && myHero->IsValidTarget(target, R->Range()))
		{
			R->CastOnTarget(target, kHitChanceHigh);
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		Combo();
	}

	killsteal();
	UseItems();
	Usepotion();
	Smiteuse();
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
	GEventManager->AddEventHandler(kEventOnGapCloser, OnGapcloser);

	if (strcmp(GEntityList->Player()->ChampionName(), "Graves") == 0)
	{
		GGame->PrintChat("D-Graves : Loaded");
	}
	else
	{
		GGame->PrintChat("You are not playing Graves...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);	
	GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapcloser);
}