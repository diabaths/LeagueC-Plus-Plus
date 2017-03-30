#pragma once
#include "Extensions.h"

inline float TotalDamage(IUnit* target)
{
	if (target == nullptr || target->IsDead())
	{
		return 0;
	}

	auto damage = 0;

	if (Q->IsReady())
	{		
		damage += GDamage->GetSpellDamage(myHero, target, kSlotQ);
	}

	if (W->IsReady())
	{
		damage += GDamage->GetSpellDamage(myHero, target, kSlotW);
	}

	if (R->IsReady())
	{
		auto Rlvl = GEntityList->Player()->GetSpellLevel(kSlotR) - 1;
		auto BaseDamage = std::vector<double>({ 200, 320, 440 }).at(Rlvl);
		auto ADMultiplier = 1.1 * GEntityList->Player()->TotalPhysicalDamage();
		auto TotalD = BaseDamage + ADMultiplier;
		damage += TotalD;
		//damage +=Rdamage(target);
	}
	damage += GDamage->GetAutoAttackDamage(myHero, target, true);
		
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
	if (GEntityList->Player()->HasBuff("summonerexhaust"))
		damage *= 0.6f;

	return static_cast<float>(damage);
}
