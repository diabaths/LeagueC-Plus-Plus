#pragma once
#include "Extensions.h"

PLUGIN_EVENT(void) OnProcessSpellCast(CastedSpell const& spell)
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range() - 100);

	if (Enemy != nullptr && spell.Caster_ == myHero && GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		if (!GSpellData->IsAutoAttack(spell.Data_) && ComboE->Enabled())// && !myHero->GetBuffDataByName("GravesBasicAttackAmmo2"))
		{
			E->CastOnPosition(Enemy->ServerPosition());
			lastE = GGame->CurrentTick();
		}
		if (std::string(spell.Name_) == "GravesMove")
		{
			ResetE();
			lastE = GGame->CurrentTick();

		}
	}
	if (Enemy != nullptr && spell.Caster_ == myHero && GetAsyncKeyState(Burst_b->GetInteger()))
	{
		if (!GSpellData->IsAutoAttack(spell.Data_))// && !myHero->GetBuffDataByName("GravesBasicAttackAmmo2"))
		{
			E->CastOnPosition(Enemy->ServerPosition());
			lastE = GGame->CurrentTick();
		}
		if (std::string(spell.Name_) == "GravesMove")
		{
			ResetE();
			lastE = GGame->CurrentTick();

		}
		if (myHero->IsDashing() && GGame->CurrentTick() - lastE > 0.01f)
		{
			R->CastOnPosition(Enemy->ServerPosition());
			lastR = GGame->CurrentTick();
			if (!R->IsReady())
			{
				Q->CastOnPosition(Enemy->GetPosition());
			}
		}
		if (std::string(spell.Name_) == "GravesQLineSpell")
		{
			W->CastOnPosition(Enemy->GetPosition());
		}
		if (std::string(spell.Name_) == "GravesChargeShot" && !GSpellData->IsAutoAttack(spell.Data_))
		{
			lastR = GGame->CurrentTick();
			ResetR();
			Q->CastOnPosition(Enemy->GetPosition());
		}
	}
}