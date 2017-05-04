#pragma once
#include "Spells.h"
#include "Items.h"

inline void Harass()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
	if (Enemy != nullptr && !Enemy->IsDead())
	{
		if (HarassMode->GetInteger() == 0)
		{
			auto epos = myHero->GetPosition() + (myHero->GetPosition() - Enemy->GetPosition()).VectorNormalize() * E->Range();
			if (E->IsReady() && Qstack == 2 && HarassE->Enabled())
			{
				E->CastOnPosition(myHero->GetPosition().Extend(epos, E->Range()).VectorNormalize());
			}

			if (Q->IsReady() && HarassQ->Enabled() && CanMoveMent(myHero) && Qstack == 2)
			{
				GPluginSDK->DelayFunctionCall(100, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (Enemy != nullptr && !Enemy->IsDead())
					{
						auto epos = myHero->GetPosition() + (myHero->GetPosition() - Enemy->GetPosition()).VectorNormalize() * E->Range();
						Q->CastOnPosition(myHero->GetPosition().Extend(epos, E->Range()).VectorNormalize());
					}
				});
			}
			if (W->IsReady() && HarassW->Enabled() && myHero->IsValidTarget(Enemy, W->Range()) && Qstack == 1)
			{
				W->CastOnPlayer();
			}


			if (Q->IsReady() && HarassQ->Enabled())
			{
				if (Qstack == 0 && myHero->IsValidTarget(Enemy, Q->Range() + myHero->GetRealAutoAttackRange(Enemy)))
				{
					Q->CastOnPosition(Enemy->ServerPosition());
					GOrbwalking->GetLastTarget();
				}

				if (Qstack == 1 && GGame->CurrentTick() - LastQ > 600)
				{
					Q->CastOnPosition(Enemy->ServerPosition());
					GOrbwalking->GetLastTarget();
				}
			}
		}
		if (HarassMode->GetInteger() == 1)
		{
			if (E->IsReady() && HarassE->Enabled() && GetDistance(myHero, Enemy) <= 325 + Q->Range() && GetDistance(myHero, Enemy) > IsInAutoAttackRange(Enemy) + 100 && CanMoveMent(myHero))
			{
				E->CastOnPosition(Enemy->GetPosition());
			}

			if (Q->IsReady() && HarassQ->Enabled() && myHero->IsValidTarget(Enemy, Q->Range() + myHero->GetRealAutoAttackRange(Enemy)) && Qstack == 0 &&
				GGame->CurrentTick() - LastQ > 500)
			{
				Q->CastOnPosition(Enemy->ServerPosition());
				GOrbwalking->GetLastTarget();
			}

			if (W->IsReady() && HarassW->Enabled() && myHero->IsValidTarget(Enemy, W->Range()) && (!Q->IsReady() || Qstack == 1))
			{
				W->CastOnPlayer();
			}
		}
	}
}

static void afterattackHarass(IUnit* source, IUnit* target)
{
	if (target == nullptr || !target->IsValidTarget())
		return;

	if (HarassQ->Enabled() && Q->IsReady())
	{
		if (HarassMode->GetInteger() == 0)
		{
			if (Qstack == 1)
			{
				Q->CastOnPosition(target->ServerPosition());
			}
		}
		if (HarassMode->GetInteger() == 1)
		{
			Q->CastOnPosition(target->ServerPosition());
		}
	}
}

