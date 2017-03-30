#pragma once
#include "Extensions.h"

PLUGIN_EVENT(void) OnPlayAnimation(IUnit* Source, std::string const Args)
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear || GOrbwalking->GetOrbwalkingMode() == kModeCombo || GetAsyncKeyState(Burst_b->GetInteger()) || GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		if (Source == myHero)
		{
			if (Contains(Args, "56b") || Contains(Args, "58b") || Contains(Args, "59b"))
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("AA_cancel");
				}
				//AAcancel();
			}
			if (Contains(Args, "c29"))
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("AnimQ-1");
				}
				Qstack = 1;
				GOrbwalking->ResetAA();
				ResetQ1();
			}
			if (Contains(Args, "c39"))
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("AnimQ-2");
				}
				Qstack = 2;
				GOrbwalking->ResetAA();
				ResetQ2();
			}
			if (Contains(Args, "c49"))
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("AnimQ-3");
				}
				Qstack = 0;
				GOrbwalking->ResetAA();
				ResetQ3();
			}
			if (Contains(Args, "b5f"))
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("Anim_W");
				}
				GOrbwalking->ResetAA();
				ResetW();
			}
			if (Contains(Args, "bda"))
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("Anim_R2");
				}
				GOrbwalking->ResetAA();
				ResetR2();
			}
		}
	}
}