// D-Jayce.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"
#define M_PI 3.14159265358979323846



PluginSetup("D-Jayce");

IMenu* MainMenu;
IMenu* ComboMenu;
IMenu* HarassMenu;
IMenu* FarmMenu;
IMenu* JungleMenu;
IMenu* SmiteMenu;
IMenu* HealMenu;
IMenu* MiscMenu;
IMenu* Drawings;
IMenu* ItemsMenu;
IMenu* PotionMenu;
IMenuOption* useIgnite;
IMenuOption* ComboQ;
IMenuOption* ComboW;
IMenuOption* ComboE;
IMenuOption* ComboR;
IMenuOption* ComboQmelee;
IMenuOption* ComboWmelee;
IMenuOption* ComboEmelee;
IMenuOption* usemaleeEtokill;
IMenuOption* HarassQ;
IMenuOption* HarassW;
IMenuOption* HarassE;
IMenuOption* HarassManaPercent;

IMenuOption* FarmQ;
IMenuOption* FarmW;
IMenuOption* FarmManaPercent;

IMenuOption* smitejungle;
IMenuOption* usesmitetarget;
IMenuOption* usesmitejungle;

IMenuOption* JungleQ;
IMenuOption* JungleW;
IMenuOption* JungleE;
IMenuOption* JungleQmelee;
IMenuOption* JungleWmelee;
IMenuOption* JungleEmelee;
IMenuOption* JungleAutoswitch;
IMenuOption* JungleManaPercent;

IMenuOption* USEQE;
IMenuOption* Fleemode;
IMenuOption* KillstealQ;
IMenuOption* KillstealW;
IMenuOption* GapcloseE;
IMenuOption* InterruptE;
IMenuOption* Blade_Cutlass;
IMenuOption* MyHpPreBlade;
IMenuOption* EnemyHpPreBlade;
IMenuOption* useYoumuus;
IMenuOption* usepotion;
IMenuOption* usepotionhpper;
IMenuOption* DrawReady;
IMenuOption* DrawQ;
IMenuOption* DrawW;
IMenuOption* DrawE;
IMenuOption* DrawQM;
IMenuOption* DrawWM;
IMenuOption* DrawEM;
IMenuOption* DrawQEx;

IUnit* myHero;

ISpell2* Q;
ISpell2* QExtend;
ISpell2* W;
ISpell2* E;
ISpell2* QM;
ISpell2* WM;
ISpell2* EM;
ISpell2* R;

ISpell* smite;
ISpell* Ignite;

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
	MainMenu = GPluginSDK->AddMenu("D-Jayce++");

	ComboMenu = MainMenu->AddMenu("Combo Settings");
	useIgnite = ComboMenu->CheckBox("Use Ignite", true);
	ComboQ = ComboMenu->CheckBox("Use Q", true);
	ComboW = ComboMenu->CheckBox("Use W", true);
	ComboE = ComboMenu->CheckBox("Use E", true);
	ComboQmelee = ComboMenu->CheckBox("Use Q Melee", true);
	ComboWmelee = ComboMenu->CheckBox("Use W Melee", true);
	ComboEmelee = ComboMenu->CheckBox("Use E Melee", true);
	usemaleeEtokill = ComboMenu->CheckBox("Use E Melee only to kill", true);
	ComboR = ComboMenu->CheckBox("Use R", true);



	HarassMenu = MainMenu->AddMenu("Harass Setting");
	HarassQ = HarassMenu->CheckBox("Use Q", true);
	HarassW = HarassMenu->CheckBox("Use W", true);
	HarassE = HarassMenu->CheckBox("Use E", true);
	HarassManaPercent = HarassMenu->AddInteger("Mana Percent for harass", 10, 100, 70);
	Drawings = MainMenu->AddMenu("Drawings");

	FarmMenu = MainMenu->AddMenu("Farm Lane Setting");
	FarmQ = FarmMenu->CheckBox("Use Q Range", true);
	FarmW = FarmMenu->CheckBox("Use W Range", false);
	FarmManaPercent = FarmMenu->AddInteger("if Mana Percent", 10, 100, 70);

	JungleMenu = MainMenu->AddMenu("Jungle Setting");
	JungleQ = JungleMenu->CheckBox("Use Q Jungle", true);
	JungleW = JungleMenu->CheckBox("Use W Jungle", true);
	JungleE = JungleMenu->CheckBox("Use E Jungle", true);
	JungleQmelee = JungleMenu->CheckBox("Use  Melee Q Jungle", true);
	JungleWmelee = JungleMenu->CheckBox("Use Melee W Jungle", true);
	JungleEmelee = JungleMenu->CheckBox("Use Melee E Jungle", true);
	JungleAutoswitch = JungleMenu->CheckBox("Auto Switch Form", true);
	JungleManaPercent = JungleMenu->AddInteger("if Mana % >", 10, 100, 70);

	SmiteMenu = MainMenu->AddMenu("Smite Setting");
	usesmitetarget = SmiteMenu->CheckBox("Use Smite on target", true);
	smitejungle = SmiteMenu->CheckBox("Use Smite in Jungle", true);
	usesmitejungle = SmiteMenu->AddInteger("0=Smite all Monst, 1=Smite only Epic", 0, 1, 0);

	MiscMenu = MainMenu->AddMenu("Misc Setting");
	Fleemode = MiscMenu->AddKey("Flee Mode", 75);
	USEQE = MiscMenu->AddKey("Use EQ to Target", 84);
	KillstealQ = MiscMenu->CheckBox("EQ or Q to killsteal", true);
	GapcloseE = MiscMenu->CheckBox("Use E to Gapclose", true);
	InterruptE = MiscMenu->CheckBox("Use E to Interrupt", true);

	ItemsMenu = MainMenu->AddMenu("Items Setting");
	useYoumuus = ItemsMenu->CheckBox("Use Youmuus", true);
	Blade_Cutlass = ItemsMenu->CheckBox("Blade-Cutlass", true);
	MyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if my HP <", 10, 100, 35);
	EnemyHpPreBlade = ItemsMenu->AddInteger("Use Blade-Cutlass if Enemy HP <", 10, 100, 35);


	PotionMenu = MainMenu->AddMenu("Potion Setting");
	usepotion = PotionMenu->CheckBox("Use potions", true);
	usepotionhpper = PotionMenu->AddInteger("Use potions if HP <", 10, 100, 35);

	DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
	DrawQEx = Drawings->CheckBox("Draw Q Extend", true);
	DrawQ = Drawings->CheckBox("Draw Q ", true);
	DrawW = Drawings->CheckBox("Draw W ", false);
	DrawE = Drawings->CheckBox("Draw E ", false);
	DrawQM = Drawings->CheckBox("Draw Q Hummer", true);
	DrawWM = Drawings->CheckBox("Draw W Hummer", false);
	DrawEM = Drawings->CheckBox("Draw E Hummer", false);

}
void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall));
	Q->SetSkillshot(0.25f, 79.f, 1200.f, 1050.f);

	QExtend = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall));
	QExtend->SetSkillshot(0.35f, 98.f, 1900.f, 1650.f);

	W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));

	E = GPluginSDK->CreateSpell2(kSlotE, kCircleCast, false, false, static_cast<eCollisionFlags> (kCollidesWithNothing));
	E->SetSkillshot(0.1f, 120.f, FLT_MAX, 650.f);

	QM = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	QM->SetOverrideRange(600);

	WM = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	WM->SetSkillshot(0.50f, 300.f, FLT_MAX, 350.f);

	EM = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	EM->SetSkillshot(0.50f, 260, FLT_MAX, 240.f);

	R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));

	auto slot1 = GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1);
	auto slot2 = GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2);
	if (strcmp(slot1, "SummonerSmite") == 0)
	{
		smite = GPluginSDK->CreateSpell(kSummonerSlot1, 570);
	}
	else if (strcmp(slot2, "SummonerSmite") == 0)
	{
		smite = GPluginSDK->CreateSpell(kSummonerSlot2, 570);
	}
	else smite == nullptr;

	if (strcmp(slot1, "SummonerDot") == 0)
	{
		Ignite = GPluginSDK->CreateSpell(kSummonerSlot1, 600);
	}
	else if (strcmp(slot2, "SummonerDot") == 0)
	{
		Ignite = GPluginSDK->CreateSpell(kSummonerSlot2, 600);
	}
	else Ignite == nullptr;

	blade = GPluginSDK->CreateItemForId(3153, 550);
	Cutlass = GPluginSDK->CreateItemForId(3144, 550);
	Youmuu = GPluginSDK->CreateItemForId(3142, 0);

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

void GetBuffName()
{
	std::vector<void*> vecBuffs; GEntityList->Player()->GetAllBuffsData(vecBuffs); for (auto i : vecBuffs)
	{
		GBuffData->GetBuffName(i); GGame->PrintChat(GBuffData->GetBuffName(i));
	}
}
float GetDistance(IUnit* Player, IUnit* target)
{
	return (Player->GetPosition() - target->GetPosition()).Length2D();
}

bool IsMelee()
{
	return myHero->HasBuff("JayceStanceHammer");
	/*if (myHero->GetSpellBook()->GetLevel(kSlotQ) > 0)
	{
	return !strcmp(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ), "jayceshockblast") == 0;
	}*/
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
void Smiteuse()
{
	if (smite == nullptr || !smite->IsReady()) return;
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


void Laneclear()
{
	auto mana = myHero->ManaPercent() > FarmManaPercent->GetInteger();
	for (auto minions : GEntityList->GetAllMinions(false, true, false))
	{
		if (mana)
		{
			if (!IsMelee())
			{
				if (Q->IsReady() && FarmQ->Enabled() && myHero->IsValidTarget(minions, Q->Range()))
				{
					auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
					Vec3 pos;
					int count;
					Q->FindBestCastPosition(true, true, pos, count);

					if (count >= 3)
					{
						Q->CastOnPosition(pos);
					}
					else if (!myHero->GetRealAutoAttackRange(minions) && minions->GetHealth() < dmg)
					{
						Q->CastOnUnit(minions);
					}

				}
				if (W->IsReady() && FarmW->Enabled())
				{
					Vec3 pos;
					int count;
					E->FindBestCastPosition(true, true, pos, count);
					if (count >= 3)
					{
						W->CastOnPlayer();
					}
				}
			}
		}
	}
}

void Jungle()
{
	auto mana = myHero->ManaPercent() > JungleManaPercent->GetInteger();
	for (auto minions : GEntityList->GetAllMinions(false, false, true))
	{
		if (minions == nullptr || myHero->IsValidTarget(minions, Q->Range())) return;
		if (mana)
		{
			if (IsMelee())
			{
				if (QM->IsReady() && JungleQmelee->Enabled() && myHero->IsValidTarget(minions, QM->Range()) && !strstr(minions->GetObjectName(), "mini"))
				{
					QM->CastOnUnit(minions);
				}
				if (WM->IsReady() && JungleWmelee->Enabled() && myHero->IsValidTarget(minions, WM->Range()) && !strstr(minions->GetObjectName(), "mini"))
				{
					WM->CastOnPlayer();
				}
				if (EM->IsReady() && JungleEmelee->Enabled() && myHero->IsValidTarget(minions, EM->Range()) && !strstr(minions->GetObjectName(), "mini"))
				{
					if (!myHero->GetBuffCount("jaycestaticfield") && !myHero->HasBuff("jaycestaticfield"))
					{
						EM->CastOnUnit(minions);
					}
				}
				if (JungleAutoswitch->Enabled() && R->IsReady() && !QM->IsReady() && !WM->IsReady() && !EM->IsReady() && !myHero->GetBuffCount("jaycestaticfield"))
				{
					{
						R->CastOnPlayer();
					}
				}
			}
			if (!IsMelee())
			{
				if (JungleQ->Enabled() && Q->IsReady() && !strstr(minions->GetObjectName(), "mini"))
				{
					if (myHero->IsValidTarget(minions, Q->Range()))
					{
						Q->CastOnUnit(minions);
					}
				}
				if (JungleW->Enabled() && mana && W->IsReady() && !strstr(minions->GetObjectName(), "mini"))
				{
					if (myHero->IsValidTarget(minions, E->Range()))
					{
						W->CastOnPlayer();
					}
				}
				if (JungleAutoswitch->Enabled() && !Q->IsReady() && !W->IsReady() && !myHero->GetBuffCount("jaycehyperchargevfx") && !myHero->HasBuff("jaycehyperchargevfx"))
				{
					if (R->IsReady())
					{
						R->CastOnPlayer();
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
				if (useYoumuus->Enabled() && Youmuu->IsReady() && Youmuu->IsOwned())
				{
					if (myHero->IsValidTarget(enemy, 550))
						Youmuu->CastOnPlayer();
				}
			}
		}
	}
}
static Vec3 Extend(const Vec3 &from, const Vec3 &to, float distance)
{
	return from + (distance * (to - from).VectorNormalize());
}
void castEQmouse()
{
	GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());

	if (IsMelee() && R->IsReady())
	{
		R->CastOnPlayer();
	}
	if (Q->IsReady() && E->IsReady() && myHero->GetMana() > Q->ManaCost() + E->ManaCost())
	{
		auto Putgate = myHero->ServerPosition().Extend(GGame->CursorPosition(), 200);
		E->CastOnPosition(Putgate);
		Q->CastOnPosition(GGame->CursorPosition());
	}
}
void CastQextend()
{
	auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, QExtend->Range());
	if (target == nullptr) return;
	auto  castposition = myHero->GetPosition().Extend(target->GetPosition(), 200);
	AdvPredictionOutput prediction_output;
	QExtend->RunPrediction(target, true, kCollidesWithYasuoWall | kCollidesWithMinions, &prediction_output);

	if (prediction_output.HitChance >= kHitChanceMedium)
	{
		if (Q->IsReady() && myHero->IsValidTarget() && GetDistance(myHero, target)< QExtend->Range())
		{
			E->CastOnPosition(castposition);
		}
		QExtend->CastOnTarget(target, kHitChanceCollision);
	}
}
void Combo()
{
	smitetarget();
	if (Ignite != nullptr)
	{
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
		if (useIgnite->Enabled() && Ignite->IsReady())
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
	if (IsMelee())
	{
		if (ComboQmelee->Enabled())
		{
			if (QM->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
				if (target != nullptr &&  target->IsValidTarget() && GetDistance(myHero, target) <= QM->Range() + QM->Radius())
					QM->CastOnTarget(target);
			}
		}
		if (ComboWmelee->Enabled())
		{
			if (WM->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());
				if (target != nullptr && myHero->IsValidTarget(target, W->Range()))
					WM->CastOnPlayer();
			}
		}
		if (ComboEmelee->Enabled())
		{
			if (EM->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, EM->Range());
				if (target != nullptr && myHero->IsValidTarget(target, EM->Range()) && GetDistance(myHero, target) <= EM->Range() + EM->Radius())
				{
					auto dmge = GDamage->GetSpellDamage(myHero, target, kSlotE);
					if (usemaleeEtokill->Enabled() && target->GetHealth() < dmge +30)
					{
						EM->CastOnTarget(target);
					}
					else if (!usemaleeEtokill->Enabled() && (target->GetHealth() < dmge +30 || (!myHero->GetBuffCount("jaycestaticfield") && !myHero->HasBuff("jaycestaticfield"))))
					{
						EM->CastOnTarget(target);

					}
				}
			}
		}
	}

	if (!IsMelee())
	{
		if (ComboE->Enabled() && ComboQ->Enabled())
		{
			if (Q->IsReady() && E->IsReady() && myHero->GetMana() > Q->ManaCost() + E->ManaCost())
			{
				CastQextend();
			}
		}
		if (ComboQ->Enabled())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (target == nullptr) return;
			if (Q->IsReady() && myHero->GetMana() > Q->ManaCost())
			{
				auto dmg = GDamage->GetSpellDamage(myHero, target, kSlotQ);
				if (myHero->IsValidTarget(target, Q->Range()))
				{
					if (!E->IsReady() || !ComboE->Enabled() || target->GetHealth() < dmg || myHero->GetMana() < Q->ManaCost() + E->ManaCost())
					{
						if(GPrediction->GetCollisionFlagsForPoint(target->GetPosition()) == 0)
						Q->CastOnTarget(target, kHitChanceMedium);
					}
				}
			}
		}
		if (ComboW->Enabled())
		{
			if (W->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
				if (myHero->IsValidTarget(target, 500) && target != nullptr && !myHero->GetBuffCount("jaycehyperchargevfx"))
				{
					W->CastOnPlayer();
				}
			}
		}
	}

	if (ComboR->Enabled() && R->IsReady())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, QExtend->Range());
		if (target != nullptr && myHero->IsValidTarget(target, QExtend->Range()))
		{
			if (IsMelee())
			{
				if ((Q->IsReady() && W->IsReady() && E->IsReady()) || GetDistance(myHero, target) > QM->Range()+50)
				{
					R->CastOnPlayer();
				}
				if (!QM->IsReady() && !WM->IsReady() && (!EM->IsReady() || (EM->IsReady() && usemaleeEtokill->Enabled()) && GetDistance(myHero, target)>EM->Radius()))
				{
					R->CastOnPlayer();
				}
			}
			if (!myHero->GetBuffCount("jaycehyperchargevfx") && !myHero->HasBuff("jaycehyperchargevfx") && (!Q->IsReady() || !ComboQ->Enabled()) && (!W->IsReady() || !ComboW->Enabled())
				&& R->IsReady() && !IsMelee() && myHero->IsValidTarget(target, QM->Range()))
			{
				R->CastOnPlayer();
			}
			if (GetDistance(myHero, target) > QM->Range() + 50 && R->IsReady() && !IsMelee() && W->IsReady() && QM->IsReady() && !Q->IsReady())
			{
				W->CastOnPlayer();
				R->CastOnPlayer();
				QM->CastOnUnit(target);
			}
		}
	}
}

void Harass()
{
	if (myHero->ManaPercent() < HarassManaPercent->GetInteger())
		return;
	if (IsMelee()) return;
	if (HarassQ->Enabled() && HarassE->Enabled())
	{
		if (Q->IsReady() && E->IsReady() && myHero->GetMana() > Q->ManaCost() + E->ManaCost())
		{
			CastQextend();
		}
	}
	if (HarassQ->Enabled())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		if (target == nullptr) return;
		if (Q->IsReady() && myHero->GetMana() > Q->ManaCost())
		{
			if (myHero->IsValidTarget(target, Q->Range()))
			{
				if (!E->IsReady() || !ComboE->Enabled())
				{
					Q->CastOnTarget(target, kHitChanceCollision);
				}
			}
		}
	}
	if (HarassW->Enabled())
	{
		if (W->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			if (myHero->IsValidTarget(target, 500) && target != nullptr && !myHero->GetBuffCount("jaycehyperchargevfx"))
			{
				W->CastOnPlayer();
			}
		}
	}
}

void killsteal()
{
	if (GGame->IsChatOpen() || !KillstealQ->Enabled()) return;
	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
		if (Enemy != nullptr && !Enemy->IsDead() && myHero->IsValidTarget(Enemy, QExtend->Range()))
		{
			auto Qlvl = GEntityList->Player()->GetSpellLevel(kSlotQ) - 1;
			auto EQDamage = std::vector<double>({ 70, 120, 170, 220, 270, 320 }).at(Qlvl) + 1.6 * myHero->PhysicalDamage();;
			auto QDamage = std::vector<double>({ 70, 120, 170, 220, 270, 320 }).at(Qlvl) + 1.2 * myHero->PhysicalDamage();;

			if (Q->IsReady() && E->IsReady() && myHero->GetMana() > Q->ManaCost() + E->ManaCost())
			{
				if (EQDamage > Enemy->GetHealth())
				{
					if (IsMelee() && R->IsReady() && GetDistance(myHero, Enemy) > 500)
					{
						R->CastOnPlayer();
					}
					else if (!IsMelee())
					{
						CastQextend();
					}
				}
			}
			if (myHero->IsValidTarget(Enemy, Q->Range()))
			{
				if (!E->IsReady() && Enemy->GetHealth() < QDamage && myHero->GetMana() > Q->ManaCost())
				{
					if (EQDamage > Enemy->GetHealth())
					{
						if (IsMelee() && R->IsReady() && GetDistance(myHero, Enemy) > 500)
						{
							R->CastOnPlayer();
						}
						else if (!IsMelee())
						{
							Q->CastOnTarget(Enemy, kHitChanceCollision);
						}
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

void FleeMode()
{
	GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	if (!IsMelee())
	{
		if (E->IsReady())
			E->CastOnPosition(myHero->GetPosition().Extend(GGame->CursorPosition(), 150));
		else if (R->IsReady())
			R->CastOnPlayer();
	}
	else
	{
		if (QM->IsReady())
		{
			auto minions = GEntityList->GetAllMinions(false, true, true);
			for (IUnit* minion : minions)
			{
				if (minion != nullptr || myHero->IsValidTarget(minion, QM->Range()))
				{
					if (Distance(minion, GGame->CursorPosition()) + 200 < Distance(myHero, GGame->CursorPosition()))
						QM->CastOnTarget(minion);
				}
			}
			for (auto Enemy : GEntityList->GetAllHeros(false, true))
				if (Enemy != nullptr || myHero->IsValidTarget(Enemy, QM->Range()))
				{
					if (Distance(Enemy, GGame->CursorPosition()) + 200 < Distance(myHero, GGame->CursorPosition()))
						QM->CastOnTarget(Enemy);
				}
		}
		if (R->IsReady())
			R->CastOnPlayer();
	}
	if (R->IsReady())
		R->CastOnPlayer();
}
	

PLUGIN_EVENT(void) OnRender()
{
	if (DrawReady->Enabled())
	{
		if (!IsMelee())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (Q->IsReady() && E->IsReady() && DrawQEx->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), QExtend->Range()); }

			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
		}
		else
		{
			if (QM->IsReady() && DrawQM->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), QM->Range()); }

			if (WM->IsReady() && DrawWM->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), WM->Range()); }

			if (EM->IsReady() && DrawEM->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), EM->Range()); }
		}
	}
	else
	{
		if (!IsMelee())
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (DrawQEx->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), QExtend->Range()); }

			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }

			if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }
		}
		else
		{
			if (DrawQM->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), QM->Range()); }

			if (DrawWM->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), WM->Range()); }

			if (DrawEM->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), EM->Range()); }
		}
	}
}

PLUGIN_EVENT(void) OnGapcloser(GapCloserSpell const& args)
{
	if (args.Source->IsEnemy(myHero) && args.Source->IsHero())
	{
		if (GapcloseE->Enabled() && EM->IsReady() && !args.IsTargeted && myHero->IsValidTarget(args.Source, 300))
		{
			if (IsMelee() && R->IsReady())
			{
				R->CastOnPlayer();
			}
			else	EM->CastOnTarget(args.Source);
		}
	}
}
PLUGIN_EVENT(void) OnInterruptable(InterruptibleSpell const& Args)
{
	if (InterruptE->Enabled() && E->IsReady() && myHero->IsValidTarget(Args.Source, 300))
	{
		if (IsMelee() && R->IsReady())
		{
			R->CastOnPlayer();
		}
		else	EM->CastOnTarget(Args.Source);

	}
}
PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GetAsyncKeyState(USEQE->GetInteger()))
	{
		castEQmouse();
	}
	if (GetAsyncKeyState(Fleemode->GetInteger()))
	{
		FleeMode();
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
		Laneclear();
		Jungle();
	}
	killsteal();
	UseItems();
	Usepotion();
	//GetBuffName();

	if (smitejungle->Enabled())
	{
		Smiteuse();
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
	GEventManager->AddEventHandler(kEventOnGapCloser, OnGapcloser);
	GEventManager->AddEventHandler(kEventOnInterruptible, OnInterruptable);

	if (strcmp(GEntityList->Player()->ChampionName(), "Jayce") == 0)
	{
		GGame->PrintChat("D-Jayce : Loaded");
	}
	else
	{
		GGame->PrintChat("You are not playing Jayce...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapcloser);
	GEventManager->RemoveEventHandler(kEventOnInterruptible, OnInterruptable);
}