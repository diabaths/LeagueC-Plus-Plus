#pragma once
#include "Extension.h"

PLUGIN_EVENT(void) OnProcessSpellCast(CastedSpell const& spell)
{
	auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);

	if (spell.Caster_ == myHero)
	{
		if (std::string(spell.Name_) == "XerathLocusPulse")
		{
			RCastTime = GGame->TickCount();
		}
		if (std::string(spell.Name_) == "SummonerFlash")
		{
			RDashTime = GGame->TickCount();
		}
	}
	if (zhonyas->IsOwned() && zhonyas->IsReady() || W->IsReady())
	{

		if (!spell.Caster_->IsEnemy(myHero) && !myHero->IsValidTarget(spell.Caster_, 1200))
			return;
		if (!spell.Caster_->IsHero() || spell.Caster_ == nullptr)
			return;

		if (spell.Target_ != myHero)
			return;

		if (GSpellData->IsAutoAttack(spell.Data_))
			return;

		if (GSpellData->GetBaseDamage(spell.Data_) > 0.f)
		{

			auto slot = GSpellData->GetSlot(spell.Data_);
			if (slot != kSlotUnknown)
			{
				auto spelldmg = GDamage->GetSpellDamage(spell.Caster_, spell.Target_, slot) * 2;
				if (CountEnemiesInRange(Q->Range()) > 0 && (myHero->GetHealth() < spelldmg || myHero->HealthPercent() < 4))
				{
					if (Usezhonyas->Enabled() && zhonyas->IsOwned() && zhonyas->IsReady())
					{
						zhonyas->CastOnPlayer();
						return;
					}	
				}
			}
		}
	}
}

PLUGIN_EVENT(void) OnCast(CastedSpell const& spell)
{
	if (zhonyas->IsOwned() && zhonyas->IsReady() || W->IsReady())
	{
		if (!spell.Caster_->IsEnemy(myHero) && !myHero->IsValidTarget(spell.Caster_, 1200))
			return;
		if (!spell.Caster_->IsHero() || !spell.Caster_->IsTurret() || spell.Caster_ == nullptr)
			return;

		if (spell.Target_ != myHero)
			return;
		if (!GSpellData->IsAutoAttack(spell.Data_))
			return;

		auto attackdmg = GDamage->GetAutoAttackDamage(spell.Caster_, spell.Target_, true) * 2;
		if (CountEnemiesInRange(Q->Range()) > 0 && (myHero->HealthPercent() < 4 || myHero->GetHealth() < attackdmg))
		{
			if (Usezhonyas->Enabled() && zhonyas->IsOwned() && zhonyas->IsReady())
			{
				zhonyas->CastOnPlayer();
				return;
			}			
		}
	}
}