#pragma once

#include "Spells.h"
#include "Extensions.h"
#include "Items.h"

inline void Burst()
{
	//auto Enemy = GTargetSelector->GetFocusedTarget();
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
	GGame->IssueOrder(myHero, kAttackUnit, GGame->CursorPosition());
	GOrbwalking->Orbwalk(Enemy, GGame->CursorPosition());
	_Youmuu(Enemy);
	if (Enemy != nullptr  && R->IsReady())
	{
		if (myHero->IsValidTarget(Enemy, 1200) && !myHero->HasBuff("RivenFengShuiEngine") && GetDistance(myHero, Enemy) <= 1000)
		{
			_Youmuu(Enemy);
			R->CastOnPlayer();
		}
	}
	if (!AutoAttack && Enemy != nullptr && !Enemy->IsDead())
	{
		if (UseIgnitecombo->Enabled() && Ignite->IsReady())
		{
			if (Enemy != nullptr && Enemy->IsValidTarget(myHero, 570))
			{
				if (Enemy->HealthPercent() <= 50)
				{
					Ignite->CastOnUnit(Enemy);
				}
			}
		}
		if (myHero->IsValidTarget(Enemy, 1200) && myHero->HasBuff("RivenFengShuiEngine"))
		{
			if (E->IsReady() && GetDistance(myHero->GetPosition(), Enemy->ServerPosition()) < IsInAutoAttackRange(Enemy) + 320)
			{
				E->CastOnPosition(Enemy->GetPosition());
			}
			if (W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
				GPluginSDK->DelayFunctionCall(120, []()
			{
				W->CastOnPlayer();
			});
			if (R->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
			{
				R2->CastOnUnit(Enemy);
			}
		}
	}
}