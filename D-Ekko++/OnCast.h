#pragma once
#include "Extension.h"

PLUGIN_EVENT(void) OnCast(CastedSpell const& spell)
{
	if (zhonyas->IsOwned() && zhonyas->IsReady() || R->IsReady())
	{
		if (!spell.Caster_->IsEnemy(myHero) && !myHero->IsValidTarget(spell.Caster_, W->Range()))
			return;
		if (!spell.Caster_->IsHero() || !spell.Caster_->IsTurret() || spell.Caster_ == nullptr)
			return;
		
		if (spell.Target_ !=myHero)
			return;
		if (!GSpellData->IsAutoAttack(spell.Data_))
			return;
				
		auto attackdmg = GDamage->GetAutoAttackDamage(spell.Caster_, spell.Target_, true)*2;
		if (CountEnemiesInRange(W->Range()) > 0 && (myHero->HealthPercent() < 4 || myHero->GetHealth() < attackdmg))
		{
			if (Usezhonyas->Enabled() && zhonyas->IsOwned() && zhonyas->IsReady())
			{
				zhonyas->CastOnPlayer();
				return;
			}
			if ((zhonyas->IsOwned() && !zhonyas->IsReady() || !zhonyas->IsOwned() || !Usezhonyas->Enabled()) && Ultisave->Enabled() && R->IsReady())
			{
				R->CastOnPlayer();
			}
		}
	}
}