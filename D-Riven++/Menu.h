#pragma once
#include "PluginSDK.h"
#include "SpellDatabase.h"

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
IMenu* BurstMenu;
IMenuOption* UseIgnitecombo;
IMenuOption* NormalCancel;
IMenuOption* QDelay1;
IMenuOption* QDelay2;
IMenuOption* QDelay3;
IMenuOption* ComboQ;
IMenuOption* ComboW;
IMenuOption* ComboQW;
IMenuOption* ComboWE;
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
IMenuOption* AutoSetDelay;
IMenuOption* qRangeColor;
IMenuOption* DmgPercent;
IMenuOption* DmgPercentmin;
IMenuOption* UseFlash;
IMenuOption* HarassMode;
IMenuOption* wRangeColor;
IMenuOption* eRangeColor;
IMenuOption* rRangeColor;
IMenuOption* dmgRangeColor;
IMenuOption* healRangeColor;
//IMenuOption* burstMode;
IMenuOption* DrawCombomode;
IMenuOption* BurstModeChange; 
IMenuOption*ChangeSkin;
IMenuOption* SkinChangeid;
IMenuOption* ManualAACancel;
IMenuOption* Autoattackanimation;
IMenuOption* burstRangeColor;
IMenuOption* Drawburst;
IMenuOption* QMode;


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

std::map<std::string, IMenuOption*> MenuOptions;
inline bool GetMenuBoolean(std::string name)
{
	return MenuOptions[name]->Enabled();
}
inline void AddCheckBox(std::string name, std::string title, bool value)
{
	MenuOptions[name] = WMenu->CheckBox(title.c_str(), value);
}
int Qstack;
int Q1Delay;
int Q2Delay;
int Q3Delay;
int DelayAA;
int BurstMode;
float LastQ;
float LastQJ;
float LastE;
float keyDown;
bool AutoAttack;
inline void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Riven++");

	Debug = MainMenu->CheckBox("Enable Debug", false);

	BurstMenu = MainMenu->AddMenu("Misc Menu");
	Burst_b = BurstMenu->AddKey("Burst Combo", 75);
	//burstMode = BurstMenu->AddSelection("Burst Mode:", 0, { "Shy", "Werhli" , "Sexy", "NidaleeJR" });
	BurstModeChange = BurstMenu->AddKey("Change Burst Combo Mode", 84);
	UseFlash = BurstMenu->CheckBox("Use Flash In Burst", true);
	Flee_b = BurstMenu->AddKey("Flee", 76);
	HarassMode = BurstMenu->AddSelection("Harass Mode:", 0, { "Smart", "Normal"});
	ManualAACancel = BurstMenu->CheckBox("Cancel Q animation when manual use it", true);
	ChangeSkin = BurstMenu->CheckBox("Use Skin", true);
	SkinChangeid = BurstMenu->AddInteger("Skin ID", 1, 8, 1);

	QMenu = MainMenu->AddMenu("Q Settings");
	QMode = QMenu->AddSelection("Q Mode:", 0, { "Enemy Position", "Cursor Position" });
	ComboQ = QMenu->CheckBox("Use Q in combo", true);
	HarassQ = QMenu->CheckBox("Use Q in Harass", true);
	FarmQ = QMenu->CheckBox("Use Q in Laneclear", true);
	JungleQ = QMenu->CheckBox("Use Q in JungleClear", true);
	Autoattackanimation = QMenu->CheckBox("Cancel AutoAttack Animation", false);
	QDelay1 = QMenu->AddInteger("Delay Q1", 50, 1000, 290);
	QDelay2 = QMenu->AddInteger("Delay Q2", 50, 1000, 290);
	QDelay3 = QMenu->AddInteger("Delay Q3", 50, 1000, 390);
	AutoSetDelay = QMenu->CheckBox("Q Delay Inlcude the Ping ?", true);
	KeepQ = QMenu->CheckBox("Keep Q Alive", false);

	WMenu = MainMenu->AddMenu("W Settings");
	ComboW = WMenu->CheckBox("Use W in Combo", true);
	ComboQW = WMenu->CheckBox("Use Q1 + W in Combo", false);
	ComboWE = WMenu->CheckBox("Use E + W in Combo", true);
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
	KillstealE = EMenu->CheckBox("Use E to close distance to Killsteal", true);
	AutoE = EMenu->CheckBox("Use E Auto Shield", true);
	{
		for (auto unit : GEntityList->GetAllHeros(false, true))
		{
			for (auto champion : SpellDatabase::Champions)
			{
				if (std::string(champion.second.DisplayName) == std::string(unit->ChampionName()))
				{
					auto spells = champion.second.Spells;
					for (auto championSpell : spells)
					{
						std::string Content = std::string(champion.second.DisplayName) + " " + SpellDatabase::Slots[championSpell.Slot] + ": " + std::string(championSpell.Name);
						AddCheckBox(std::string(championSpell.Name), Content, true);
					}
				}
			}
		}}

	RMenu = MainMenu->AddMenu("R Settings");
	ComboR = RMenu->CheckBox("Use R1 Combo", true);
	DmgPercent = RMenu->AddInteger("Total Damage Percent to active R1", 100, 200, 130);
	DmgPercentmin = RMenu->AddInteger("Dont Active R1 if Enemy HP% <", 1, 100, 5);
	ComboR2 = RMenu->CheckBox("Use R2 Combo", true);
	//ComboR2 = RMenu->AddSelection("Use R2 Mode:", 0, { "my Logic", "Only KillSteal", "First Cast", "Off" });
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
	qRangeColor = Drawings->AddColor("Q Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawW = Drawings->CheckBox("Draw W", false);
	wRangeColor = Drawings->AddColor("W Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawE = Drawings->CheckBox("Draw E", false);
	eRangeColor = Drawings->AddColor("E Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawR = Drawings->CheckBox("Draw R", false);
	rRangeColor = Drawings->AddColor("R Range Color", 3.f, 252.f, 19.f, 255.f);
	Drawdmg = Drawings->CheckBox("Draw Damage (Percent)", false);
	dmgRangeColor = Drawings->AddColor("Damage (Percent) Color", 3.f, 252.f, 19.f, 255.f);
	Drawhealthbar = Drawings->CheckBox("Draw Damage (Healthbar)", false);
	healRangeColor = Drawings->AddColor("Damage (Healthbar) Color", 3.f, 252.f, 19.f, 255.f);
	DrawCombomode = Drawings->CheckBox("Draw Combo Mode", true); 
	Drawburst= Drawings->CheckBox("Draw Burst Range", true);
	burstRangeColor = Drawings->AddColor("Burst range  Color", 3.f, 252.f, 19.f, 255.f);
	
		
}