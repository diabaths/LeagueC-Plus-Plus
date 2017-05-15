#pragma once
#include "PluginSDK.h"
#include <map>
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
IMenuOption* ChangeSkin;
IMenuOption* SkinChangeid;
std::map<std::string, IMenuOption*> MenuOptions;
inline bool GetMenuBoolean(std::string name)
{
	return MenuOptions[name]->Enabled();
}
inline void AddCheckBox(std::string name, std::string title, bool value)
{
	MenuOptions[name] = EMenu->CheckBox(title.c_str(), value);
}


IUnit* Rpos;
IUnit* myHero;

ISpell2* Q;
ISpell2* W;
ISpell2* E;
ISpell2* R;


ISpell* Ignite;
ISpell2* smite;

IInventoryItem* blade;
IInventoryItem* Cutlass;
IInventoryItem* Hextech;
IInventoryItem* protobelt;
IInventoryItem* zhonyas;

IInventoryItem* HealthPot;
IInventoryItem* CorruptPot;
IInventoryItem* Biscuit;
IInventoryItem* RefillPot;
IInventoryItem* hunter;

int mode;
float lastrecall;
short keyDown;
bool SmiteDown;

inline void  Menu()
{
	MainMenu = GPluginSDK->AddMenu("D-Ekko++");

	QMenu = MainMenu->AddMenu("Q Settings");
	ComboQ = QMenu->CheckBox("Use Q in combo", true);
	HarassQ = QMenu->CheckBox("Use Q harass", true);
	FarmQ = QMenu->CheckBox("Use Q Farm", true);
	minminions = QMenu->AddInteger("Use Q if Hit Minions =>", 1, 6, 3);
	JungleQ = QMenu->CheckBox("Use Q Jungle", true);
	Qin2stucks = QMenu->CheckBox("Use Q if target have 2 stucks", true);
	KillstealQ = QMenu->CheckBox("Use Q to killsteal", true);

	WMenu = MainMenu->AddMenu("W Settings");
	ComboW = WMenu->CheckBox("Use W in Combo", true);
	HarassW = WMenu->CheckBox("Use W in Harass", true);
	FarmW = WMenu->CheckBox("Use W Farm", true);
	minminionsW = WMenu->AddInteger("Use W if Hit Minions =>", 1, 6, 3);
	JungleW = WMenu->CheckBox("Use W Jungle", true);

	
	EMenu = MainMenu->AddMenu("E Settings");
	ComboE = EMenu->CheckBox("Use E Combo", true);
	HarassE = EMenu->CheckBox("Use E Harass", true);
	FarmE = EMenu->CheckBox("Use E Laneclear", false);
	JungleE = EMenu->CheckBox("Use E JungleClear", true);
	KillstealE = EMenu->CheckBox("Use E Killsteal", true);
	EnemyUndertowerE = EMenu->CheckBox("Use E if Enemy UnderTurret", true);
	AoeE = EMenu->CheckBox("Use E if X Enemys Around", true);
	AoeEEnemys = EMenu->AddInteger("Dont Use E if Enemys Around =>", 1, 5, 3);
	UseEHP = EMenu->AddInteger("Dont Use E if HP% <=", 1, 100, 1);
	AutoE = EMenu->CheckBox("Use E to dodge Skills", false);
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
		}
	}


	RMenu = MainMenu->AddMenu("R Settings");
	ComboR = RMenu->CheckBox("Use R Combo to kill the target", true);
	ComboRAOE = RMenu->CheckBox("Use R Combo if hit X enemys", true);
	ComboRAOEUse = RMenu->AddInteger("Use R Combo if hit Enemys =>", 1, 5, 3);
	Ultisave = RMenu->CheckBox("Use R to Save(auto)", true);
	//Recallback = RMenu->CheckBox("Use R to Recall back in lane", true);	
	KillstealR = RMenu->CheckBox("Use R to killsteal", true);

	MiscMenu = MainMenu->AddMenu("Misc Settings");
	FleeKey = MiscMenu->AddKey("Flee Key", 76);
	ChangeSkin = MiscMenu->CheckBox("Use Skin", true);
	SkinChangeid = MiscMenu->AddInteger("Skin ID", 1, 3, 1);
	
	ManaMenu = MainMenu->AddMenu("Mana Settings");
	HarassManaPercent = ManaMenu->AddInteger("Mana Percent for harass", 10, 100, 70);
	FarmManaPercent = ManaMenu->AddInteger("Mana Percent for Farm", 10, 100, 70);
	JungleManaPercent = ManaMenu->AddInteger("Mana Percent for Jungle", 10, 100, 70);

	Smitemenu = MainMenu->AddMenu("Smite Setting");
	smitekey = Smitemenu->AddKey("Smite On-Off(Toggle)", 84);
	usesmitetarget = Smitemenu->CheckBox("Use Smite on target", true);
	smitejungle = Smitemenu->CheckBox("Use Smite in Jungle", true);
	usesmitejungle = Smitemenu->AddInteger("0=Smite all Monst, 1=Smite only Epic", 0, 1, 0);

	ItemsMenu = MainMenu->AddMenu("Items Setting");
	UseIgnitecombo = ItemsMenu->CheckBox("Use ignite in combo", true);
	Usezhonyas = ItemsMenu->CheckBox("Use Zhonyas", true);
	UseProto = ItemsMenu->CheckBox("Use Protobelt in combo", true);
	UseProtojungle = ItemsMenu->CheckBox("Use Protobelt in jungleClear", true);
	Blade_Cutlass = ItemsMenu->CheckBox("Hextech-Cutlass", true);
	MyHpPreBlade = ItemsMenu->AddInteger("Use Hextech-Cutlass if my HP <", 10, 100, 35);
	EnemyHpPreBlade = ItemsMenu->AddInteger("Use Hextech-Cutlass if Enemy HP <", 10, 100, 35);
	

	PotionMenu = MainMenu->AddMenu("Potion Setting");
	usepotion = PotionMenu->CheckBox("Use potions", true);
	usepotionhpper = PotionMenu->AddInteger("Use potions if HP <", 10, 100, 35);

	Drawings = MainMenu->AddMenu("Drawings");
	DrawSmite = Drawings->CheckBox("Draw Smite Status", true);
	DrawReady = Drawings->CheckBox("Draw Only Ready Spells", true);
	DrawQ = Drawings->CheckBox("Draw Q", true);
	qRangeColor = Drawings->AddColor("Q Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawW = Drawings->CheckBox("Draw W", false);
	wRangeColor = Drawings->AddColor("W Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawE = Drawings->CheckBox("Draw E", false);
	eRangeColor = Drawings->AddColor("W Range Color", 3.f, 252.f, 19.f, 255.f);
	DrawR = Drawings->CheckBox("Draw R", true);
	rRangeColor = Drawings->AddColor("R Range Color", 3.f, 252.f, 19.f, 255.f);
	Drawhealthbar = Drawings->CheckBox("Draw Damage", true);
	healRangeColor = Drawings->AddColor("Damage (Healthbar) Color", 3.f, 252.f, 19.f, 255.f);
}
