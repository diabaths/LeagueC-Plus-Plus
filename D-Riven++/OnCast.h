#pragma once
#include "Extensions.h"
#include "Items.h"
PLUGIN_EVENT(void) OnDoCast(CastedSpell const& spell)
{
	if (spell.Target_ == nullptr) return;
	/*if (Contains(args.Name_, "ItemTiamatCleave")) forceItem = false;
	if (Contains(args.Name_, "RivenTriCleave")) forceQ = false;
	if (Contains(args.Name_, "RivenMartyr")) forceW = false;
	if (Equals(args.Name_, IsFirstR)) forceR = false;
	if (Equals(args.Name_, IsSecondR)) forceR2 = false;*/
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && myHero->IsWindingUp() && spell.Caster_ == myHero)
	{
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);

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