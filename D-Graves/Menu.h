#pragma once
#include "PluginSDK.h"

IMenu* MainMenu;
IMenu* ComboMenu;
IMenu* HarassMenu;
IMenu* Smitemenu;
IMenu* FarmMenu;
IMenu* JungleMenu;
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
IMenuOption* smitejungle;
IMenuOption* usesmitetarget;
IMenuOption* usesmitejungle;
IMenuOption* FarmQ;
IMenuOption* FarmW;
IMenuOption* FarmE;
IMenuOption* FarmManaPercent;
IMenuOption* JungleQ;
IMenuOption* JungleW;
IMenuOption* JungleE;
IMenuOption* JungleManaPercent;
IMenuOption* SemiR;
IMenuOption* KillstealQ;
IMenuOption* KillstealW;
IMenuOption* KillstealR;
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
IMenuOption* Burst_b;
IMenuOption* BurstColor;
IMenuOption* DrawBurst;
IMenuOption* Drawhealthbar;
IMenuOption* Drawdmg;
IMenuOption* qRangeColor;
IMenuOption* wRangeColor;
IMenuOption* eRangeColor;
IMenuOption* rRangeColor;
IMenuOption* dmgRangeColor;
IMenuOption* QRange;

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
float lastE;
float lastR;
 bool nowauto = false;
inline void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Graves");

	ComboMenu = MainMenu->AddMenu("Combo Settings");
	ComboQ = ComboMenu->CheckBox("Use Q", true);
	QRange = ComboMenu->AddInteger("Q->Range", 750, 950, 800);
	ComboW = ComboMenu->CheckBox("Use W", true);
	ComboE = ComboMenu->CheckBox("Use E", true);
	ComboR = ComboMenu->CheckBox("Use R if Is killable", true);
	ComboRAOEuse = ComboMenu->CheckBox("Use R if hit 3 Enemys", false);
	SemiR = ComboMenu->AddKey("Semi-Manual R", 84);
	Burst_b = MainMenu->AddKey("Burst Combo", 75);

	HarassMenu = MainMenu->AddMenu("Harass Setting");
	HarassQ = HarassMenu->CheckBox("Use Q", true);
	HarassW = HarassMenu->CheckBox("Use W", true);
	HarassManaPercent = HarassMenu->AddInteger("Mana Percent for harass", 10, 100, 70);
	Drawings = MainMenu->AddMenu("Drawings");

	Smitemenu = MainMenu->AddMenu("Smite Setting");
	usesmitetarget = Smitemenu->CheckBox("Use Smite on target", true);
	smitejungle = Smitemenu->CheckBox("Use Smite in Jungle", true);
	usesmitejungle = Smitemenu->AddInteger("0=Smite all Monst, 1=Smite only Epic", 0, 1, 0);

	FarmMenu = MainMenu->AddMenu("LaneClear Setting");
	FarmQ = FarmMenu->CheckBox("Use Q Farm", true);
	FarmW = FarmMenu->CheckBox("Use W Farm", true);
	FarmManaPercent = FarmMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	JungleMenu = MainMenu->AddMenu("Jungle Setting");
	JungleQ = JungleMenu->CheckBox("Use Q Jungle", true);
	JungleW = JungleMenu->CheckBox("Use W Jungle", true);
	JungleE = JungleMenu->CheckBox("Use E Jungle", true);
	JungleManaPercent = JungleMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);

	MiscMenu = MainMenu->AddMenu("Misc Setting");
	KillstealQ = MiscMenu->CheckBox("Use Q to killsteal", true);
	KillstealW = MiscMenu->CheckBox("Use W to killsteal", true);
	KillstealR = MiscMenu->CheckBox("Use R to killsteal", true);
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
	qRangeColor = Drawings->AddColor("Q Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawW = Drawings->CheckBox("Draw W", false);
	wRangeColor = Drawings->AddColor("W Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawR = Drawings->CheckBox("Draw R", true);
	rRangeColor = Drawings->AddColor("R Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawBurst = Drawings->CheckBox("Draw Burst Range", true);
	BurstColor = Drawings->AddColor("Burst Range Color", 3.f, 252.f, 19.f, 255.f);
	Drawdmg = Drawings->CheckBox("Draw Damage (Percent)", true);
	Drawhealthbar = Drawings->CheckBox("Draw Damage (Healthbar)", true);
	dmgRangeColor = Drawings->AddColor("Damage (Healthbar) Color", 3.f, 252.f, 19.f, 255.f);
}
