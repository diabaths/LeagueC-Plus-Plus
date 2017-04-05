#pragma once
#include "Items.h"

inline void jungleclear()
{
	for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
	{
		if (Itemsinlane->Enabled())
		{
			if (jMinion != nullptr && myHero->IsValidTarget(jMinion, 385))
			{
				if (haveitems())
				{
					UseItems(jMinion);
					GOrbwalking->ResetAA();
					return;
				}
			}
		}
		if (JungleQ->Enabled() && Q->IsReady() && !AutoAttack)
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
			{
				Q->CastOnUnit(jMinion);
				return;
			}
		}
		if (JungleW->Enabled() && W->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, W->Range()))
			{
				W->CastOnPlayer();
				return;
			}
		}
		if (JungleE->Enabled() && E->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, E->Range()))
			{
				E->CastOnPosition(jMinion->GetPosition());
				return;
			}
		}
	}
}
