#pragma once
#include "Extension.h"
#include "Combo.h"
PLUGIN_EVENT(void) OnProcessCast(CastedSpell const& spell)
{
	if (spell.Caster_ == myHero)
	{
		if (Contains(std::string(spell.Name_), "RengarQ"))
		{
			ResetQ();
		}
		if (Contains(std::string(spell.Name_), "RengarE"))
		{
			ResetE();
		}
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		Combo(spell);
		return;
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
	//	harass(spell);
		return;
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		//laneclear(spell);
		//jungleclear(spell);
	}
}