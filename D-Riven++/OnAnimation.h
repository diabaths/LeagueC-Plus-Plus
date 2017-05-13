#pragma once
#include "Extensions.h"

PLUGIN_EVENT(void) OnPlayAnimation(IUnit* Source, std::string const Args)
{
	/*if (Autoattackanimation->Enabled() && Source == myHero &&(GetAsyncKeyState(Burst_b->GetInteger())|| GOrbwalking->GetOrbwalkingMode() == kModeCombo))
	{
		if (Contains(Args, "56b") || Contains(Args, "58b") || Contains(Args, "59b"))
		{
			if (Debug->Enabled())
			{
				GGame->PrintChat("AA_cancel");
			}
			AAcancel();
		}
	}*/
	if (ManualAACancel->Enabled() || GOrbwalking->GetOrbwalkingMode() == kModeLaneClear|| GOrbwalking->GetOrbwalkingMode() == kModeCombo || GetAsyncKeyState(Burst_b->GetInteger()) || GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		if (Source == myHero)
		{			
			if (Contains(Args, "c29"))
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("AnimQ-1");
				}
				//ResetQ1();
				return;
			}
			if (Contains(Args, "c39"))
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("AnimQ-2");
				}
				//Qstack = 2;
				//ResetQ2();
				return;
			}
			if (Contains(Args, "c49"))
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("AnimQ-3");
				}
				//Qstack = 0;
				//ResetQ3();
				return;
			}
			if (Contains(Args, "b4f"))
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("Anim_W");
				}
				//ResetW();
				return;
			}
			if (Contains(Args, "bea6"))
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("Anim_R1");
				}
				//ResetR1();
			}
			if (Contains(Args, "bda"))
			{
				if (Debug->Enabled())
				{
					GGame->PrintChat("Anim_R2");
				}
				//ResetR2();
			}
		}
	}
}