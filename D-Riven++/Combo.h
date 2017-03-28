#pragma once
#include "Spells.h"
#include "Extensions.h"
#include "Damage.h"

inline void Combo()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
	if (Ignite != nullptr)
	{
		if (UseIgnitecombo->Enabled() && Ignite->IsReady())
		{
			if (Enemy != nullptr && Enemy->IsValidTarget(myHero, 570))
			{
				if (Enemy->HealthPercent() <= 30)
				{
					Ignite->CastOnUnit(Enemy);
				}
			}
		}
	}
	_Youmuu(Enemy);
	if (!AutoAttack && Enemy != nullptr && myHero->IsValidTarget(Enemy, 650) && ComboE->Enabled() && E->IsReady() && GetDistance(myHero, Enemy) <= 650 &&
		GetDistance(myHero, Enemy) > IsInAutoAttackRange(Enemy) + 100 && CanMoveMent(myHero))
	{
		if (Debug->Enabled())
		{
			GGame->PrintChat("E_COMBO");
		}
		ELogic(Enemy);
	}
	if (ComboQ->Enabled() && Q->IsReady() && Enemy != nullptr)
	{
		if (CanMoveMent(myHero) && Qstack == 0 &&
			GetDistance(myHero, Enemy) <= 310 + IsInAutoAttackRange(Enemy) &&
			GetDistance(myHero, Enemy) > IsInAutoAttackRange(Enemy) + 50 &&
			GGame->CurrentTick() - LastQ > 900)
		{
			if (!myHero->IsDashing() && !AutoAttack)
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("Q_COMBO");
				}
				Q->CastOnPosition(Enemy->ServerPosition());
				AutoAttack = false;
			}
		}
	}
	if (!AutoAttack && ComboW->Enabled() && W->IsReady() &&
		myHero->IsValidTarget(Enemy, Wrange))
	{
		WLogic(Enemy);
		return;
	}
	if (Enemy != nullptr  && R->IsReady())
	{
		{
			if (ComboR->Enabled() && myHero->IsValidTarget(Enemy, R2->Range()) && !myHero->HasBuff("RivenFengShuiEngine") && CountEnemiesInRange(500) >= 1)
			{
				R->CastOnPlayer();
			}

			if (ComboR2->Enabled() && myHero->HasBuff("RivenFengShuiEngine") && myHero->IsValidTarget(Enemy, R2->Range()) && R2->IsReady())
			{
				auto end = GBuffData->GetEndTime(myHero->GetBuffDataByName("RivenFengShuiEngine"));
				auto start = GBuffData->GetStartTime(myHero->GetBuffDataByName("RivenFengShuiEngine"));
				auto Rlvl = GEntityList->Player()->GetSpellLevel(kSlotR) - 1;
				auto BaseDamage = std::vector<double>({ 80, 120, 160 }).at(Rlvl);
				auto ADMultiplier = 0.6 * GEntityList->Player()->TotalPhysicalDamage() *
					(1 + (Enemy->GetMaxHealth() - Enemy->GetHealth()) / Enemy->GetMaxHealth() > 0.75 ?
						0.75 : ((Enemy->GetMaxHealth() - Enemy->GetHealth()) / Enemy->GetMaxHealth()) * 8 / 3);
				auto damage = BaseDamage + ADMultiplier;
				auto dmg = GDamage->GetSpellDamage(GEntityList->Player(), Enemy, kSlotR);
				if (!Enemy->IsInvulnerable() && Enemy->GetHealth() *1.2< dmg)
				{
					R2->CastOnUnit(Enemy);
				}
				else if (end - GGame->Time() <= 0.1 * (end - start))
				{
					R2->CastOnUnit(Enemy);
				}
			}
		}
	}
}
