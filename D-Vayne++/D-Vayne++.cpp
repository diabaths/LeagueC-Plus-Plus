// D-Vayne.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"




PluginSetup("D-Vayne++");

IMenu* MainMenu;
IMenu* Qmenu;
IMenu* Emenu;
IMenu* Rmenu;
IMenu* Drawings;
IMenu* ItemsMenu;
IMenu* PotionMenu;
IMenuOption* QStealth;
IMenuOption* UseQC;
IMenuOption* UseQH;
IMenuOption* restrictq;
IMenuOption* UseQJ;
IMenuOption* KillstealQ;
IMenuOption* KillstealE;
IMenuOption* FarmManaPercent;
IMenuOption* harassManaPercent;

IMenuOption* UseEC;
IMenuOption* UseEH;
IMenuOption* Int_E;
IMenuOption* Gap_E;
IMenuOption* PushDistance;
IMenuOption* UseEaa;

IMenuOption* useYoumuu;
IMenuOption* Blade_Cutlass;
IMenuOption* MyHpPreBlade;
IMenuOption* EnemyHpPreBlade;
IMenuOption* usepotion;
IMenuOption* usepotionhpper;
IMenuOption* DrawReady;
IMenuOption* DrawQ;
IMenuOption* DrawE;

IMenuOption* UseRC;
IMenuOption* EnemyArround;

IUnit* myHero;

ISpell2* Q;
ISpell2* W;
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

void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Vayne");
	harassManaPercent = MainMenu->AddInteger("Mana Percent for Harass", 10, 100, 70);
	Qmenu = MainMenu->AddMenu("Q Settings");
	QStealth = Qmenu->AddInteger("Q Stealh Duration (0 to disable)", 0, 1000, 300);
	UseQC = Qmenu->CheckBox("Use Q Combo", true);
	UseQH = Qmenu->CheckBox("Use Q Harass", true);
	KillstealQ = Qmenu->CheckBox("Use Q Killsteal", true);
	restrictq = Qmenu->CheckBox("Restrict Q usage, false=ToMouse", true);
	UseQJ = Qmenu->CheckBox("Use Q to Farm", true);
	FarmManaPercent = Qmenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	Emenu = MainMenu->AddMenu("E Settings");
	UseEC = Emenu->CheckBox("Use E Combo", true);
	UseEH = Emenu->CheckBox("Use E Harass", true);
	KillstealE = Emenu->CheckBox("Use E Killsteal", true);
	Int_E = Emenu->CheckBox("Use E To Interrupt", true);
	Gap_E = Emenu->CheckBox("Use E To Gabcloser", true);
	PushDistance = Emenu->AddInteger("E Push Distance", 300, 475, 450);


	Rmenu = MainMenu->AddMenu("R Settings");
	UseRC = Rmenu->CheckBox("Use R in Combo", true);
	EnemyArround = Rmenu->AddInteger("Enemy Arround to use R =>", 1, 5, 2);

	ItemsMenu = MainMenu->AddMenu("Items Setting");
	Blade_Cutlass = ItemsMenu->CheckBox("Blade-Cutlass", true);
	MyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if my HP <", 10, 100, 35);
	EnemyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if Enemy HP <", 10, 100, 35);
	useYoumuu = ItemsMenu->CheckBox("Use Youmuu's", true);

	PotionMenu = MainMenu->AddMenu("Potion Setting");
	usepotion = PotionMenu->CheckBox("Use potions", true);
	usepotionhpper = PotionMenu->AddInteger("Use potions if HP <", 10, 100, 35);

	Drawings = MainMenu->AddMenu("Drawings");
	DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
	DrawQ = Drawings->CheckBox("Draw Q", false);
	DrawE = Drawings->CheckBox("Draw E", true);

}
void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, false, false, kCollidesWithNothing);
	Q->SetOverrideRange(300);

	E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, true, false, kCollidesWithNothing);
	E->SetSkillshot(0.25f, FLT_MAX, 1200.f, 550.f);

	R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, kCollidesWithNothing);
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

float GetDistance(IUnit* source, IUnit* target)
{
	auto x1 = source->GetPosition().x;
	auto x2 = target->GetPosition().x;
	auto y1 = source->GetPosition().y;
	auto y2 = target->GetPosition().y;
	auto z1 = source->GetPosition().z;
	auto z2 = target->GetPosition().z;
	return static_cast<float>(sqrt(pow((x2 - x1), 2.0) + pow((y2 - y1), 2.0) + pow((z2 - z1), 2.0)));
}

Vec3 Get3DPoint(const Vec2 position)
{
	return Vec3(position.x, GNavMesh->GetHeightForPoint(position), position.y);
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
			if (Blade_Cutlass->Enabled() && myHero->IsValidTarget(enemy, 550))
			{
				if (myHero->HealthPercent() < MyHpPreBlade->GetInteger() || enemy->HealthPercent() < EnemyHpPreBlade->GetInteger())
				{
					if (blade->IsOwned() && blade->IsReady())
						blade->CastOnTarget(enemy);
					if (Cutlass->IsOwned() && Cutlass->IsReady())
						Cutlass->CastOnTarget(enemy);
				}
				if (useYoumuu->Enabled() && Youmuu->IsReady() && Youmuu->IsOwned())
				{
					if (myHero->IsValidTarget(enemy, 550))
						Youmuu->CastOnPlayer();
				}
			}
	}
}

inline Vec2 ToVec2(Vec3 vec)
{
	return Vec2(vec.x, vec.z);
}
inline Vec3 ToVec3(Vec2 vec)
{
	return Vec3(vec.x, 0, vec.y);
}
inline float Distance(Vec3 from, Vec3 to)
{
	return (from - to).Length2D();
}
inline float Distance(IUnit* from, IUnit* to)
{
	return (from->GetPosition() - to->GetPosition()).Length2D();
}
inline float Distance(IUnit* from, Vec3 to)
{
	return (from->GetPosition() - to).Length2D();
}
inline float Distance(Vec2 from, Vec2 to)
{
	return (from - to).Length();
}
//IJava code
PLUGIN_EVENT(void) OnBeforeAttack(IUnit* target)
{
	if (target != nullptr && target->IsHero() && QStealth->GetInteger() > 0)
	{
		auto duration = QStealth->GetInteger();
		auto buff = myHero->GetBuffDataByName("vaynetumblefade");
		if (GBuffData->GetEndTime(buff) - GGame->Time() > GBuffData->GetEndTime(buff) - GBuffData->GetStartTime(buff) - duration / 1000)
		{
			GOrbwalking->DisableNextAttack();
		}
	}
}
PLUGIN_EVENT(void) OnAfterAttack(IUnit* source, IUnit* target)
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{

		if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
			return;
		int MinionDie = 0;
		for (auto minions : GEntityList->GetAllMinions(false, true, false))
		{
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
			{
				auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
				auto dmg1 = GDamage->GetAutoAttackDamage(myHero, minions, true);
				if (minions->GetHealth() <= dmg || minions->GetHealth() <= dmg1 || minions->GetHealth() <= dmg1 + dmg)
					MinionDie++;
				if (UseQJ->Enabled() && Q->IsReady())
				{
					if (MinionDie >= 1)
					{
						Q->CastOnPosition(GGame->CursorPosition());
					}
				}
			}
		}

		for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
			{

				Q->CastOnUnit(jMinion);
			}
		}
	}

	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		UseItems();
	}
	if (Q->IsReady())
	{
		auto mana = myHero->ManaPercent() > harassManaPercent->GetInteger();
		if ((GOrbwalking->GetOrbwalkingMode() == kModeCombo && UseQC->Enabled()) || (GOrbwalking->GetOrbwalkingMode() == kModeMixed && UseQH->Enabled() && mana))
		{
			if (restrictq->Enabled())
			{
				auto after = myHero->GetPosition() + (GGame->CursorPosition() - myHero->GetPosition()).VectorNormalize() * 300;
				auto disafter = Distance(after, target->ServerPosition());
				{
					auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ);
					auto dmg1 = GDamage->GetAutoAttackDamage(myHero, target, true);
					if (disafter > 630 && disafter > 150)
					{
						Q->CastOnPosition(GGame->CursorPosition());
						return;
					}
					if (Distance(target->GetPosition(), myHero->GetPosition()) > 630
						&& disafter < 630)
					{
						Q->CastOnPosition(GGame->CursorPosition());
						return;
					}
					if (target->GetHealth() < dmg + dmg1 && GetDistance(myHero, target) < Q->Range() + myHero->GetRealAutoAttackRange(target) && GetDistance(myHero, target) > myHero->GetRealAutoAttackRange(target))
					{
						Q->CastOnPosition(target->ServerPosition());
						return;
					}
					if (target->IsMelee() && GetDistance(myHero, target) < target->GetRealAutoAttackRange(myHero))
					{
						Q->CastOnPosition(myHero->ServerPosition().Extend(target->GetPosition(), -Q->Range()));
					}
				}
			}
			else
			{
				Q->CastOnPosition(GGame->CursorPosition());
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
				if (myHero->IsValidTarget(Enemy, myHero->GetRealAutoAttackRange(Enemy) + Q->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmg && Q->IsReady())
					{
						Q->CastOnPosition(Enemy->ServerPosition());
					}
				}
			}
			if (KillstealE->Enabled())
			{
				auto dmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotE);
				if (myHero->IsValidTarget(Enemy, E->Range()) && !Enemy->IsInvulnerable())
				{
					if (Enemy->GetHealth() <= dmg && E->IsReady())
					{
						E->CastOnUnit(Enemy);
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

		if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
	}
	else
	{
		if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

		if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
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
	if (args.Sender != myHero && myHero->IsValidTarget(args.Sender, E->Range())
		&& E->IsReady() && args.Sender->IsEnemy(myHero) && Gap_E->Enabled()
		&& (myHero->GetPosition() - args.EndPosition).Length() < 250)
	{
		E->CastOnUnit(args.Sender);
	}
}

PLUGIN_EVENT(void) OnInterruptable(InterruptibleSpell const& Args)
{
	if (Int_E->Enabled() && E->IsReady() && Args.DangerLevel >= kMediumDanger
		&& myHero->IsValidTarget(Args.Target, E->Range()) && (myHero->GetPosition() - Args.Target->GetPosition()).Length() < E->Range())
	{
		E->CastOnUnit(Args.Target);
	}
}
void GetBuffName()
{
	std::vector<void*> vecBuffs; GEntityList->Player()->GetAllBuffsData(vecBuffs); for (auto i : vecBuffs)
	{
		GBuffData->GetBuffName(i); GGame->PrintChat(GBuffData->GetBuffName(i));
	}
}
PLUGIN_EVENT(void) OnGameUpdate()
{	
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo  && R->IsReady())
	{
		auto enemys = EnemyArround->GetInteger();
		if (UseRC->Enabled() && CountEnemiesInRange(1500) >= enemys)
		{
			R->CastOnPlayer();
		}
	}
	killsteal();
	Usepotion();
	auto mana = myHero->ManaPercent() > harassManaPercent->GetInteger();
	if ((GOrbwalking->GetOrbwalkingMode() == kModeCombo && UseEC->Enabled()) || (GOrbwalking->GetOrbwalkingMode() == kModeMixed && UseEH->Enabled() && mana))
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, E->Range());
		if (target == nullptr || !target->IsValidTarget(GEntityList->Player(), E->Range())
			|| target->IsDead() || target->IsDashing()
			|| target->HasBuffOfType(BUFF_SpellShield)
			|| target->HasBuffOfType(BUFF_SpellImmunity)
			|| !target->IsHero())
			return;

		AdvPredictionOutput prediction_output;
		E->RunPrediction(target, false, kCollidesWithYasuoWall, &prediction_output);
		if (prediction_output.HitChance >= kHitChanceHigh)
		{
			auto pushDirection = (prediction_output.TargetPosition - myHero->GetPosition()).VectorNormalize();
			auto checkDistance = PushDistance->GetInteger() / 40;
			for (auto i = 0; i < 40; ++i)
			{
				auto finalPosition = prediction_output.TargetPosition + (pushDirection * checkDistance * i);
				if (GNavMesh->IsPointWall(finalPosition))
				{
					E->CastOnUnit(target);
				}
			}
		}
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
	GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);
	GEventManager->AddEventHandler(kEventOnGapCloser, OnGapcloser);
	GEventManager->AddEventHandler(kEventOnInterruptible, OnInterruptable);
	GEventManager->AddEventHandler(kEventOrbwalkBeforeAttack, OnBeforeAttack);
	if (strcmp(GEntityList->Player()->ChampionName(), "Vayne") == 0)
	{
		GGame->PrintChat("D-Vayne: Loaded");
	}
	else
	{
		GGame->PrintChat("You are not playing Vayne...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnAfterAttack);
    GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapcloser);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, OnInterruptable);
	GEventManager->RemoveEventHandler(kEventOrbwalkBeforeAttack, OnBeforeAttack);
}