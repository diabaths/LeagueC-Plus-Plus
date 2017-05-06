#pragma once
#include "Extension.h"

PLUGIN_EVENT(void) OnProcessSpellCast(CastedSpell const& spell)
{
	auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);

	if (spell.Caster_ == myHero)
	{
	}
}