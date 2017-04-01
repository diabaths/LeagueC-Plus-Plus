#pragma once
#include "PluginSDK.h"
#include "Menu.h"

ISpell2* Q;
ISpell2* W;
ISpell2* E;
ISpell2* R;
ISpell2* R2;
ISpell* Ignite;

float Wrange;

inline void LoadSpells()
{
	Q = GPluginSDK->CreateSpell2(kSlotQ, kTargetCast, false, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	W->SetOverrideRange(260);

	W = GPluginSDK->CreateSpell2(kSlotW, kTargetCast, true, true, static_cast<eCollisionFlags>(kCollidesWithNothing));
	W->SetOverrideRange(Wrange);

	E = GPluginSDK->CreateSpell2(kSlotE, kLineCast, true, false, static_cast<eCollisionFlags> (kCollidesWithYasuoWall | kCollidesWithMinions));
	E->SetSkillshot(0.f, 0.f, 1450.f, 325.f);

	R = GPluginSDK->CreateSpell2(kSlotR, kTargetCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall | kCollidesWithHeroes));

	R2 = GPluginSDK->CreateSpell2(kSlotR, kConeCast, true, true, static_cast<eCollisionFlags>(kCollidesWithYasuoWall | kCollidesWithHeroes));
	R2->SetSkillshot(0.25f, 60.f, 2200.f, 900.f);

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

	Titanic_Hydra = GPluginSDK->CreateItemForId(3748, 385);
	Ravenous_Hydra = GPluginSDK->CreateItemForId(3074, 385);
	Tiamat = GPluginSDK->CreateItemForId(3077, 385);
	Youmuu = GPluginSDK->CreateItemForId(3142, 0);
	blade = GPluginSDK->CreateItemForId(3153, 550);
	Cutlass = GPluginSDK->CreateItemForId(3144, 550);
	HealthPot = GPluginSDK->CreateItemForId(2003, 0);
	CorruptPot = GPluginSDK->CreateItemForId(2033, 0);
	RefillPot = GPluginSDK->CreateItemForId(2031, 0);
	Biscuit = GPluginSDK->CreateItemForId(2010, 0);
	hunter = GPluginSDK->CreateItemForId(2032, 0);
}
