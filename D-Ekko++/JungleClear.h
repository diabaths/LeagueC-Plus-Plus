#pragma once
#include "Items.h"

inline void jungleclear()
{	
		for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
		{
			if (UseProtojungle->Enabled() && myHero->IsValidTarget(jMinion, 600))
			{
				if (protobelt->IsOwned() && protobelt->IsReady())
					protobelt->CastOnPosition(jMinion->GetPosition());
			}
			if (myHero->ManaPercent() < JungleManaPercent->GetInteger())
				return;
			if (!strstr(jMinion->GetObjectName(), "mini"))
			{
				if (JungleW->Enabled() && W->IsReady())
				{
					if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, W->Range()))
					{
						W->CastOnPosition(jMinion->GetPosition());
						return;
					}
				}

				if (JungleQ->Enabled() && Q->IsReady())
				{
					if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
					{
						Q->CastOnUnit(jMinion);
						return;
					}
				}

				if (JungleE->Enabled() && E->IsReady())
				{
					if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, E->Range()))
					{
						E->CastOnPosition(jMinion->GetPosition());
						GGame->IssueOrder(myHero, kAttackUnit, GGame->CursorPosition());
						return;
					}
				}
			}
		}
	}