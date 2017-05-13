#pragma once
#include "Items.h"

inline void laneclear()
{
	for (auto minions : GEntityList->GetAllMinions(false, true, false))
	{
		
		if (W->IsReady() && FarmW->Enabled())
		{
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotW);
			if (minions != nullptr && myHero->IsValidTarget(minions, W->Range()))
			{
				Vec3 pos;
				int Whit;
				GPrediction->FindBestCastPosition(W->Range(), W->Radius(), false, true, false, pos, Whit);
				if (Whit >= 3)
				{
					W->CastOnPlayer();
					return;
				}
				if (minions->GetHealth() < dmg)
				{
					W->CastOnPlayer();
					return;
				}

			}
		}
		if (Itemsinlane->Enabled())
		{
			if (minions != nullptr && myHero->IsValidTarget(minions, 385))
			{
				if (haveitems())
				{
					UseItems(minions);
					return;
				}
			}
		}
	}
}

inline void afterattacklane(IUnit* source, IUnit* target)
{
	for (auto minions : GEntityList->GetAllMinions(false, true, false))
	{		
		if (Q->IsReady() && FarmQ->Enabled())
		{
			auto end = GBuffData->GetEndTime(myHero->GetBuffDataByName("RivenTriCleave"));
			auto start = GBuffData->GetStartTime(myHero->GetBuffDataByName("RivenTriCleave"));
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
			auto qPosition = GEntityList->Player()->ServerPosition() + GEntityList->Player()->Direction() * (Q->Range() + 100);
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
			{
				Vec3 pos;
				int Qhit;
				GPrediction->FindBestCastPosition(Q->Range(), Q->Radius(), false, true, false, pos, Qhit);

				if (Qhit >= 2 && GGame->TickCount() - LastQ > 1400)
				{
					Q->CastOnPosition(GGame->CursorPosition());
					return;
				}
				if (minions->GetHealth() < dmg && GGame->TickCount() - LastQ > 700)
				{
					Q->CastOnPosition(GGame->CursorPosition());
					return;
				}
				if (myHero->HasBuff("RivenTriCleave") && end - GGame->Time() <= 0.1 * (end - start))
				{
					Q->CastOnPosition(GGame->CursorPosition());
					return;
				}
			}
		}
	}
}