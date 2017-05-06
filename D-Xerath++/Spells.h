#pragma once
#include "Menu.h"

inline void LoadSpells()
{
	
	
	//WCenter = new Spell(SpellSlot.W, 1000f);
	//WCenter.SetSkillshot(0.7f, 50f, float.MaxValue, false, SkillshotType.SkillshotCircle);
		
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	Q->SetSkillshot(0.6f, 100.f, FLT_MAX, 1600.f);
	Q->SetCharged(750, 1550, 1.5);

	W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	W->SetSkillshot(0.7f, 200.f, FLT_MAX, 1000.f);

	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall | kCollidesWithHeroes | kCollidesWithMinions));
	E->SetSkillshot(0.2f, 60.f, 1400.f, 1150.f);

	R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	R->SetSkillshot(0.7f, 120.f, FLT_MAX, 2950.f);

	auto slot1 = GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1);
	auto slot2 = GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2);

	if (strcmp(slot1, "SummonerDot") == 0)
	{
		Ignite = GPluginSDK->CreateSpell2(kSummonerSlot1, kCircleCast, false, false, kCollidesWithNothing);
		Ignite->SetOverrideRange(600.f);
	}

	if (strcmp(slot2, "SummonerDot") == 0)
	{
		Ignite = GPluginSDK->CreateSpell2(kSummonerSlot2, kCircleCast, false, false, kCollidesWithNothing);
		Ignite->SetOverrideRange(600.f);
	}	
	bluetinket = GPluginSDK->CreateItemForId(3363, 4000);
	Titanic_Hydra = GPluginSDK->CreateItemForId(3748, 385);
	Ravenous_Hydra = GPluginSDK->CreateItemForId(3074, 385);
	Tiamat = GPluginSDK->CreateItemForId(3077, 385);
	Youmuu = GPluginSDK->CreateItemForId(3142, 0);
	blade = GPluginSDK->CreateItemForId(3153, 550);
	Cutlass = GPluginSDK->CreateItemForId(3144, 550);
	Quicksilver = GPluginSDK->CreateItemForId(3140, 0);
	Mercurial = GPluginSDK->CreateItemForId(3139, 600);

	HealthPot = GPluginSDK->CreateItemForId(2003, 0);
	CorruptPot = GPluginSDK->CreateItemForId(2033, 0);
	RefillPot = GPluginSDK->CreateItemForId(2031, 0);
	Biscuit = GPluginSDK->CreateItemForId(2010, 0);
	hunter = GPluginSDK->CreateItemForId(2032, 0);
}
