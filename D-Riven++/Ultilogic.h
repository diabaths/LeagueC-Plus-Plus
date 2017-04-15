#pragma once
#include "Extensions.h"
#include "Damage.h"

static bool isR1()
{
	if (myHero->GetSpellBook()->GetLevel(kSlotR) > 0)
	{
		return strcmp(GEntityList->Player()->GetSpellBook()->GetName(kSlotR), "RivenFengShuiEngine") == 0;
	}
	return false;
}
static bool isR2()
{
	if (myHero->GetSpellBook()->GetLevel(kSlotR) > 0)
	{
		return strcmp(GEntityList->Player()->GetSpellBook()->GetName(kSlotR), "RivenIzunaBlade") == 0;
	}
	return false;
}
static bool R1Logic(IUnit* target)
{
	if (!myHero->IsValidTarget(target, R2->Range()) || !isR1() || !ComboR->Enabled() || target->HealthPercent() <= DmgPercentmin->GetInteger())
	{
		return false;
	}

	return R->CastOnPlayer();
}

static bool R2Logic(IUnit* target)
{
	auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), target, kSlotR);
	auto dmg1 = GDamage->GetAutoAttackDamage(myHero, target, true);
	auto end = GBuffData->GetEndTime(myHero->GetBuffDataByName("RivenFengShuiEngine"));
	auto start = GBuffData->GetStartTime(myHero->GetBuffDataByName("RivenFengShuiEngine"));
	if (!myHero->IsValidTarget(target, R2->Range()) || isR1() || !ComboR2->Enabled())
	{
		return false;
	}

	
		if (end - GGame->Time() <= 0.1 * (end - start) || target->HealthPercent() < 20 || (target->GetHealth() > dmg + dmg1 * 2 && target->HealthPercent() < 40) ||
			(target->GetHealth() <= dmg || (target->GetHealth() <= TotalDamage(target))))
		{
			return R2->CastOnTarget(target, kHitChanceHigh);
		}

	return false;
}
