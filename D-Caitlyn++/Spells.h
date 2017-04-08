#pragma once

#include "Menu.h"
inline void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	Q->SetSkillshot(0.25f, 60.f, 2000.f, 1200.f);

	W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, true, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	W->SetSkillshot(1.00f, 100.f, FLT_MAX, 800.f);

	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, static_cast<eCollisionFlags> (kCollidesWithYasuoWall | kCollidesWithMinions));
	E->SetSkillshot(0.25f, 80.f, 1600.f, 770.f);

	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall | kCollidesWithHeroes));
	R->SetSkillshot(0.25f, 0.f, 1000.f, RRange);

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


	blade = GPluginSDK->CreateItemForId(3153, 550);
	Cutlass = GPluginSDK->CreateItemForId(3144, 550);
	HealthPot = GPluginSDK->CreateItemForId(2003, 0);
	CorruptPot = GPluginSDK->CreateItemForId(2033, 0);
	RefillPot = GPluginSDK->CreateItemForId(2031, 0);
	Biscuit = GPluginSDK->CreateItemForId(2010, 0);
	hunter = GPluginSDK->CreateItemForId(2032, 0);
}
