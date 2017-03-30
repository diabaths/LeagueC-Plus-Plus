#pragma once

#include "PluginSDK.h"
#include "Menu.h"

inline void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall | kCollidesWithWalls));
	W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, true, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, static_cast<eCollisionFlags>(kCollidesWithNothing));
	R = GPluginSDK->CreateSpell2(kSlotR, kLineCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall));

	Q->SetOverrideRange(950);
	W->SetOverrideRange(950);
	E->SetOverrideRange(450);
	R->SetOverrideRange(1500);

	Q->SetOverrideDelay(0.25);
	W->SetOverrideDelay(0.35);
	R->SetOverrideDelay(0.25);

	Q->SetOverrideRadius(60);
	W->SetOverrideRadius(150);
	R->SetOverrideRadius(100);
	Q->SetOverrideSpeed(2000);
	W->SetOverrideSpeed(1650);
	R->SetOverrideSpeed(2100);


	auto slot1 = GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot1);
	auto slot2 = GPluginSDK->GetEntityList()->Player()->GetSpellName(kSummonerSlot2);
	if (strcmp(slot1, "SummonerSmite") == 0)
	{
		smite = GPluginSDK->CreateSpell(kSummonerSlot1, 570);
	}
	if (strcmp(slot2, "SummonerSmite") == 0)
	{
		smite = GPluginSDK->CreateSpell(kSummonerSlot2, 570);
	}
	else smite == nullptr;

	blade = GPluginSDK->CreateItemForId(3153, 550);
	Cutlass = GPluginSDK->CreateItemForId(3144, 550);
	Youmuu = GPluginSDK->CreateItemForId(3142, 0);

	HealthPot = GPluginSDK->CreateItemForId(2003, 0);
	CorruptPot = GPluginSDK->CreateItemForId(2033, 0);
	RefillPot = GPluginSDK->CreateItemForId(2031, 0);
	Biscuit = GPluginSDK->CreateItemForId(2010, 0);
	hunter = GPluginSDK->CreateItemForId(2032, 0);
}

