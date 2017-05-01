#pragma once
#include "Extension.h"

inline float TotalDamage(IUnit* target)
{
	if (target == nullptr || target->IsDead())
	{
		return 0;
	}

	auto damage = 0;

	if (Q->IsReady())
	{
		damage += 2 * GDamage->GetSpellDamage(myHero, target, kSlotQ);
	}

	if (W->IsReady())
	{
		damage += GDamage->GetSpellDamage(myHero, target, kSlotW);
	}
	if (E->IsReady())
	{
		damage += GDamage->GetSpellDamage(myHero, target, kSlotE);
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
	return static_cast<float>(damage);
}
