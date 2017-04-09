#pragma once
#include "PluginSDK.h"

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
IMenuOption* EWQCombo;
IMenuOption* DrawReady;
IMenuOption* DrawQ;
IMenuOption* DrawW;
IMenuOption* DrawE;
IMenuOption* DrawR;
IMenuOption* qRangeColor;
IMenuOption* wRangeColor;
IMenuOption* eRangeColor;
IMenuOption* rRangeColor;
IMenuOption* harassFarmQ;

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

inline void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Caitlyn++");
	EWQCombo = MainMenu->AddKey("EWQ Combo", 83);
	QMenu = MainMenu->AddMenu("Q Settings");
	ComboQ = QMenu->CheckBox("Use Q in combo", true);
	HarassQ = QMenu->CheckBox("Use Q harass", true);
	harassFarmQ = QMenu->CheckBox("Use Q harass if Hit 2 Minions", true);
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
	qRangeColor = Drawings->AddColor("Q Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawW = Drawings->CheckBox("Draw W", false);
	wRangeColor = Drawings->AddColor("W Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawE = Drawings->CheckBox("Draw E", false);
	eRangeColor = Drawings->AddColor("W Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawR = Drawings->CheckBox("Draw R", true);
	rRangeColor = Drawings->AddColor("R Range Color", 3.f, 252.f, 19.f, 255.f);
}
