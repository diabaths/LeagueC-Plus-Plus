#pragma once
#include "Spells.h"
#include "Items.h"

inline void Harass()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
	if (Enemy != nullptr)
	{
		auto epos = myHero->GetPosition() + (myHero->GetPosition() - Enemy->GetPosition()).VectorNormalize() * 300;

		if (myHero->IsValidTarget(Enemy, 625) && E->IsReady() && Qstack == 2)
		{
			if (GetDistance(myHero, Enemy) <= 325 + Q->Range() && GetDistance(myHero, Enemy) > IsInAutoAttackRange(Enemy) + 100 && CanMoveMent(myHero))
			{
				if (!myHero->IsDashing() && !AutoAttack)
				{
					E->CastOnPosition(epos);
				}
			}
		}
		if (myHero->IsValidTarget(Enemy, Q->Range()+100) && Q->IsReady() && HarassQ->Enabled() && Qstack == 2 && CanMoveMent(myHero))
		{
			Q->CastOnPosition(epos);
		}
		if (W->IsReady() && HarassW->Enabled() && myHero->IsValidTarget(Enemy, Wrange))
		{
			W->CastOnPlayer();
		
		}
		if (Q->IsReady() && HarassQ->Enabled()  && CanMoveMent(myHero) &&  myHero->IsValidTarget(Enemy, Q->Range()))
		{
			Q->CastOnUnit(Enemy);
		}
		
	}
}