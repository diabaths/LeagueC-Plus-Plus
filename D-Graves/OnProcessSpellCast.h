#pragma once
#include "Extensions.h"

PLUGIN_EVENT(void) OnProcessSpellCast(CastedSpell const& args)
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range()-100);

	if (Enemy !=nullptr && args.Caster_ == myHero && GetAsyncKeyState(Burst_b->GetInteger()))
	{
		if (std::string(args.Name_) == "GravesMove")
		{
			R->CastOnPosition(Enemy->ServerPosition());
			if (!R->IsReady() && !GSpellData->IsAutoAttack(args.Data_))
			{
				Q->CastOnPosition(Enemy->GetPosition());
			}
		}
		if (std::string(args.Name_) == "GravesQLineSpell")
		{
			W->CastOnPosition(Enemy->GetPosition());
		}
		if (std::string(args.Name_) == "GravesChargeShot" && !GSpellData->IsAutoAttack(args.Data_))
		{
			ResetR();
			Q->CastOnPosition(Enemy->GetPosition());
		}
	}
}
