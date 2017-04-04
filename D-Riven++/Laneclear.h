#pragma once
#include "Items.h"

inline void laneclear()
{
	for (auto minions : GEntityList->GetAllMinions(false, true, false))
	{
		if (Itemsinlane->Enabled())
		{
			if (minions != nullptr && myHero->IsValidTarget(minions, 385))
			{
				if (!AutoAttack)
				{
					UseItems(minions);
					GOrbwalking->ResetAA();
				}
			}
		}
		if (Q->IsReady() && FarmQ->Enabled() && GOrbwalking->CanMove(10))
		{
			auto end = GBuffData->GetEndTime(myHero->GetBuffDataByName("RivenTriCleave"));
			auto start = GBuffData->GetStartTime(myHero->GetBuffDataByName("RivenTriCleave"));
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
			auto qPosition = GEntityList->Player()->ServerPosition() + GEntityList->Player()->Direction() * (Q->Range() + 100);
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()) && !GUtility->IsPositionUnderTurret(qPosition))
			{
				int MinionQ = 0;
				if (minions->IsValidTarget(myHero, Q->Range()))
					MinionQ++;

				if (MinionQ >= 3 && GGame->CurrentTick() -LastQ > 100)
				{
					Q->CastOnPosition(GGame->CursorPosition());
					LastQ = GGame->CurrentTick();
				}
				if (minions->GetHealth() < dmg && GGame->CurrentTick() - LastQ > 100)
				{
					Q->CastOnPosition(GGame->CursorPosition());
					LastQ = GGame->CurrentTick();
				}
				if (myHero->HasBuff("RivenTriCleave") && end - GGame->Time() <= 0.1 * (end - start))
				{
					Q->CastOnPosition(GGame->CursorPosition());
					LastQ = GGame->CurrentTick();
				}
			}
		}
		if (W->IsReady() && FarmW->Enabled())
		{
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotW);
			if (minions != nullptr && myHero->IsValidTarget(minions, W->Range()))
			{
				int MinionW = 0;
				if (minions->IsValidTarget(myHero, W->Range()))
					MinionW++;
				if (MinionW >= 4)
				{
					W->CastOnPlayer();
				}
				if (minions->GetHealth() < dmg)
				{
					W->CastOnPlayer();
				}

			}
		}
	}
}

