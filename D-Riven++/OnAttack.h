#pragma once
#include "Extensions.h"
#include "Items.h"
static void Onattack(IUnit* source, IUnit* target)
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);

	if (target != nullptr && target->IsValidTarget() && !target->IsDead() && target->IsHero() &&
		(GOrbwalking->GetOrbwalkingMode() == kModeMixed || GOrbwalking->GetOrbwalkingMode() == kModeCombo))
	{
		if (Q->IsReady() && ComboQ->Enabled())
		{
			if (haveitems() && myHero->IsValidTarget(Enemy, 380))
			{
				if (_tiamat->Enabled())
				{
					if (Tiamat->IsOwned() && Tiamat->IsReady())
					{
						Tiamat->CastOnPlayer();
						GOrbwalking->ResetAA();
						return;
					}
				}
				if (RHydra->Enabled())
				{
					if (Ravenous_Hydra->IsOwned() && Ravenous_Hydra->IsReady())
					{
						Ravenous_Hydra->CastOnPlayer();
						GOrbwalking->ResetAA();
					}
				}
				if (Hydra->Enabled())
				{
					if (Titanic_Hydra->IsOwned() && Titanic_Hydra->IsReady())
					{
						Titanic_Hydra->CastOnTarget(Enemy);
						GOrbwalking->ResetAA();
					}
				}
			}
			if (Qstack == 1)
			{
				if (Enemy != nullptr && myHero->IsValidTarget(Enemy, Q->Range() + IsInAutoAttackRange(Enemy) + 75))
				{
					if (Debug->Enabled())
					{
						GGame->PrintChat("ONATTACK_1");
					}
					Q->CastOnPosition(Enemy->GetPosition());
					return;
				}
			}
			if (Qstack == 2)
			{
				if (Enemy != nullptr && myHero->IsValidTarget(Enemy, Q->Range() + IsInAutoAttackRange(Enemy) + 75))
				{
					if (Debug->Enabled())
					{
						GGame->PrintChat("ONATTACK_2");
					}
					Q->CastOnPosition(Enemy->GetPosition());
					return;
				}
			}
			if (Qstack == 0)
			{
				if (Enemy != nullptr && myHero->IsValidTarget(Enemy, Q->Range() + IsInAutoAttackRange(Enemy) + 75))
				{
					if (Debug->Enabled())
					{
						GGame->PrintChat("ONATTACK_3");
					}
					Q->CastOnPosition(Enemy->GetPosition());
					return;
				}
			}
		}
	}
}