#pragma once
#include "Extensions.h"
#include "Items.h"
PLUGIN_EVENT(void) OnDoCast(CastedSpell const& spell)
{
	/*if (Contains(args.Name_, "ItemTiamatCleave")) forceItem = false;
	if (Contains(args.Name_, "RivenTriCleave")) forceQ = false;
	if (Contains(args.Name_, "RivenMartyr")) forceW = false;
	if (Equals(args.Name_, IsFirstR)) forceR = false;
	if (Equals(args.Name_, IsSecondR)) forceR2 = false;*/

	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
	if (Enemy !=nullptr && spell.Caster_ == myHero && Enemy->IsHero()  && (GOrbwalking->GetOrbwalkingMode() == kModeMixed || GOrbwalking->GetOrbwalkingMode() == kModeCombo || GetAsyncKeyState(Burst_b->GetInteger())))
	{
		if (Hydra->Enabled())
		{
			
				Titanic(Enemy);
				GOrbwalking->ResetAA();
			
		}
		if (Q->IsReady() && ComboQ->Enabled() && (!W->IsReady() || !ComboW->Enabled()))
		{
			if (myHero->IsValidTarget(Enemy, 385))
				if (_tiamat->Enabled() || RHydra->Enabled())
				{
					
						Tiamat_hydra(Enemy);
						GOrbwalking->ResetAA();
					
				}
			if (Qstack == 1)
			{
				if (Enemy != nullptr && myHero->IsValidTarget(Enemy, Q->Range() + IsInAutoAttackRange(Enemy) + 75))
				{
					if (Debug->Enabled())
					{
						GGame->PrintChat("ONATTACK_1");
					}
					Q->CastOnPosition(Enemy->ServerPosition());
					
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
		if (!AutoAttack && W->IsReady() && myHero->IsValidTarget(Enemy, Wrange) && (Qstack != 0 || Enemy->IsMelee() || Enemy->IsFacing(myHero) || !Q->IsReady() ||
			myHero->HasBuff("RivenFeint")))
		{
			if (Debug->Enabled())
			{
				GGame->PrintChat("W_OnDoCast");
			}
			W->CastOnPlayer();
		}
		if (!AutoAttack && myHero->IsValidTarget(Enemy, 650) && E->IsReady() && ComboE->Enabled() && GetDistance(myHero, Enemy) <= 650
			&& GetDistance(myHero, Enemy) > IsInAutoAttackRange(Enemy) + 100 && CanMoveMent(myHero))
		{
			if (Debug->Enabled())
			{
				GGame->PrintChat("E_OnDoCast");
			}
			ELogic(Enemy);
		}
	}
}