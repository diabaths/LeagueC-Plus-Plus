// D-Jarvan.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"
#define M_PI 3.14159265358979323846





PluginSetup("D-Jarvan");

IMenu* MainMenu;
IMenu* ComboMenu;
IMenu* HarassMenu;
IMenu* FarmMenu;
IMenu* JungleMenu;
IMenu* MiscMenu;
IMenu* Drawings;
IMenu* ItemsMenu;
IMenu* PotionMenu;
IMenu* SmiteMenu;

IMenuOption* Harassitems;
IMenuOption* HarassEQ;
IMenuOption* HarassHpPercent;
IMenuOption* UseIgnitecombo;
IMenuOption* ComboQ;
IMenuOption* ComboW;
IMenuOption* ComboE;
IMenuOption* ComboR;
IMenuOption* ComboRAOEuse;
IMenuOption* HarassQ;
IMenuOption* HarassW;
IMenuOption* HarassE;
IMenuOption* HarassR;
IMenuOption* Harassammo;
IMenuOption* HarassManaPercent;
IMenuOption* FarmQ;
IMenuOption* FarmW; 
IMenuOption* FarmWManaPercent;
IMenuOption* FarmE;
IMenuOption* FarmR;
IMenuOption* Farmitems;
IMenuOption* FarmManaPercent;
IMenuOption* JungleQ;
IMenuOption* JungleE;
IMenuOption* JungleW; 
IMenuOption* JungleWManaPercent; 
IMenuOption* JungleR;
IMenuOption* Jungleitems;
IMenuOption* JungleManaPercent;

IMenuOption* smitejungle;
IMenuOption* usesmitetarget;
IMenuOption* usesmitejungle;
IMenuOption* UseIgnitekillsteal;
IMenuOption* KillstealQ;
IMenuOption* KillstealE;
IMenuOption* KillstealR;
IMenuOption* UseEQ; 
IMenuOption* UseEQW;
IMenuOption* useYoumuu;
IMenuOption* Hydra;
IMenuOption* RHydra; 
IMenuOption* _tiamat;
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
ISpell* smite;

IInventoryItem* Titanic_Hydra; 
IInventoryItem* Ravenous_Hydra; 
IInventoryItem* Tiamat;
IInventoryItem* hextech;
IInventoryItem* blade;
IInventoryItem* Cutlass;
IInventoryItem* HealthPot;
IInventoryItem* CorruptPot;
IInventoryItem* Biscuit;
IInventoryItem* RefillPot;
IInventoryItem* hunter;
IInventoryItem* Youmuu;

int lastq;
int lastr;
int _haveulti;
void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Jarvan");

	ComboMenu = MainMenu->AddMenu("Combo Settings");
	UseIgnitecombo = ComboMenu->CheckBox("Use Ignite", true);
	ComboQ = ComboMenu->CheckBox("Use Q", true);
	ComboW = ComboMenu->CheckBox("Use W", true);
	ComboE = ComboMenu->CheckBox("Use E", true);
	ComboR = ComboMenu->CheckBox("Use R", true);
	//ComboRAOEuse = ComboMenu->CheckBox("Use R if Hit 3 Enemys", true);

	HarassMenu = MainMenu->AddMenu("Harass Setting");
	Harassitems = HarassMenu->CheckBox("Use Items Jungle", true);
	HarassQ = HarassMenu->CheckBox("Use Q", true);
	HarassE = HarassMenu->CheckBox("Use E", true);
	HarassEQ = HarassMenu->CheckBox("Use EQ", true);
	HarassHpPercent = HarassMenu->AddInteger("HP Percent to Use EQ > ", 10, 100, 70);
	HarassManaPercent = HarassMenu->AddInteger("Mana Percent for harass", 10, 100, 70);

	FarmMenu = MainMenu->AddMenu("LaneClear Setting");
	FarmQ = FarmMenu->CheckBox("Use Q Farm", true);
	FarmE = FarmMenu->CheckBox("Use E Farm", true);
	FarmManaPercent = FarmMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);
	Farmitems = FarmMenu->CheckBox("Use Items Farm", true);

	JungleMenu = MainMenu->AddMenu("Jungle Setting");
	JungleQ = JungleMenu->CheckBox("Use Q Jungle", true);
	JungleW = JungleMenu->CheckBox("Use W Jungle", true);
	JungleWManaPercent = FarmMenu->AddInteger("Use W if my HP <", 10, 100, 20);
	JungleE = JungleMenu->CheckBox("Use E Jungle", true);
	JungleManaPercent = JungleMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);
	Jungleitems = JungleMenu->CheckBox("Use Items Jungle", true);

	MiscMenu = MainMenu->AddMenu("Misc Setting");
	KillstealQ = MiscMenu->CheckBox("Use Q to killsteal", true);
	KillstealE = MiscMenu->CheckBox("Use E to killsteal", true);
	KillstealR = MiscMenu->CheckBox("Use R to killsteal", true);
	UseEQ = MiscMenu->AddKey("Use EQ to Mouse", 84);
	UseEQW = MiscMenu->CheckBox("Use W if Enemy in range after the EQ ", true);

	SmiteMenu = MainMenu->AddMenu("Smite Setting");
	usesmitetarget = SmiteMenu->CheckBox("Use Smite on target", true);
	smitejungle = SmiteMenu->CheckBox("Use Smite in Jungle", true);
	usesmitejungle = SmiteMenu->AddInteger("0=Smite all Monst, 1=Smite only Epic", 0, 1, 0);
	
	ItemsMenu = MainMenu->AddMenu("Items Setting");
	useYoumuu = ItemsMenu->CheckBox("Use Youmuu's", true);
	Hydra = ItemsMenu->CheckBox("Use Titanic_Hydra", true);
	RHydra = ItemsMenu->CheckBox(" Use Ravenous_Hydras", true);
	_tiamat = ItemsMenu->CheckBox(" UseTiamat", true);
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
	DrawE = Drawings->CheckBox("Draw E", false);
	DrawR = Drawings->CheckBox("Draw R", false);
}
void LoadSpells()
{
	
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	Q->SetSkillshot(0.5f, 70.f, FLT_MAX, 770.f);

	W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	W->SetOverrideRange(600);

	E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, true, true, static_cast<eCollisionFlags> (kCollidesWithNothing));
	E->SetSkillshot(0.50f, 50.f, FLT_MAX, 830.f);

	R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, true, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	R->SetOverrideRange(650);

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

	if (strcmp(slot1, "SummonerSmite") == 0)
	{
		smite = GPluginSDK->CreateSpell(kSummonerSlot1, 570);
	}
	if (strcmp(slot2, "SummonerSmite") == 0)
	{
		smite = GPluginSDK->CreateSpell(kSummonerSlot2, 570);
	}
	else smite == nullptr;

	Youmuu = GPluginSDK->CreateItemForId(3142, 0);
	Titanic_Hydra = GPluginSDK->CreateItemForId(3748, 385);
	Ravenous_Hydra = GPluginSDK->CreateItemForId(3074, 385);
	Tiamat = GPluginSDK->CreateItemForId(3077, 385);
	hextech = GPluginSDK->CreateItemForId(3146, 700);
	blade = GPluginSDK->CreateItemForId(3153, 550);
	Cutlass = GPluginSDK->CreateItemForId(3144, 550);
	HealthPot = GPluginSDK->CreateItemForId(2003, 0);
	CorruptPot = GPluginSDK->CreateItemForId(2033, 0);
	RefillPot = GPluginSDK->CreateItemForId(2031, 0);
	Biscuit = GPluginSDK->CreateItemForId(2010, 0);
	hunter = GPluginSDK->CreateItemForId(2032, 0);
}
void GetBuffName()
{
	std::vector<void*> vecBuffs; GEntityList->Player()->GetAllBuffsData(vecBuffs); for (auto i : vecBuffs)
	{
		GBuffData->GetBuffName(i); GGame->PrintChat(GBuffData->GetBuffName(i));
	}
}
bool haveulti()
{
	if (myHero->GetSpellBook()->GetLevel(kSlotR) > 0)
	{
		return myHero->HasBuff("JarvanIVCataclysm");
	}
	return false;
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

void UseItems()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (useYoumuu->Enabled() && Youmuu->IsReady() && Youmuu->IsOwned())
			{
				if (myHero->IsValidTarget(enemy, 550))
					Youmuu->CastOnPlayer();
			}
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

			if (_tiamat->Enabled() && myHero->IsValidTarget(enemy, 385))
			{
				if (Tiamat->IsOwned() && Tiamat->IsReady())
					Tiamat->CastOnPlayer();
			}
			if (Hydra->Enabled() && myHero->IsValidTarget(enemy, 385))
			{
				if (Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady())
					Titanic_Hydra->CastOnPlayer();
			}
			if (RHydra->Enabled() && myHero->IsValidTarget(enemy, 385))
			{
				if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
					Ravenous_Hydra->CastOnPlayer();
			}
		}
	}
}
void Smiteuse()
{
	if (smite != nullptr && smite->IsReady())
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

void smitetarget()
{
	if (smite == nullptr) return;
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
void Combo()
{
	auto Ecd = myHero->GetSpellRemainingCooldown(kSlotE);
	auto Qcd = myHero->GetSpellRemainingCooldown(kSlotQ);
	smitetarget();
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

	if (ComboQ->Enabled() && ComboE->Enabled())
	{
		if (Q->IsReady() && E->IsReady() && myHero->GetMana() > Q->ManaCost() + E->ManaCost())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
			if (myHero->IsValidTarget(target, E->Range()) && target != nullptr)
			{
				AdvPredictionOutput prediction_output;
				E->RunPrediction(target, true, kCollidesWithYasuoWall | kCollidesWithMinions, &prediction_output);
				if (E->IsReady() && prediction_output.HitChance >= kHitChanceHigh)
				{
					Vec3 Enemypos;
					//auto Rstartcast = target->ServerPosition().Extend(target->ServerPosition(), 50);
					GPrediction->GetFutureUnitPosition(target, 0.5, true, Enemypos);
					E->CastOnPosition(Enemypos);
					Q->CastOnPosition(Enemypos);
				}
			}
		}
	}
	if (ComboE->Enabled() && (!Q->IsReady() || Qcd > 3) || !ComboQ->Enabled())
	{
		if (E->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());

			if (target != nullptr && myHero->IsValidTarget(target, E->Range()))
			{
				auto dmg = GDamage->GetSpellDamage(myHero, target, kSlotE);
				if (target->GetHealth() < dmg)
					E->CastOnTarget(target, kHitChanceHigh);
			}
		}
	}
	if (ComboW->Enabled())
	{
		if (W->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			if (target != nullptr)
			{
				if (myHero->IsValidTarget(target, W->Range()))
					W->CastOnPlayer();
			}
		}
	}
	if (ComboQ->Enabled())
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (target != nullptr && myHero->IsValidTarget(target, Q->Range()))
			{
				if (!E->IsReady() || Ecd > 3)
				{
					Q->CastOnTarget(target, kHitChanceHigh);
				}
				auto dmg = GDamage->GetSpellDamage(myHero, target, kSlotQ);
				if (target->GetHealth() < dmg)
				{
					Q->CastOnTarget(target, kHitChanceHigh);
				}
			}
		}
	}
	if (ComboR->Enabled() && R->IsReady())
	{
		auto Enemy = GTargetSelector->GetFocusedTarget();
		if (myHero->IsValidTarget(Enemy, R->Range()) && Enemy != nullptr)
		{
			//auto dmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotQ);
			auto Rlvl = GEntityList->Player()->GetSpellLevel(kSlotR) - 1;
			auto BaseDamage = std::vector<double>({ 200, 325, 450 }).at(Rlvl);
			auto ADMultiplier = 1.5 * GEntityList->Player()->TotalPhysicalDamage();
			auto dmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotQ);
			auto TotalD = BaseDamage + ADMultiplier;
			if (!Enemy->IsInvulnerable() && Enemy->GetHealth() < TotalD+ dmg)
			{
				R->CastOnTarget(Enemy);
			}
		}
	}
	/*if (R->IsReady() && ComboRAOEuse->Enabled())
	{
		for (auto target : GEntityList->GetAllHeros(false, true))
			if (target != nullptr &&  myHero->IsValidTarget(target, R->Range()))
			{
				R->CastOnTargetAoE(target, 3, kHitChanceLow);
			}
	}*/
}
void Forest()
{
	GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	if (Q->IsReady() && E->IsReady())
	{
		if (Q->ManaCost() + E->ManaCost() < myHero->GetMana())
		{
			E->CastOnPosition(GGame->CursorPosition());
			Q->CastOnPosition(GGame->CursorPosition());
		}
	}
	if (UseEQW->Enabled() && W->IsReady())
	{
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
		if (myHero->IsValidTarget(Enemy, W->Range()) && Enemy != nullptr)
		{
			W->CastOnPlayer();
		}
	}
}

void laneclear()
{
	for (auto minions : GEntityList->GetAllMinions(false, true, false))
	{
		if (Farmitems->Enabled())
		{
			if (_tiamat->Enabled() && myHero->IsValidTarget(minions, 385))
			{
				if (Tiamat->IsOwned() && Tiamat->IsReady())
					Tiamat->CastOnPlayer();
			}
			if (Hydra->Enabled() && myHero->IsValidTarget(minions, 385))
			{
				if (Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady())
					Titanic_Hydra->CastOnPlayer();
			}
			if (RHydra->Enabled() && myHero->IsValidTarget(minions, 385))
			{
				if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
					Ravenous_Hydra->CastOnPlayer();
			}
		}
		if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
			return;
		if (FarmQ->Enabled() && Q->IsReady())
		{
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
			{
				auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
				Q->AttackMinions();
				if (minions->GetHealth() < dmg && GetDistance(myHero, minions) > myHero->GetRealAutoAttackRange(minions))
				{
					Q->CastOnUnit(minions);
					return;
				}
			}
		}
		if (FarmE->Enabled() && E->IsReady())
		{
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
			{
				auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
				Vec3 pos;
				int hit;
				GPrediction->FindBestCastPosition(E->Range(), E->Radius(), true, true, false, pos, hit);
				if (hit >= 2)
				{
					E->CastOnPosition(pos);
					return;
				}
				if (minions->GetHealth() < dmg && GetDistance(myHero, minions) > myHero->GetRealAutoAttackRange(minions))
				{
					E->CastOnUnit(minions);
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
		if (Jungleitems->Enabled())
		{
			if (_tiamat->Enabled() && myHero->IsValidTarget(jMinion, 385))
			{
				if (Tiamat->IsOwned() && Tiamat->IsReady())
					Tiamat->CastOnPlayer();
			}
			if (Hydra->Enabled() && myHero->IsValidTarget(jMinion, 385))
			{
				if (Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady())
					Titanic_Hydra->CastOnPlayer();
			}
			if (RHydra->Enabled() && myHero->IsValidTarget(jMinion, 385))
			{
				if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
					Ravenous_Hydra->CastOnPlayer();
			}
		}
		if (myHero->ManaPercent() < JungleManaPercent->GetInteger())
			return;
		if (strstr(jMinion->GetObjectName(), "mini")) return;
		if (JungleE->Enabled() && E->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, E->Range()))
			{
				E->CastOnUnit(jMinion);
				return;
			}
		}
		if (JungleQ->Enabled() && Q->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
			{
				Q->CastOnUnit(jMinion);
				return;
			}
		}
		if (JungleW->Enabled() && W->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, W->Range()))
			{if(myHero->GetHealth() <JungleWManaPercent->GetInteger())
				W->CastOnPlayer();
				return;
			}
		}
	}
}


void Harass()
{
	if (Harassitems->Enabled())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		if (myHero->IsValidTarget(target, Q->Range()) && target != nullptr)
		{
			if (_tiamat->Enabled() && myHero->IsValidTarget(target, 385))
			{
				if (Tiamat->IsOwned() && Tiamat->IsReady())
					Tiamat->CastOnPlayer();
			}
			if (Hydra->Enabled() && myHero->IsValidTarget(target, 385))
			{
				if (Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady())
					Titanic_Hydra->CastOnPlayer();
			}
			if (RHydra->Enabled() && myHero->IsValidTarget(target, 385))
			{
				if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
					Ravenous_Hydra->CastOnPlayer();
			}
		}
	}

	if (myHero->ManaPercent() < HarassManaPercent->GetInteger())
		return;
	if (HarassQ->Enabled())
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (myHero->IsValidTarget(target, Q->Range()) && target != nullptr)
			{
				Q->CastOnTarget(target, kHitChanceHigh);
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
				{
					E->CastOnTarget(target, kHitChanceHigh);
				}
			}
		}
	}
	if (HarassEQ->Enabled())
	{
		if (Q->IsReady() && E->IsReady() && myHero->GetMana() > Q->ManaCost() + E->ManaCost())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
			if (myHero->GetHealth() > HarassHpPercent->GetInteger())
			{
				if (myHero->IsValidTarget(target, E->Range()) && target != nullptr)
				{
					AdvPredictionOutput prediction_output;
					E->RunPrediction(target, true, kCollidesWithYasuoWall | kCollidesWithMinions, &prediction_output);
					if (E->IsReady() && prediction_output.HitChance >= kHitChanceHigh)
					{
						Vec3 Enemypos;
						//auto Rstartcast = target->ServerPosition().Extend(target->ServerPosition(), 50);
						GPrediction->GetFutureUnitPosition(target, 0.5, true, Enemypos);
						E->CastOnPosition(Enemypos);
						Q->CastOnPosition(Enemypos);

					}
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
			if (KillstealE->Enabled() && E->IsReady())
			{
				auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotE);
				if (myHero->IsValidTarget(Enemy, E->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmg)
					{
						E->CastOnTarget(Enemy, kHitChanceHigh);
					}
				}
			}
			if (KillstealR->Enabled() && R->IsReady())
			{
				auto dmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotR);
				if (myHero->IsValidTarget(Enemy, R->Range()) && !Enemy->IsInvulnerable())
				{
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

PLUGIN_EVENT(void) OnCreateObject(IUnit* obj)
{
	if (strcmp(obj->GetObjectName(), "JarvanIVCataclysm") == 0)
	{
		_haveulti = true;
		GGame->PrintChat("ulti");
	}
}
PLUGIN_EVENT(void) OnDestroyObject(IUnit* obj)
{
	if (strcmp(obj->GetObjectName(), "JarvanCataclysm_tar") == 0)
	{
		_haveulti = false;
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
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		laneclear();
		jungleclear();
	}
	killsteal();
	UseItems();
	Usepotion();
	if (smitejungle->Enabled())
	{
		Smiteuse();
	}
	if (GetAsyncKeyState(UseEQ->GetInteger()))
	{
		Forest();
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
//	GEventManager->AddEventHandler(kEventOnCreateObject, OnCreateObject);
	//GEventManager->AddEventHandler(kEventOnDestroyObject, OnDestroyObject);
	if (strcmp(GEntityList->Player()->ChampionName(), "JarvanIV") == 0)
	{
		GGame->PrintChat("D-JarvanIV : Loaded");
	}
	else
	{
		GGame->PrintChat("You are not playing JarvanIV...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	//GEventManager->RemoveEventHandler(kEventOnCreateObject, OnCreateObject);
	//GEventManager->RemoveEventHandler(kEventOnDestroyObject, OnDestroyObject);

}