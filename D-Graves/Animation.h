#pragma once
#include "Extensions.h"

/*PLUGIN_EVENTD(void) OnPlayAnimation(IUnit* Source, std::string const AnimationId)
{

	if (Source == GEntityList->Player())
	{
		GGame->PrintChat(AnimationId.c_str());
	}
}*/
PLUGIN_EVENT(void) OnPlayAnimation(IUnit* Source, std::string const Args)
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range() - 100);
	if (Source == myHero)
	{
		if (GetAsyncKeyState(Burst_b->GetInteger()) || GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			if (Contains(Args, "b4f63b8e"))
			{
				lastE = GGame->CurrentTick();
			ResetE();
				if(GetAsyncKeyState(Burst_b->GetInteger()))
				{
					R->CastOnPosition(Enemy->ServerPosition());
				}
			}
			if (Contains(Args, "b7f"))
			{
				lastR = GGame->CurrentTick();
				ResetR();
				if (GetAsyncKeyState(Burst_b->GetInteger()))
				{
					Q->CastOnPosition(Enemy->ServerPosition());
				}
			}
			if (Contains(Args, "bf2"))
			{
				ResetQ();
			}
		}
	}
}

