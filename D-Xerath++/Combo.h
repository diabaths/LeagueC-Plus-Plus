#pragma once
#include "Damage.h"
#include "Menu.h"



inline void Combo()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1600);
	if (Enemy != nullptr && !Enemy->IsDead())
	{
		if (Ignite != nullptr)
		{
			if (UseIgnitecombo->Enabled() && Ignite->IsReady())
			{
				if (Enemy->IsValidTarget(myHero, Ignite->Range()))
				{
					if (Enemy->GetHealth() <= 1.4 * TotalDamage(Enemy))
					{
						Ignite->CastOnUnit(Enemy);
						return;
					}
				}
			}
		}		
		if (ComboQ->Enabled() && Q->IsReady())
		{
			if (myHero->IsValidTarget(Enemy, Q->Range()))
			{
				QCast(Enemy);
				return;
			}
		}
		if (ComboW->Enabled() && W->IsReady() && !UltiIsUp)
		{
			if (Enemy->IsValidTarget(myHero, W->Range()))
			{
				MalachiteCast(W, Enemy, kHitChanceHigh);
			}
		}
		if (ComboE->Enabled() && E->IsReady() && !UltiIsUp)
		{
			if (Enemy->IsValidTarget(myHero, E->Range()))
			{
				MalachiteCast(E, Enemy, kHitChanceHigh);
			}
		}
		if (ComboR->Enabled() && R->IsReady())
		{
			if (Enemy->IsValidTarget(myHero, R->Range()))
			{
				if (!UltiIsUp && Enemy->GetHealth() < TotalDamage(Enemy))
				{
					R->CastOnPlayer();
				}

				if (UltiIsUp)
				{
					if (bluetinket->IsOwned() && bluetinket->IsReady())
					{
						if (myHero->IsValidTarget(Enemy, 4000) && !Enemy->IsVisible())
						{
							bluetinket->CastOnPosition(GGame->CursorPosition());
						}
					}
					Rcast(Enemy);
				}
			}
		}
	}
}
