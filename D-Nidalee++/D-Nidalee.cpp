// D-Nidalee.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"
#define M_PI 3.14159265358979323846



PluginSetup("D-Nidalee");

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
IMenuOption* ComboQCougar;
IMenuOption* ComboWCougar;
IMenuOption* ComboECougar;

IMenuOption* HarassQ;
IMenuOption* HarassW;
IMenuOption* HarassManaPercent;

IMenuOption* FarmQ;
IMenuOption* FarmW;
IMenuOption* FarmE;
IMenuOption* FarmQCougar;
IMenuOption* FarmWCougar;
IMenuOption* FarmECougar;
IMenuOption* FarmAutoswitch;
IMenuOption* FarmManaPercent;

IMenuOption* smitejungle;
IMenuOption* usesmitetarget;
IMenuOption* usesmitejungle;

IMenuOption* JungleQ;
IMenuOption* JungleW;
IMenuOption* JungleE;
IMenuOption* JungleQCougar;
IMenuOption* JungleWCougar;
IMenuOption* JungleECougar;
IMenuOption* JungleAutoswitch;
IMenuOption* JungleManaPercent;

IMenuOption* HealE;
IMenuOption* HealmanaPercent;
IMenuOption* HealhpPercent;
IMenuOption* HealEAlly;
IMenuOption* HealAllymanaPercent;
IMenuOption* HealAllyhpPercent;
IMenuOption* HealAutoswitch;

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
IMenuOption* DrawQCougar;
IMenuOption* DrawWCougar;
IMenuOption* DrawECougar;

IUnit* myHero;

ISpell2* Q;
ISpell2* W;
ISpell2* E;
ISpell2* QC;
ISpell2* WC;
ISpell2* EC;
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
	MainMenu = GPluginSDK->AddMenu("D-NIdalee++");

	ComboMenu = MainMenu->AddMenu("Combo Settings");
	useIgnite = ComboMenu->CheckBox("Use Ignite", true);
	ComboQ = ComboMenu->CheckBox("Use Q", true);
	ComboW = ComboMenu->CheckBox("Use W", true);
	ComboE = ComboMenu->CheckBox("Use E", true);
	ComboQCougar = ComboMenu->CheckBox("Use Q Cougar", true);
	ComboWCougar = ComboMenu->CheckBox("Use W Cougar", true);
	ComboECougar = ComboMenu->CheckBox("Use E Cougar", true);
	ComboR = ComboMenu->CheckBox("Use R", true);
	
	

	HarassMenu = MainMenu->AddMenu("Harass Setting");
	HarassQ = HarassMenu->CheckBox("Use Q", true);
	HarassManaPercent = HarassMenu->AddInteger("Mana Percent for harass", 10, 100, 70);
	Drawings = MainMenu->AddMenu("Drawings");

	FarmMenu = MainMenu->AddMenu("Farm Lane Setting");
	FarmQ = FarmMenu->CheckBox("Use Q Farm", true);
	FarmW = FarmMenu->CheckBox("Use W Farm", false);
	FarmE = FarmMenu->CheckBox("Use E Farm", true);
	FarmQCougar = FarmMenu->CheckBox("Use  Cougar Q Farm", true);
	FarmWCougar = FarmMenu->CheckBox("Use Cougar W Farm", true);
	FarmECougar = FarmMenu->CheckBox("Use Cougar E Farm", true);
	FarmAutoswitch = FarmMenu->CheckBox("Auto Switch Form", true);
	FarmManaPercent = FarmMenu->AddInteger("if Mana Percent", 10, 100, 70);

	JungleMenu = MainMenu->AddMenu("Jungle Setting");
	JungleQ = JungleMenu->CheckBox("Use Q Jungle", true);
	JungleW = JungleMenu->CheckBox("Use W Jungle", true);
	JungleE = JungleMenu->CheckBox("Use E Jungle", true);
	JungleQCougar = JungleMenu->CheckBox("Use  Cougar Q Jungle", true);
	JungleWCougar = JungleMenu->CheckBox("Use Cougar W Jungle", true);
	JungleECougar = JungleMenu->CheckBox("Use Cougar E Jungle", true);
	JungleAutoswitch = JungleMenu->CheckBox("Auto Switch Form", true);
	JungleManaPercent = JungleMenu->AddInteger("if Mana % >", 10, 100, 70);

	SmiteMenu = MainMenu->AddMenu("Smite Setting");
	usesmitetarget = SmiteMenu->CheckBox("Use Smite on target", true);
	smitejungle = SmiteMenu->CheckBox("Use Smite in Jungle", true);
	usesmitejungle = SmiteMenu->AddInteger("0=Smite all Monst, 1=Smite only Epic", 0, 1, 0);
	
	HealMenu = MainMenu->AddMenu("Heal Setting");
	HealE = HealMenu->CheckBox("Use E to heal", true);
	HealmanaPercent = HealMenu->AddInteger("Heal me if Mana % >", 10, 100, 40);
	HealhpPercent = HealMenu->AddInteger("Heal me if HP % <", 10, 100, 70);
	HealEAlly = HealMenu->CheckBox("Use E to heal Ally", true);
	HealAllymanaPercent = HealMenu->AddInteger("Heal Ally if Mana % >", 10, 100, 70);
	HealAllyhpPercent = HealMenu->AddInteger("Heal Ally if HP % <", 10, 100, 40);
	HealAutoswitch = HealMenu->CheckBox("Auto Switch Form", true);
	
	
	MiscMenu = MainMenu->AddMenu("Misc Setting");
	KillstealQ = MiscMenu->CheckBox("Use Q to killsteal", true);
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
	DrawQ = Drawings->CheckBox("Draw Q Human", true);
	DrawW = Drawings->CheckBox("Draw W Human", false);
	DrawQCougar = Drawings->CheckBox("Draw Q Cougar", false);
	DrawWCougar = Drawings->CheckBox("Draw W Cougar", false);
	DrawECougar = Drawings->CheckBox("Draw E Cougar", true);
}
void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithHeroes | kCollidesWithYasuoWall));
	Q->SetSkillshot(0.25f, 40.f, 1300.f, 1500.f);

	W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	W->SetOverrideRange(875);
	W->SetOverrideRadius(50);

	E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, static_cast<eCollisionFlags> (kCollidesWithNothing));
	E->SetOverrideRange(600);

	QC = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	QC->SetOverrideRange(400);

	WC = GPluginSDK->CreateSpell2(kSlotW, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	WC->SetSkillshot(0.50f, 300.f, FLT_MAX, 375.f);

	EC = GPluginSDK->CreateSpell2(kSlotE, kConeCast, false, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	EC->SetSkillshot(0.50f, 260, FLT_MAX, 300.f);

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

bool IsHuman()
{
	if (myHero->GetSpellBook()->GetLevel(kSlotQ) > 0)
	{
		return strcmp(GEntityList->Player()->GetSpellBook()->GetName(kSlotQ), "JavelinToss") == 0;
	}
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
		if (!IsHuman())
		{
			if (QC->IsReady() && FarmQCougar->Enabled() && myHero->IsValidTarget(minions, QC->Range()))
			{
				QC->CastOnUnit(minions);
			}
			if (WC->IsReady() && FarmWCougar->Enabled() && myHero->IsValidTarget(minions, WC->Range()))
			{
				WC->CastOnTargetAoE(minions, 2, kHitChanceLow) || WC->LastHitMinion();			
			}
			if (EC->IsReady() && FarmECougar->Enabled() && myHero->IsValidTarget(minions, EC->Range()))
			{
				EC->CastOnUnit(minions);
			}
			if (FarmAutoswitch->Enabled() && R->IsReady() && !QC->IsReady() && !WC->IsReady() && !EC->IsReady() && mana)
			{
				R->CastOnPlayer();
			}
		}
		if (IsHuman())
		{
			if (FarmQ->Enabled() && mana && Q->IsReady())
			{
				if (myHero->IsValidTarget(minions, Q->Range()))
				{
					Q->CastOnUnit(minions);
				}
			}
			if (FarmW->Enabled() && mana && W->IsReady())
			{
				if (myHero->IsValidTarget(minions, W->Range()) && !minions->GetBuffDataByName("nidaleepassivehunted"))
				{
					W->CastOnTarget(minions);
				}
			}

			if (FarmAutoswitch->Enabled() && (!Q->IsReady() || !mana || !FarmQ) /*&& !myHero->GetBuffCount("PrimalSurge")*/)
			{
				if (R->IsReady())
				{
					R->CastOnPlayer();
				}
			}
			if (E->IsReady() && !FarmAutoswitch && FarmE->Enabled() && mana)
			{
				E->CastOnPlayer();
			}
		}
	}
}
void Jungle()
{
	auto mana = myHero->ManaPercent() > JungleManaPercent->GetInteger();
	for (auto minions : GEntityList->GetAllMinions(false, false, true))
	{
		if (!IsHuman())
		{
			if (QC->IsReady() && JungleQCougar->Enabled() && myHero->IsValidTarget(minions, QC->Range()))
			{
				QC->CastOnPlayer();
			}
			if (WC->IsReady() && JungleWCougar->Enabled() && myHero->IsValidTarget(minions, WC->Range()))
			{
				WC->CastOnPosition(minions->ServerPosition());
			}
			if (EC->IsReady() && JungleECougar->Enabled() && myHero->IsValidTarget(minions, EC->Range()))
			{
				EC->CastOnUnit(minions);
			}
			if (JungleAutoswitch->Enabled() && R->IsReady() && !QC->IsReady() && !WC->IsReady() && !EC->IsReady())
			{
				if (mana)
				{
					R->CastOnPlayer();
				}
			}
		}
		if (IsHuman())
		{
			if (JungleQ->Enabled() && mana && Q->IsReady() && !strstr(minions->GetObjectName(), "mini"))
			{
				if (myHero->IsValidTarget(minions, Q->Range()))
				{
					Q->CastOnUnit(minions);
				}
			}
			if (JungleW->Enabled() && mana && W->IsReady() && !strstr(minions->GetObjectName(), "mini"))
			{
				if (myHero->IsValidTarget(minions, W->Range()) && !minions->GetBuffDataByName("nidaleepassivehunted"))
				{
					W->CastOnUnit(minions);
				}
			}
			if (JungleAutoswitch->Enabled() && (!Q->IsReady() || !JungleQ->Enabled() || !mana))
			{
				if (R->IsReady())
				{
					R->CastOnPlayer();
				}
			}
			if (E->IsReady() && !FarmAutoswitch && FarmE->Enabled() && mana && myHero->HealthPercent() < 30)
			{
				E->CastOnPlayer();
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
void Heal()
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo || !myHero->IsRecalling())
		return;
	if (E->IsReady())
	{
		if (HealE->Enabled() && myHero->HealthPercent() < HealhpPercent->GetInteger() && myHero->ManaPercent() > HealmanaPercent->GetInteger())
		{
			if (IsHuman())
			{
				E->CastOnPlayer();
			}
			if (!IsHuman() && HealAutoswitch->Enabled() && R->IsReady())
			{
				R->CastOnPlayer();
				E->CastOnPlayer();
			}
		}
		for (auto ally : GEntityList->GetAllHeros(true, false))
		{
			if (HealEAlly->Enabled() && myHero->ManaPercent() > HealAllymanaPercent->GetInteger())
			{
				if (myHero->IsValidTarget(ally, E->Range()) && ally->HealthPercent() < HealAllyhpPercent->GetInteger())
				{
					if (IsHuman())
					{
						E->CastOnTarget(ally);
					}
					if (!IsHuman() && HealAutoswitch->Enabled() && R->IsReady())
					{
						R->CastOnPlayer();
						E->CastOnTarget(ally);
					}
				}
			}
		}
	}
}
void Combo()
{
	smitetarget();
	if (Ignite != nullptr)
	{
		if (useIgnite->Enabled() && Ignite->IsReady())
		{
			auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			if (Enemy->HealthPercent() <= 30 && Enemy->IsValidTarget(myHero, Ignite->GetSpellRange()) && Enemy != nullptr)
			{
				Ignite->CastOnUnit(Enemy);
			}
		}
	}
	if (IsHuman())
	{
		if (ComboQ->Enabled())
		{
			if (Q->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
				if (target != nullptr &&  target->IsValidTarget())
					Q->CastOnTarget(target, kHitChanceMedium);
			}
		}
		if (ComboW->Enabled())
		{
			if (W->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());
				if (target != nullptr && myHero->IsValidTarget(target, W->Range()))
					W->CastOnTarget(target, kHitChanceHigh);
			}
		}
		if (ComboR->Enabled() && R->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, W->Range());
			if (target != nullptr &&  target->IsValidTarget(target, W->Range()))
			{
				if (GetDistance(myHero, target) <= 325 || target->HasBuff("nidaleepassivehunted"))
				{
					R->CastOnPlayer();
				}
			}
		}
	}


	if (!IsHuman())
	{
		if (ComboWCougar->Enabled())
		{
			if (WC->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, WC->Range());
				if (target != nullptr && myHero->IsValidTarget(target, WC->Range()))
					WC->CastOnPosition(target->ServerPosition());
			}
		}
		if (ComboECougar->Enabled())
		{
			if (EC->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, EC->Range());
				if (target != nullptr && myHero->IsValidTarget(target, EC->Range()))
					EC->CastOnTarget(target, kHitChanceMedium);
			}
		}
		if (ComboQCougar->Enabled())
		{
			if (QC->IsReady())
			{
				auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, WC->Range());
				if (target != nullptr && myHero->IsValidTarget(target, WC->Range()))
					QC->CastOnPlayer();
			}
		}

		if (ComboR->Enabled() && R->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
			if (target != nullptr && !target->IsDead())
				if (GetDistance(myHero, target) > WC->Range())
				{
					R->CastOnPlayer();
				}

			if (!QC->IsReady() && !WC->IsReady() && !EC->IsReady())
			{
				R->CastOnPlayer();
			}
		}
	}
	if (ComboE->Enabled() && IsHuman() && myHero->HealthPercent() < 20 && E->IsReady())
	{
		E->CastOnPlayer();
	}
}

void Harass()
{
	if (myHero->ManaPercent() < HarassManaPercent->GetInteger())
		return;
	if (HarassQ->Enabled() && IsHuman())
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (target != nullptr && target->IsValidTarget(myHero, Q->Range()))
				Q->CastOnTarget(target, kHitChanceHigh);
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
			if (KillstealQ->Enabled() && IsHuman())
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
		if (IsHuman())
		{
			if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
		}
		else if (!IsHuman())
		{
			if (QC->IsReady() && DrawQCougar->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), QC->Range()); }

			if (WC->IsReady() && DrawWCougar->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), WC->Range()); }

			if (EC->IsReady() && DrawECougar->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), EC->Range()); }
		}
	}
	else
	{
		if (IsHuman())
		{
			if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

			if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), W->Range()); }
		}
		else if (!IsHuman())
		{
			if (DrawQCougar->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), QC->Range()); }

			if (DrawWCougar->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), WC->Range()); }

			if (DrawECougar->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), EC->Range()); }
		}
	}
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	auto target = GTargetSelector->FindTarget(QuickestKill, SpellDamage, Q->Range());
	if (myHero->IsValidTarget(target, Q->Range()))
	{
		if (target->HasBuff("nidaleepassivehunted"))
			WC->SetOverrideRange(750);
		else WC->SetOverrideRange(375);
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
	Heal();
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
		
	if (strcmp(GEntityList->Player()->ChampionName(), "Nidalee") == 0)
	{
		GGame->PrintChat("D-NIdalee : Loaded");
	}
	else
	{
		GGame->PrintChat("You are not playing Nidalee...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
}