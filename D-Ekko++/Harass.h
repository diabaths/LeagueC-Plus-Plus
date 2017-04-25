#pragma once
#include "Extension.h"


inline void Harass()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1500);
	if (myHero->ManaPercent() < HarassManaPercent->GetInteger())
		return;
	if (HarassQ->Enabled())
	{
		if (Q->IsReady())
		{
		if (myHero->IsValidTarget(Enemy, Q->Range()))
			{
				AdvPredictionOutput QPred;
				Q->RunPrediction(Enemy, true, kCollidesWithNothing, &QPred);

				if (QPred.HitChance >= kHitChanceHigh)
				{
					Vec3 Enemypos;
					GPrediction->GetFutureUnitPosition(Enemy, 0.5, true, Enemypos);
					Q->CastOnPosition(Enemypos);
				}
			}
		}
	}
	if (HarassW->Enabled())
	{
		if (W->IsReady())
		{	if (Enemy->IsValidTarget(myHero, W->Range()) && !CanMove(Enemy))
				W->CastOnTarget(Enemy, kHitChanceHigh);
		}
	}
	if (HarassE->Enabled())
	{
		if (E->IsReady())
		{
			auto harasspos = myHero->GetPosition().Extend(GGame->CursorPosition(), E->Range());
			if (myHero->IsValidTarget(Enemy, E->Range() + 475) && GetDistance(myHero->ServerPosition(), Enemy->ServerPosition()) <= E->Range() + 475
				&& UseE(harasspos))
			{
				E->CastOnPosition(harasspos);
				GGame->IssueOrder(GEntityList->Player(), kAutoAttack, Enemy);
			}
		}
	}
}
