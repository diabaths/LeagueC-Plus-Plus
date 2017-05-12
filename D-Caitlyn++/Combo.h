#pragma once
#include "Extension.h"

inline void Combo()
{
	if (ComboQ->Enabled())
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		CastQ(target);
	}
	if (ComboW->Enabled() && W->IsReady() && GGame->TickCount() - LastWTick > 2000)
	{
		if (myHero->GetMana() > Q->ManaCost() + E->ManaCost())
		{
			auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range());
			if (myHero->IsValidTarget(Enemy, W->Range()) && Enemy != nullptr && !Enemy->HasBuff("caitlynyordletrapinternal"))
			{
				AdvPredictionOutput prediction_output;
				W->RunPrediction(Enemy, true, kCollidesWithNothing, &prediction_output);
				/*if (prediction_output.HitChance >= kHitChanceVeryHigh && Enemy->IsFacing(myHero))
				{
					auto vector = Enemy->GetPosition() - myHero->GetPosition();
					auto Behind = prediction_output.CastPosition - vector.VectorNormalize() * 100;
					W->CastOnPosition(Behind);
				}
				if (prediction_output.HitChance >= kHitChanceVeryHigh && !Enemy->IsFacing(myHero))
				{
					auto vector = Enemy->GetPosition() - myHero->GetPosition();
					auto Behind = prediction_output.CastPosition + vector.VectorNormalize() * 100;
					W->CastOnPosition(Behind);
				}*/
			}
		}
	}
	if (ComboR->Enabled() && R->IsReady() && GGame->TickCount() - QCastTime > 1000 && !GUtility->IsPositionUnderTurret(myHero->GetPosition()))
	{
		auto Rmin = RMin->GetInteger();
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, RRange);
		if (myHero->IsValidTarget(Enemy, RRange) && Enemy != nullptr)
		{
			auto dmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotR);
			if (Enemy->GetHealth() < dmg && !Enemy->IsInvulnerable() && GetDistance(myHero, Enemy) > Rmin &&  CountEnemiesInRange(RMinenemies->GetInteger()) == 0)
			{
				R->CastOnUnit(Enemy);
			}
		}
	}
}