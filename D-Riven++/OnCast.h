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
	if (ManualAACancel->Enabled() || GOrbwalking->GetOrbwalkingMode() == kModeLaneClear || GOrbwalking->GetOrbwalkingMode() == kModeCombo || GetAsyncKeyState(Burst_b->GetInteger()) || GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		if (spell.Caster_ == myHero && std::string(spell.Name_) == "RivenIzunaBlade")
		{
			ResetR2();
		}
	}
	if (Enemy != nullptr && spell.Caster_ == myHero && Enemy->IsHero() && (GOrbwalking->GetOrbwalkingMode() == kModeMixed || GOrbwalking->GetOrbwalkingMode() == kModeCombo))
	{		
		

		/*if (Q->IsReady() && ComboQ->Enabled() && myHero->IsValidTarget(Enemy, Q->Range()) && !AutoAttack)
		{
		if (Debug->Enabled())
		{
		GGame->PrintChat("q_OnDoCast");
		}
		AutoAttack = true;
		Q->CastOnPosition(Enemy->ServerPosition());
		}*/
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo && ComboW->Enabled() &&  W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()) &&
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