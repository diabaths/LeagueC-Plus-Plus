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
				if (!AutoAttack)
				{
					UseItems(jMinion);
					GOrbwalking->ResetAA();
				}
			}
		}
		if (JungleQ->Enabled() && Q->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
			{
				Q->CastOnUnit(jMinion);
			}
		}
		if (JungleW->Enabled() && W->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, W->Range()))
			{
				W->CastOnPlayer();
			}
		}
		if (JungleE->Enabled() && E->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, E->Range()))
			{
				E->CastOnPosition(jMinion->GetPosition());
			}
		}
	}
}
