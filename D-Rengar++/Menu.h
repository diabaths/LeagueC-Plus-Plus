#pragma once
#include "PluginSDK.h"
#include <map>

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
IMenu* Smitemenu;
IMenuOption* ComboQ;
IMenuOption* ComboW;
IMenuOption* ComboE;
IMenuOption* ComboR;
IMenuOption* UseIgnitecombo;
IMenuOption* ComboR2;
IMenuOption* HarassQ;
IMenuOption* HarassManaPercent;
IMenuOption* FarmQ;
IMenuOption* LastHitQ;
IMenuOption* minminions;
IMenuOption* FarmManaPercent;
IMenuOption* JungleQ;
IMenuOption* JungleW;
IMenuOption* JungleE;
IMenuOption* JungleManaPercent;
IMenuOption* KillstealQ;
IMenuOption* KillstealR;
IMenuOption* Blade_Cutlass;
IMenuOption* MyHpPreBlade;
IMenuOption* EnemyHpPreBlade;
IMenuOption* usepotion;
IMenuOption* AutoEGapcloser;
IMenuOption* usepotionhpper;
IMenuOption* DrawReady;
IMenuOption* DrawQ;
IMenuOption* DrawW;
IMenuOption* DrawE;
IMenuOption* DrawR;
IMenuOption* qRangeColor;
IMenuOption* wRangeColor;
IMenuOption* eRangeColor;
IMenuOption* rRangeColor;
IMenuOption* DrawCombomode;
IMenuOption* FarmW;
IMenuOption* minminionsW;
IMenuOption* smitejungle;
IMenuOption* usesmitejungle;
IMenuOption* usesmitetarget;
IMenuOption* UseAsapR2;
IMenuOption* FleeKey;
IMenuOption* Qin2stucks;
IMenuOption* ComboRAOE;
IMenuOption* ComboRAOEUse;
IMenuOption* Ultisave;
IMenuOption* UltisaveHp;
IMenuOption* Recallback;
IMenuOption* HarassE;
IMenuOption* KillstealE;
IMenuOption* EnemyUndertowerE;
IMenuOption* AoeE;
IMenuOption* AoeEEnemys;
IMenuOption* UseEHP;
IMenuOption* FarmE;
IMenuOption* HarassW;
IMenuOption* UseProto;
IMenuOption* Drawhealthbar;
IMenuOption* healRangeColor;
IMenuOption* laneclearON;
IMenuOption* Usezhonyas;
IMenuOption* UseProtojungle;
IMenuOption* AutoE;
IMenuOption* smitekey;
IMenuOption* DrawSmite;
IMenuOption* Hydra; 
IMenuOption* RHydra; 
IMenuOption* _tiamat; 
IMenuOption* useYoumuu; 
IMenuOption* Itemsinlane; 
IMenuOption* Burst_b;
IMenuOption* menuquicksilver;
IMenuOption* menumercurial;
IMenuOption* AutoW;
IMenuOption* Comboprio;
IMenuOption* ChangeSkin;
IMenuOption* SkinChangeid;
IMenuOption* Flee_b;

IUnit* Rpos;
IUnit* myHero;

ISpell2* Q;
ISpell2* W;
ISpell2* E;
ISpell2* R;


ISpell2* Ignite;
ISpell2* smite;

IInventoryItem* Titanic_Hydra;
IInventoryItem* Ravenous_Hydra;
IInventoryItem* Tiamat;
IInventoryItem* Youmuu;
IInventoryItem* blade;
IInventoryItem* Cutlass;
IInventoryItem* Quicksilver;
IInventoryItem* Mercurial;


IInventoryItem* HealthPot;
IInventoryItem* CorruptPot;
IInventoryItem* Biscuit;
IInventoryItem* RefillPot;
IInventoryItem* hunter;

int mode;
float lastrecall;
short keyDown;
bool SmiteDown;
bool stealthdown;
bool passiveup;
float CombokeyDown;
int ComboMode;
inline void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Rengar++");

	QMenu = MainMenu->AddMenu("Q Settings");
	ComboQ = QMenu->CheckBox("Use Q in combo", true);
	HarassQ = QMenu->CheckBox("Use Q harass", false);
	FarmQ = QMenu->CheckBox("Use Q Farm", true);
	JungleQ = QMenu->CheckBox("Use Q Jungle", true);
	//KillstealQ = QMenu->CheckBox("Use Q to killsteal", true);

	WMenu = MainMenu->AddMenu("W Settings");
	ComboW = WMenu->CheckBox("Use W in Combo", true);
	HarassW = WMenu->CheckBox("Use W in Harass", false);
	FarmW = WMenu->CheckBox("Use W Farm", true);
	minminionsW = WMenu->AddInteger("Use W if Hit minion =>", 1, 6, 3);
	JungleW = WMenu->CheckBox("Use W Jungle", true);
	AutoW = WMenu->CheckBox("Remove crowd control effects", true);


	EMenu = MainMenu->AddMenu("E Settings");
	ComboE = EMenu->CheckBox("Use E Combo", true);
	HarassE = EMenu->CheckBox("Use E Harass", true);
	FarmE = EMenu->CheckBox("Use E Laneclear", false);
	JungleE = EMenu->CheckBox("Use E JungleClear", true);
	//KillstealE = EMenu->CheckBox("Use E Killsteal", true);
		

	MiscMenu = MainMenu->AddMenu("Misc Settings");
	Comboprio = MiscMenu->AddKey("Change Combo Mode", 83);	
	ChangeSkin = MiscMenu->CheckBox("Use Skin", true);
	SkinChangeid = MiscMenu->AddInteger("Skin ID", 1, 3, 1);
		

	Smitemenu = MainMenu->AddMenu("Smite Setting");
	smitekey = Smitemenu->AddKey("Smite On-Off(Toggle)", 84);
	usesmitetarget = Smitemenu->CheckBox("Use Smite on target", true);
	smitejungle = Smitemenu->CheckBox("Use Smite in Jungle", true);
	usesmitejungle = Smitemenu->AddInteger("0=Smite all Monst, 1=Smite only Epic", 0, 1, 0);

	ItemsMenu = MainMenu->AddMenu("Items Setting");
	UseIgnitecombo = ItemsMenu->CheckBox("Use ignite in combo", true);
	Hydra = ItemsMenu->CheckBox("Use Titanic_Hydra", true);
	RHydra = ItemsMenu->CheckBox("Use Ravenous_Hydras", true);
	_tiamat = ItemsMenu->CheckBox("UseTiamat", true);
	useYoumuu = ItemsMenu->CheckBox("Use Youmuus", true);
	Itemsinlane = ItemsMenu->CheckBox("Use tiamat/hydra in lane", true);
	Blade_Cutlass = ItemsMenu->CheckBox("Hextech-Cutlass", true);
	MyHpPreBlade = ItemsMenu->AddInteger("Use Hextech-Cutlass if my HP <", 10, 100, 35);
	EnemyHpPreBlade = ItemsMenu->AddInteger("Use Hextech-Cutlass if Enemy HP <", 10, 100, 35);
	menuquicksilver = ItemsMenu->AddInteger("Use Quicksilver", 10, 100, 35);
	menumercurial = ItemsMenu->AddInteger("Use Mercurial ", 10, 100, 35);


	PotionMenu = MainMenu->AddMenu("Potion Setting");
	usepotion = PotionMenu->CheckBox("Use potions", true);
	usepotionhpper = PotionMenu->AddInteger("Use potions if HP <", 10, 100, 35);

	Drawings = MainMenu->AddMenu("Drawings");
	DrawSmite = Drawings->CheckBox("Draw Smite Status", true);
	DrawCombomode = Drawings->CheckBox("Draw Combo Mode", true);
	DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
	DrawQ = Drawings->CheckBox("Draw Q", false);
	qRangeColor = Drawings->AddColor("Q Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawW = Drawings->CheckBox("Draw W", false);
	wRangeColor = Drawings->AddColor("W Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawE = Drawings->CheckBox("Draw E", true);
	eRangeColor = Drawings->AddColor("E Range Color", 3.f, 252.f, 19.f, 255.f);
	Drawhealthbar = Drawings->CheckBox("Draw Damage", true);
	healRangeColor = Drawings->AddColor("Damage (Healthbar) Color", 3.f, 252.f, 19.f, 255.f);
}
