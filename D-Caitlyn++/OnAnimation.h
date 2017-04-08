#pragma once
#include "Extension.h"

PLUGIN_EVENT(void) OnPlayAnimation(IUnit* Source, std::string const Args)
{
	if (Source == myHero &&  Q->IsReady() && !GetAsyncKeyState(USEE->GetInteger()))
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
		
		if (Contains(Args, "b4f"))
		{			
			if (EWQCombo->GetInteger())
			{
				auto enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range() -100);
				Vec3 Enemypos;
				GPrediction->GetFutureUnitPosition(target, 0.1, true, Enemypos);
				W->CastOnPosition(Enemypos);
			}
			if (!GetAsyncKeyState(EWQCombo->GetInteger()) && target != nullptr && AlwaysQAfterE->Enabled() && myHero->IsValidTarget(target, Q->Range()))
			{
				Q->CastOnPosition(target->GetPosition());
			}
		}
	}
}

/*PLUGIN_EVENTD(void) OnPlayAnimation(IUnit* Source, std::string const AnimationId)
{

if (Source == GEntityList->Player())
{
GGame->PrintChat(AnimationId.c_str());
}
}*/
