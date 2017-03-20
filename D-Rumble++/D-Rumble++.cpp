// D-Rumble.cpp : Defines the exported functions for the DLL application.
//

//#include "stdafx.h"
#include "PluginSDK.h"




PluginSetup("D-Rumble++");

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
IMenuOption* smitejungle;
IMenuOption* usesmitetarget;
IMenuOption* usesmitejungle;
IMenuOption* SemiR;
IMenuOption* UseIgnitecombo;
IMenuOption* ComboQ;
IMenuOption* ComboE;
IMenuOption* ComboW;
IMenuOption* ComboR;
IMenuOption* ComboRAOEuse;
IMenuOption* Combormin;
IMenuOption* HarassQ;
IMenuOption* HarassE;
IMenuOption* FarmQ;
IMenuOption* FarmE;
IMenuOption* JungleQ;
IMenuOption* JungleE;
IMenuOption* JungleW;
IMenuOption* UseIgnitekillsteal;
IMenuOption* KillstealQ;
IMenuOption* KillstealE;
IMenuOption* KillstealR;
IMenuOption* Keep_Heet;
IMenuOption* HeetQ;
IMenuOption* HeetW;
IMenuOption* AutoEGapcloser;
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
IMenuOption* AutoW;
IMenuOption* FarmoutE;
IMenuOption* Farmharass;
IMenuOption* escapterino;


IUnit* myHero;

ISpell2* Q;
ISpell2* W;
ISpell2* E;
ISpell2* R;

ISpell* Ignite;
ISpell* smite;

IInventoryItem* blade;
IInventoryItem* Cutlass;
IInventoryItem* HealthPot;
IInventoryItem* CorruptPot;
IInventoryItem* Biscuit;
IInventoryItem* RefillPot;
IInventoryItem* hunter;

void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Rumble");

	ComboMenu = MainMenu->AddMenu("Combo Settings");
	UseIgnitecombo = ComboMenu->CheckBox("Use Ignite", true);
	ComboQ = ComboMenu->CheckBox("Use Q", true);
	ComboW = ComboMenu->CheckBox("Use W", true);
	ComboE = ComboMenu->CheckBox("Use E", true);
	ComboR = ComboMenu->CheckBox("Use R if Is killable", true);
	ComboRAOEuse = ComboMenu->CheckBox("Use R if hit x Enemys", false);
	Combormin = ComboMenu->AddInteger("Use R if Hit ", 1, 5, 3);




	HarassMenu = MainMenu->AddMenu("Harass Setting");
	HarassQ = HarassMenu->CheckBox("Use Q", true);
	HarassE = HarassMenu->CheckBox("Use W", true);


	FarmMenu = MainMenu->AddMenu("LaneClear Setting");
	FarmQ = FarmMenu->CheckBox("Use Q Farm", true);
	FarmE = FarmMenu->CheckBox("Use E Farm", true);
	FarmoutE = FarmMenu->CheckBox("Use E OUT OF AA RANGE", true);
	Farmharass = FarmMenu->CheckBox("Use Q-E to harass while farm", true);


	JungleMenu = MainMenu->AddMenu("Jungle Setting");
	JungleQ = JungleMenu->CheckBox("Use Q Jungle", true);
	JungleW = JungleMenu->CheckBox("Use W Jungle", true);
	JungleE = JungleMenu->CheckBox("Use E Jungle", true);

	SmiteMenu = MainMenu->AddMenu("Smite Setting");
	usesmitetarget = SmiteMenu->CheckBox("Use Smite on target", true);
	smitejungle = SmiteMenu->CheckBox("Use Smite in Jungle", true);
	usesmitejungle = SmiteMenu->AddInteger("0=Smite all Monst, 1=Smite only Epic", 0, 1, 0);

	MiscMenu = MainMenu->AddMenu("Misc Setting");
	KillstealQ = MiscMenu->CheckBox("Use Q to killsteal", true);
	KillstealE = MiscMenu->CheckBox("Use E to killsteal", true);
	KillstealR = MiscMenu->CheckBox("Use R to killsteal", true);
	AutoEGapcloser = MiscMenu->CheckBox("Use E to Gapclose", true);
	Keep_Heet = MiscMenu->AddKey("Use Q-W to Heet", 84);
	HeetQ = MiscMenu->CheckBox("Use Q to Heet", true);
	HeetW = MiscMenu->CheckBox("Use W to Heet", true);
	AutoW = MiscMenu->CheckBox("Use W autoshield", true);
	escapterino= MiscMenu->AddKey("Run Forest!!!", 84);
	

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
	DrawE = Drawings->CheckBox("Draw E", true);
	DrawR = Drawings->CheckBox("Draw R", true);
}
void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	Q->SetOverrideRange(600);

	W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));

	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, static_cast<eCollisionFlags> (kCollidesWithYasuoWall | kCollidesWithMinions | kCollidesWithHeroes));
	E->SetSkillshot(0.45f, 90.f, 1200.f, 840.f);

	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithMinions | kCollidesWithYasuoWall));
	R->SetSkillshot(0.25f, 110.f, 2500.f, 1700.f);


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
Vec2 Perpendicular(Vec2 v)
{
	return Vec2(-v.y, v.x);
}
//Dewblackio2 logic from Victor
void CastR(IUnit* target)
{
	if ((target->ServerPosition() - GEntityList->Player()->ServerPosition()).Length2D() < R->Range())
	{
		auto Rstartcast = target->ServerPosition();
		R->SetRangeCheckFrom(Rstartcast);
		R->SetFrom(Rstartcast);
		AdvPredictionOutput outputfam;
		R->RunPrediction(target, true, kCollidesWithYasuoWall, &outputfam);
		if (outputfam.HitChance >= kHitChanceHigh)
		{
			R->CastFrom(Rstartcast, outputfam.CastPosition);
			R->SetFrom(Vec3(0, 0, 0));
		}
	}
	else if ((target->ServerPosition() - GEntityList->Player()->ServerPosition()).Length2D() < 2700)
	{
		auto Rstartcast = GEntityList->Player()->ServerPosition().Extend(target->ServerPosition(), R->Range());
		R->SetRangeCheckFrom(Rstartcast);
		R->SetFrom(Rstartcast);
		AdvPredictionOutput outputfam;
		R->RunPrediction(target, true, kCollidesWithYasuoWall, &outputfam);
		if (outputfam.HitChance >= kHitChanceHigh)
		{
			R->CastFrom(Rstartcast, outputfam.CastPosition);
			R->SetFrom(Vec3(0, 0, 0));
		}
	}

}

void Heet()
{
	if (myHero->ManaPercent()<50)
	{
		if (HeetQ->Enabled() && Q->IsReady())
		{
			Q->CastOnPlayer();
		}
		if (HeetW->Enabled() && W->IsReady())
		{
			W->CastOnPlayer();
		}
	}
}
void CastQ(IUnit* target)
{
	auto Qdmg = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ);
	auto dmg1 = GDamage->GetAutoAttackDamage(myHero, target, true);
		if(myHero->ManaPercent() < 80 || target->GetHealth()< Qdmg + 2*dmg1)
	{
		Q->CastOnPlayer();
	}
}
void CastE(IUnit* target)
{
	AdvPredictionOutput prediction_output;
	E->RunPrediction(target, true, kCollidesWithYasuoWall | kCollidesWithMinions, &prediction_output);
	if (prediction_output.HitChance >= kHitChanceHigh)
	{
		auto Qdmg = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE);
		auto dmg1 = GDamage->GetAutoAttackDamage(myHero, target, true);
		if (myHero->ManaPercent() < 80 || target->GetHealth()< Qdmg + 2 * dmg1)
		E->CastOnTarget(target, kHitChanceCollision);
	}
}

void Combo()
{
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

	if (ComboQ->Enabled())
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (myHero->IsValidTarget(target, Q->Range()))
			{
				CastQ(target);
			}
		}
	}

	if (ComboW->Enabled())
	{
		if (W->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (myHero->IsValidTarget(target, Q->Range()))
				W->CastOnPlayer();
		}
	}
	if (ComboE->Enabled())
	{
		if (E->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
			if (myHero->IsValidTarget(target, E->Range()))
				CastE(target);
		}
	}
	if (ComboR->Enabled())
	{
		if (R->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R->Range());
			if (myHero->IsValidTarget(target, R->Range()))
			{
				auto Qdmg = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotQ);
				auto Edmg = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE);
				auto Rdmg = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR);
				if (target->GetHealth() < Qdmg + 2 * Edmg + 2 * Rdmg)
				{
					CastR(target);
				}
			}
		}
	}

	if (R->IsReady() && ComboRAOEuse->Enabled())
	{
		auto min = Combormin->GetInteger();
		for (auto Enemy : GEntityList->GetAllHeros(false, true))
		{
			if (Enemy != nullptr && !Enemy->IsDead())
			{
				if (Enemy != nullptr &&  myHero->IsValidTarget(Enemy, R->Range() +800))
				{
					R->CastOnTargetAoE(Enemy, min, kHitChanceMedium);
				}
			}
		}
	}
}

void Harass()
{
	if (HarassQ->Enabled())
	{
		if (Q->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
			if (myHero->IsValidTarget(target, Q->Range()))
			{
				{
					CastQ(target);
				}
			}
		}
	}

	if (HarassE->Enabled())
	{
		if (E->IsReady())
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, E->Range());
			if (myHero->IsValidTarget(target, E->Range()))
				CastE(target);
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
						{
							Q->CastOnTarget(Enemy, kHitChanceHigh);
						}
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
						if (GPrediction->GetCollisionFlagsForPoint(Enemy->GetPosition()) == 0)
						{
							E->CastOnTarget(Enemy, kHitChanceHigh);
						}
					}
				}
			}
		}
	}
}
void laneclear()
{
	if (myHero->ManaPercent() < 80)
	{
		for (auto minions : GEntityList->GetAllMinions(false, true, false))
		{
			if (FarmQ->Enabled() && Q->IsReady())
			{
				auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
				if (myHero->IsValidTarget(minions, Q->Range()))
				{
					if (minions->GetHealth() < dmg)
					{
						Q->CastOnUnit(minions);
					}
					else  	Q->AttackMinions();
				}
			}
			if (FarmE->Enabled() && E->IsReady())
			{
				if (myHero->IsValidTarget(minions, E->Range()))
				{
					E->CastOnUnit(minions);
				}
			}
			auto dmgE = GDamage->GetSpellDamage(myHero, minions, kSlotE);
			if (myHero->IsValidTarget(minions, E->Range()))
			{
				if (FarmoutE->Enabled() && E->IsReady() && !myHero->GetRealAutoAttackRange(minions) && minions->GetHealth() <= dmgE)
				{
					E->CastOnUnit(minions);
				}
			}
		}
	}
}
void jungleclear()
{
	for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
	{
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
				E->CastOnUnit(jMinion);
				return;
			}
		}
		if (JungleW->Enabled() && W->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
			{
				W->CastOnPlayer();
				return;
			}
		}
	}
}
PLUGIN_EVENT(void) OnProcessSpell(CastedSpell const& Args)
{
	if (Args.Caster_ == myHero)
	{
		if (W->IsReady() && AutoW->Enabled() && !GGame->IsChatOpen())
		{
			if (Args.Target_ != nullptr && Args.Target_ == myHero && Args.Damage_ >= 2*myHero->HealthPercent())
			{
				W->CastOnPlayer();
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

		if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
	}
	else
	{
		if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

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
		if (AutoEGapcloser->Enabled() && E->IsReady() && myHero->IsValidTarget(args.Sender, 250) && !args.IsTargeted)
		{
			E->CastOnTarget(args.Sender);
		}
	}
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	if (GetAsyncKeyState(Keep_Heet->GetInteger()))
	{
		Heet();
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		Combo();
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		laneclear();
		jungleclear();
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed || (Farmharass->Enabled() && GOrbwalking->GetOrbwalkingMode() == kModeLaneClear))
	{
		Harass();
	}
	killsteal();
	UseItems();
	Usepotion();
	if (smitejungle->Enabled())
	{
		Smiteuse();
	}
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	if (GetAsyncKeyState(escapterino->GetInteger()))
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			if (W->IsReady())
			{
				W->CastOnPlayer();
			}
			if (E->IsReady() && myHero->IsValidTarget(enemy, E->Range()))
			{
				if (GPrediction->GetCollisionFlagsForPoint(enemy->GetPosition()) == 0)
				{
					E->CastOnTarget(enemy, kHitChanceHigh);
				}
			}
		}
	}
	PluginSDKSetup(PluginSDK);
	Menu();
	LoadSpells();
	myHero = GEntityList->Player();

	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
	GEventManager->AddEventHandler(kEventOnGapCloser, OnGapcloser);
	GEventManager->AddEventHandler(kEventOnSpellCast, OnProcessSpell);
	if (strcmp(GEntityList->Player()->ChampionName(), "Rumble") == 0)
	{
		GGame->PrintChat("D-Rumble++ : Loaded");
	}
	else
	{
		GGame->PrintChat("You are not playing Rumble...");
	}
}


PLUGIN_API void OnUnload()
{
	MainMenu->Remove();

	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
	GEventManager->RemoveEventHandler(kEventOnGapCloser, OnGapcloser);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, OnProcessSpell);
}