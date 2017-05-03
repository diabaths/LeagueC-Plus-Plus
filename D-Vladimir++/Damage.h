#pragma once
#include "Extension.h"

inline float QDamage(IUnit* Target)
{
	float Damage = 0;
	
	if (myHero->GetSpellLevel(kSlotQ) == 1)
		Damage += 75 + 0.55*myHero->MagicDamage();
	else if (myHero->GetSpellLevel(kSlotQ) == 2)
		Damage += 90 + 0.55*myHero->MagicDamage();
	else if (myHero->GetSpellLevel(kSlotQ) == 3)
		Damage += 105 + 0.55*myHero->MagicDamage();
	else if (myHero->GetSpellLevel(kSlotQ) == 4)
		Damage += 120 + 0.55*myHero->MagicDamage();
	else if (myHero->GetSpellLevel(kSlotQ) == 5)
		Damage += 135 + 0.55*myHero->MagicDamage();

	return Damage;
}

inline float WDamage(IUnit* Target)
{
	float Damage = 0;

	if (myHero->GetSpellLevel(kSlotW) == 1)
		Damage += 80;
	else if (myHero->GetSpellLevel(kSlotW) == 2)
		Damage += 135;
	else if (myHero->GetSpellLevel(kSlotW) == 3)
		Damage += 190;
	else if (myHero->GetSpellLevel(kSlotW) == 4)
		Damage += 245;
	else if (myHero->GetSpellLevel(kSlotW) == 5)
		Damage += 300;

	return Damage;
}

inline float EDamage(IUnit* Target)
{	
	float Damage = 0;

	if (myHero->GetSpellLevel(kSlotE) == 1)
		Damage += 60 + 0.45*myHero->MagicDamage();
	else if (myHero->GetSpellLevel(kSlotE) == 2)
		Damage += 80 + 0.45*myHero->MagicDamage();
	else if (myHero->GetSpellLevel(kSlotE) == 3)
		Damage += 100 + 0.45*myHero->MagicDamage();
	else if (myHero->GetSpellLevel(kSlotE) == 4)
		Damage += 120 + 0.45*myHero->MagicDamage();
	else if (myHero->GetSpellLevel(kSlotE) == 5)
		Damage += 140 + 0.45*myHero->MagicDamage();

	return Damage;
}

inline float RDamage(IUnit* Target)
{
	float Damage = 0;
	
	if (myHero->GetSpellLevel(kSlotR) == 1)
		Damage += 150 + 0.7*myHero->MagicDamage();
	else if (myHero->GetSpellLevel(kSlotR) == 2)
		Damage += 250 + 0.7*myHero->MagicDamage();
	else if (myHero->GetSpellLevel(kSlotR) == 3)
		Damage += 350 + 0.7*myHero->MagicDamage();
	

	return Damage;
}
inline float TotalDamage(IUnit* target)
{
	if (target == nullptr || target->IsDead())
	{
		return 0;
	}

	auto damage = 0;

	if (Q->IsReady())
	{
		damage += QDamage(target);
	}

	if (W->IsReady())
	{
		damage += WDamage(target);
	}
	if (E->IsReady())
	{
		damage += EDamage(target);
	}
	if (R->IsReady())
	{
		damage += RDamage(target);
	}
	damage += 2 * GDamage->GetAutoAttackDamage(myHero, target, true);

	if (Ignite != nullptr&& Ignite->IsReady())
	{
		damage += GDamage->GetSpellDamage(myHero, target, kSummonerSpellIgnite);
	}
	if (target->HasBuff("GarenW"))
	{
		damage = damage * 0.7f;
	}

	if (target->HasBuff("ferocioushowl"))
	{
		damage = damage * 0.7f;
	}

	if (target->HasBuff("BlitzcrankManaBarrierCD") && target->HasBuff("ManaBarrier"))
	{
		damage -= target->GetMana() / 2;
	}
	if (myHero->HasBuff("summonerexhaust"))
	{
		damage *= 0.6f;
	}
	
	if (GEntityList->Player()->HasBuff("LichBane"))
	{
		damage += myHero->TotalPhysicalDamage() *0.75 + myHero->MagicDamage() * 0.5;
	}
	if (protobelt->IsOwned() && protobelt->IsReady())
	{
		auto proto = (79 + 4 * (myHero->GetLevel() - 1)) + 0.25*myHero->MagicDamage();
		damage += proto;
	}
	return static_cast<float>(damage);
}
