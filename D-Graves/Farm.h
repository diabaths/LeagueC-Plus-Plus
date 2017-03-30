#pragma once
#include "Extensions.h"

inline void LaneClear()
{
	for (auto minions : GEntityList->GetAllMinions(false, true, false))
	{
		if (myHero->ManaPercent() < FarmManaPercent->GetInteger())
			return;
		if (FarmQ->Enabled() && Q->IsReady())
		{
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
			{
				Q->CastOnUnit(minions);
			}
			else Q->LastHitMinion();
		}
		if (FarmW->Enabled() && W->IsReady())
		{
			if (minions != nullptr && myHero->IsValidTarget(minions, W->Range()))
			{
				W->CastOnUnit(minions);
			}
			else W->LastHitMinion();
		}
	}
}

inline void JungleClear()
{
	for (auto jMinion : GEntityList->GetAllMinions(false, false, true))
	{
		if (myHero->ManaPercent() < JungleManaPercent->GetInteger())
			return;
		if (JungleQ->Enabled() && Q->IsReady())
		{
			if (jMinion != nullptr && myHero->IsValidTarget(jMinion, Q->Range()))
			{
				Q->CastOnUnit(jMinion);
			}
		}
		if (JungleW->Enabled() && W->IsReady())
		{
			if (jMinion != nullptr && myHero->IsValidTarget(jMinion, W->Range()))
			{
				W->CastOnUnit(jMinion);
			}
		}
		if (JungleE->Enabled() && E->IsReady())
		{
			if (jMinion != nullptr && myHero->IsValidTarget(jMinion, 500))
			{
				if (!myHero->GetBuffDataByName("GravesBasicAttackAmmo2") && E->IsReady())
					E->CastOnPosition(GGame->CursorPosition());
				GOrbwalking->ResetAA();
			}
		}
	}
}