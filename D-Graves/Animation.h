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
	if (Source == myHero)
	{
		if (GetAsyncKeyState(Burst_b->GetInteger()))
		{
			auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range() + 300);

			if (Contains(Args, "b4f63b8e"))
			{
				ResetE();
			}
			if (Contains(Args, "b7f"))
			{
				ResetR();
			}
			if (Contains(Args, "bf2"))
			{
				ResetQ();
			}
		}
	}
}

