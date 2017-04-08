#pragma once
#include "Extension.h"


PLUGIN_EVENT(void) OnAfterAttack(IUnit* source, IUnit* target)
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		if (E->IsReady() && ComboE->Enabled() && target->IsHero())
		{
			if (target != nullptr && myHero->IsValidTarget(target, E->Range()))
			{
				AdvPredictionOutput prediction_output;
				E->RunPrediction(target, true, kCollidesWithYasuoWall | kCollidesWithMinions, &prediction_output);
				if (prediction_output.HitChance >= kHitChanceHigh)
				{
					E->CastOnTarget(target);
					GOrbwalking->ResetAA();
					/*if (AlwaysQAfterE->Enabled() && Q->IsReady())
					{
					Q->CastOnTarget(target);
					}*/
				}
			}
		}
	}
}