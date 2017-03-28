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
IMenuOption* UseIgnitecombo;
IMenuOption* NormalCancel;
IMenuOption* QDelay1;
IMenuOption* QDelay2;
IMenuOption* QDelay3;
IMenuOption* ComboQ;
IMenuOption* ComboW;
IMenuOption* ComboE;
IMenuOption* ComboR;
IMenuOption* ComboR2;
IMenuOption* HarassQ;
IMenuOption* HarassW;
IMenuOption* HarassE;
IMenuOption* FarmQ;
IMenuOption* FarmW;
IMenuOption* LastHitQ;
IMenuOption* Itemsinlane;
IMenuOption* JungleQ;
IMenuOption* JungleW;
IMenuOption* JungleE;
IMenuOption* KeepQ;
IMenuOption* useYoumuu;
IMenuOption* AutoE;
IMenuOption* InterruptE;

IMenuOption* KillstealW;
IMenuOption* KillstealE;
IMenuOption* KillstealR;
IMenuOption* RMin;
IMenuOption* ImmobileQ;
IMenuOption* ImmobileR;
IMenuOption* Blade_Cutlass;
IMenuOption* MyHpPreBlade;
IMenuOption* EnemyHpPreBlade;
IMenuOption* usepotion;
IMenuOption* WGapcloser;
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
IMenuOption* Hydra;
IMenuOption* RHydra;
IMenuOption* _tiamat;
IMenuOption* AADelay;
IMenuOption* Burst_b;
IMenuOption* Flee_b;
IMenuOption* Debug;
IMenuOption* Drawdmg;
IMenuOption* Drawhealthbar;
IMenuOption* healthbarcolor;

IUnit* myHero;

IInventoryItem* Titanic_Hydra;
IInventoryItem* Ravenous_Hydra;
IInventoryItem* Tiamat;
IInventoryItem* Youmuu;
IInventoryItem* blade;
IInventoryItem* Cutlass;
IInventoryItem* HealthPot;
IInventoryItem* CorruptPot;
IInventoryItem* Biscuit;
IInventoryItem* RefillPot;
IInventoryItem* hunter;

int Qstack;
float LastQ;
float LastE;
bool AutoAttack = false;
inline void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Riven++");
	Burst_b = MainMenu->AddKey("Burst Combo", 75);
	Flee_b = MainMenu->AddKey("Flee", 76);
	Debug = MainMenu->CheckBox("Enable Debug", false);
	QMenu = MainMenu->AddMenu("Q Settings");
	ComboQ = QMenu->CheckBox("Use Q in combo", true);
	HarassQ = QMenu->CheckBox("Use Q in Harass", true);
	FarmQ = QMenu->CheckBox("Use Q in Laneclear", true);
	JungleQ = QMenu->CheckBox("Use Q in JungleClear", true);
	AADelay = QMenu->AddInteger("AA Delay", 100, 1000, 550);
	QDelay1 = QMenu->AddInteger("Delay Q1", 100, 1000, 290);
	QDelay2 = QMenu->AddInteger("Delay Q2", 100, 1000, 290);
	QDelay3 = QMenu->AddInteger("Delay Q3", 100, 1000, 390);
	KeepQ = QMenu->CheckBox("Keep Q Alive", false);

	WMenu = MainMenu->AddMenu("W Settings");
	ComboW = WMenu->CheckBox("Use W in Combo", true);
	HarassW = WMenu->CheckBox("Use W in Harass", true);
	WGapcloser = WMenu->CheckBox("Use W Gapcloser", true);
	InterruptE = WMenu->CheckBox("Use W Interrupt", true);
	FarmW = WMenu->CheckBox("Use W in Laneclear", true);
	JungleW = WMenu->CheckBox("Use W in JungleClear", true);
	KillstealW = WMenu->CheckBox("Use W to Killsteal", true);
	

	EMenu = MainMenu->AddMenu("E Settings");
	ComboE = EMenu->CheckBox("Use E Combo", true);
	HarassE = EMenu->CheckBox("Use E Harass", true);
	JungleE = EMenu->CheckBox("Use E in Jungle", true);
	AutoE = EMenu->CheckBox("Use E Auto Shield", true);
	KillstealE = EMenu->CheckBox("Use Eto closse distance to Killsteal", true);


	RMenu = MainMenu->AddMenu("R Settings");
	ComboR = RMenu->CheckBox("Use R1 Combo", true);
	ComboR2 = RMenu->CheckBox("Use R2 Combo", true);
	KillstealR = RMenu->CheckBox("Use R to killsteal", true);
	

	ItemsMenu = MainMenu->AddMenu("Items Setting");
	UseIgnitecombo = ItemsMenu->CheckBox("Use ignite in combo", true);
	Hydra = ItemsMenu->CheckBox("Use Titanic_Hydra", true);
	RHydra = ItemsMenu->CheckBox("Use Ravenous_Hydras", true);
	_tiamat = ItemsMenu->CheckBox("UseTiamat", true);
	useYoumuu = ItemsMenu->CheckBox("Use Youmuu's", true);
	Itemsinlane = ItemsMenu->CheckBox("Use tiamat/hydra in lane", true);
	

	PotionMenu = MainMenu->AddMenu("Potion Setting");
	usepotion = PotionMenu->CheckBox("Use potions", true);
	usepotionhpper = PotionMenu->AddInteger("Use potions if HP <", 10, 100, 35);

	Drawings = MainMenu->AddMenu("Drawings");
	DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
	DrawQ = Drawings->CheckBox("Draw Q", true);
	DrawW = Drawings->CheckBox("Draw W", false);
	DrawE = Drawings->CheckBox("Draw E", false);
	DrawR = Drawings->CheckBox("Draw R", false);
	Drawdmg = Drawings->CheckBox("Draw Damage (Percent)", true);
	Drawhealthbar = Drawings->CheckBox("Draw Damage (Healthbar)", true);
	healthbarcolor = Drawings->AddColor("Damage.Healthbar.Color", 0, 128, 0, 255);
		
}