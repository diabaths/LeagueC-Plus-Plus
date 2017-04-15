#pragma once
#include "Extensions.h"
#include "Items.h"
#include "Burst.h"
PLUGIN_EVENT(void) OnDoCast(CastedSpell const& spell)
{
	/*if (Contains(args.Name_, "ItemTiamatCleave")) forceItem = false;
	if (Contains(args.Name_, "RivenTriCleave")) forceQ = false;
	if (Contains(args.Name_, "RivenMartyr")) forceW = false;
	if (Equals(args.Name_, IsFirstR)) forceR = false;
	if (Equals(args.Name_, IsSecondR)) forceR2 = false;*/

	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);

	if (Enemy != nullptr && spell.Caster_ == myHero && Enemy->IsHero() && (GOrbwalking->GetOrbwalkingMode() == kModeMixed || GOrbwalking->GetOrbwalkingMode() == kModeCombo))
	{		
		if (Q->IsReady() && ComboQ->Enabled())
		{
			if (myHero->IsValidTarget(Enemy, 385) && haveitems())
			{
				if (_tiamat->Enabled() || RHydra->Enabled())
				{

					Tiamat_hydra(Enemy);
					GOrbwalking->ResetAA();
					return;
				}
			}
			if (Qstack == 1 )
			{
				if (Enemy != nullptr && myHero->IsValidTarget(Enemy, Q->Range() + IsInAutoAttackRange(Enemy) + 75))
				{
					if (Debug->Enabled())
					{
						GGame->PrintChat("ONATTACK_1");
					}
					Q->CastOnPosition(Enemy->ServerPosition());
					return;
				}
			}
			if (Qstack == 2 )
			{
				if (Enemy != nullptr && myHero->IsValidTarget(Enemy, Q->Range() + IsInAutoAttackRange(Enemy) + 75))
				{
					if (Debug->Enabled())
					{
						GGame->PrintChat("ONATTACK_2");
					}
					Q->CastOnPosition(Enemy->ServerPosition());
					return;
				}
			}
			if (Qstack == 0 )
			{
				if (Enemy != nullptr && myHero->IsValidTarget(Enemy, Q->Range() + IsInAutoAttackRange(Enemy) + 75))
				{
					if (Debug->Enabled())
					{
						GGame->PrintChat("ONATTACK_3");
					}
					Q->CastOnPosition(Enemy->ServerPosition());
					return;
				}
			}
		}

		/*if (Q->IsReady() && ComboQ->Enabled() && myHero->IsValidTarget(Enemy, Q->Range()) && !AutoAttack)
		{
		if (Debug->Enabled())
		{
		GGame->PrintChat("q_OnDoCast");
		}
		AutoAttack = true;
		Q->CastOnPosition(Enemy->ServerPosition());
		}*/
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && ComboW->Enabled() && !AutoAttack && W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()) &&
			(Qstack != 0 || Enemy->IsMelee() || Enemy->IsFacing(myHero) || !Q->IsReady() ||
				myHero->HasBuff("RivenFeint")))
		{
			if (Debug->Enabled())
			{
				GGame->PrintChat("W_OnDoCast");
			}
			W->CastOnPlayer();
		}
	}
}