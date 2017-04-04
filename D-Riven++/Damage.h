#pragma once
#include "Extensions.h"

inline double GetPassive()
{
	if (myHero->GetLevel() == 18)
	{
		return 0.5;
	}

	if (myHero->GetLevel() >= 15)
	{
		return 0.45;
	}
	if (myHero->GetLevel() >= 12)
	{
		return 0.40;
	}
	if (myHero->GetLevel() >= 9)
	{
		return 0.35;
	}
	if (myHero->GetLevel() >= 6)
	{
		return 0.30;
	}
	if (myHero->GetLevel() >= 3)
	{
		return 0.25;
	}
	return 0.2;
}

/*inline float Rdamage(IUnit* target)
{
	auto damage = 0;
	if (myHero->GetSpellBook()->GetLevel(kSlotR) == 0)
	{
		return 0;
	}
	auto Rlvl = GEntityList->Player()->GetSpellLevel(kSlotR) - 1;
	auto BaseDamage = std::vector<double>({ 80, 120, 160 }).at(Rlvl);
	auto ADMultiplier = 0.6 * GEntityList->Player()->TotalPhysicalDamage() *
		(1 + (target->GetMaxHealth() - target->GetHealth()) / target->GetMaxHealth() > 0.75 ?
			0.75 : ((target->GetMaxHealth() - target->GetHealth()) / target->GetMaxHealth()) * 8 / 3);
	damage += BaseDamage + ADMultiplier;
	return static_cast<float>(damage);
}*/
	
//return target->HasBuff("tristanaecharge") ? GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE) + GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotE) * target->GetBuffCount("tristanaechargesound") * 0.3f : 0.f;
inline float TotalDamage(IUnit* target)
{
	if (target == nullptr || target->IsDead())
	{
		return 0;
	}

	auto damage = 0;

	if (Q->IsReady() || myHero->HasBuff("RivenTriCleave"))
	{
		auto Qhan = 3 - Qstack;
		auto Qhanpassive = Qhan * (1 + GetPassive());
		damage += GDamage->GetSpellDamage(myHero, target, kSlotQ) * Qhan +
			GDamage->GetSpellDamage(myHero, target, kSlotQ)*Qhanpassive;

	}
	
	if (W->IsReady())
	{
		damage += GDamage->GetSpellDamage(myHero, target, kSlotW);
	}
	
	if (R->IsReady())
	{
		damage += GDamage->GetSpellDamage(myHero, target, kSlotR);
		//damage +=Rdamage(target);
	}
	damage += GDamage->GetAutoAttackDamage(myHero, target, true);

	if  (Ignite != nullptr&& Ignite->IsReady())
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
	if (GEntityList->Player()->HasBuff("summonerexhaust"))
		damage *= 0.6f;

	return static_cast<float>(damage);
}
