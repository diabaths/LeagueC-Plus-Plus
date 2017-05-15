#pragma once
#include "Menu.h"

inline void LoadSpells()
{	
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	Q->SetSkillshot(0.25f, 60.f, 1650.f, 950.f);

	W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, true, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	W->SetSkillshot(3.75f, 200.f, 1650, 1600.f);
	
	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	E->SetOverrideRange(325);

	R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	R->SetSkillshot(0.25f, 375.f, FLT_MAX, 280.f);
	
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
	if (strstr(slot1, "SummonerSmite"))
	{
		smite = GPluginSDK->CreateSpell2(kSummonerSlot1, kTargetCast, false, false, kCollidesWithNothing);
		smite->SetOverrideRange(550.f);
	}
	if (strstr(slot2, "SummonerSmite"))
	{
		smite = GPluginSDK->CreateSpell2(kSummonerSlot2, kTargetCast, false, false, kCollidesWithNothing);
		smite->SetOverrideRange(550.f);
	}

	zhonyas = GPluginSDK->CreateItemForId(3157, 0);
	blade = GPluginSDK->CreateItemForId(3153, 550);
	Cutlass = GPluginSDK->CreateItemForId(3144, 550);
	Hextech = GPluginSDK->CreateItemForId(3146, 600); 
	protobelt = GPluginSDK->CreateItemForId(3152, 600);
	HealthPot = GPluginSDK->CreateItemForId(2003, 0);
	CorruptPot = GPluginSDK->CreateItemForId(2033, 0);
	RefillPot = GPluginSDK->CreateItemForId(2031, 0);
	Biscuit = GPluginSDK->CreateItemForId(2010, 0);
	hunter = GPluginSDK->CreateItemForId(2032, 0);
}
