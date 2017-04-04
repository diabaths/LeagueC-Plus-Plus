#pragma once
#include "Extensions.h"
#include "Burst.h"

PLUGIN_EVENT(void) Afterattack(IUnit* source, IUnit* target)
{
	if (target != nullptr || !target->IsDead() || target->IsHero())
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			afterattackCombo(source, target);
		}
		if (GetAsyncKeyState(Burst_b->GetInteger()))
		{
			afterattackBurst(source, target);
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			afterattackHarass(source, target);
		}
	}
}

