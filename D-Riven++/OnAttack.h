#pragma once
#include "Extensions.h"

PLUGIN_EVENT(void) OnAttack(IUnit* source, IUnit* target)
{
	if (target == nullptr || target == myHero || target->IsDead() && !target->IsHero()) return;
	
	if (target->IsHero() && (GOrbwalking->GetOrbwalkingMode() == kModeMixed || GOrbwalking->GetOrbwalkingMode() == kModeCombo || GetAsyncKeyState(Burst_b->GetInteger())))
	{
		if (Hydra->Enabled())
		{
			if (!AutoAttack)
			{
				Titanic(target);
				GOrbwalking->ResetAA();
			}
		}
		if (Q->IsReady() && ComboQ->Enabled())
		{
			if (myHero->IsValidTarget(target, 385))
				if (_tiamat->Enabled() || RHydra->Enabled())
				{
					if (!AutoAttack)
					{
						Tiamat_hydra(target);
						GOrbwalking->ResetAA();
					}
				}
			if (Qstack == 1 && !AutoAttack)
			{
				if (target != nullptr && myHero->IsValidTarget(target, Q->Range() + IsInAutoAttackRange(target) +75))
				{
					if (Debug->Enabled())
					{
						GGame->PrintChat("ONATTACK_1");
					}					
					Q->CastOnPosition(target->ServerPosition());
					AutoAttack = false;
				}
			}
			if (Qstack == 2 && !AutoAttack)
			{
				if ( target != nullptr && myHero->IsValidTarget(target, Q->Range() + IsInAutoAttackRange(target) +75))
				{
					if (Debug->Enabled())
					{
						GGame->PrintChat("ONATTACK_2");
					}
					Q->CastOnPosition(target->ServerPosition());
					AutoAttack = false;
				}
			}
			if (Qstack == 0 && !AutoAttack)
			{
				if (target != nullptr && myHero->IsValidTarget(target, Q->Range() + IsInAutoAttackRange(target) +75))
				{
					if (Debug->Enabled())
					{
						GGame->PrintChat("ONATTACK_3");
					}
					Q->CastOnPosition(target->ServerPosition());
					AutoAttack = false;
				}
			}
		}
	}
}

