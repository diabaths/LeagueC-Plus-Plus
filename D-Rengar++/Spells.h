#pragma once
#include "Menu.h"

inline void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kConeCast, false, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	Q->SetOverrideRange(450.f);

	W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, false, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));
	W->SetOverrideRange(450.f);

	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, static_cast<eCollisionFlags>(kCollidesWithYasuoWall | kCollidesWithMinions));
	E->SetSkillshot(0.125f, 70.f, 1500.f, 980.f);

	R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	R->SetOverrideRange(2000);
	auto slot1 = GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1);
	auto slot2 = GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2);

	if (strstr(slot1, "SummonerDot"))
	{
		Ignite = GPluginSDK->CreateSpell2(kSummonerSlot1, kTargetCast, false, false, kCollidesWithNothing);
		Ignite->SetOverrideRange(600.f);
	}
	if (strstr(slot2, "SummonerDot"))
	{
		Ignite = GPluginSDK->CreateSpell2(kSummonerSlot2, kTargetCast, false, false, kCollidesWithNothing);
		Ignite->SetOverrideRange(600.f);
	}
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
