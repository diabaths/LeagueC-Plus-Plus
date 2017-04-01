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
					Titanic(minions);
					Tiamat_hydra(minions);
					GOrbwalking->ResetAA();
				}
			}
		}
		if (Q->IsReady() && FarmQ->Enabled() && GOrbwalking->CanMove(true))
		{
			auto end = GBuffData->GetEndTime(myHero->GetBuffDataByName("RivenTriCleave"));
			auto start = GBuffData->GetStartTime(myHero->GetBuffDataByName("RivenTriCleave"));
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
			{
				int MinionQ = 0;
				if (minions->IsValidTarget(myHero, Q->Range()))
					MinionQ++;

				if (MinionQ >= 3 && GGame->CurrentTick() -LastQ > 100)
				{
					Q->CastOnPosition(GGame->CursorPosition());
					LastQ = GGame->CurrentTick();
					return;
				}
				if (minions->GetHealth() < dmg && GGame->CurrentTick() - LastQ > 100)
				{
					Q->CastOnPosition(GGame->CursorPosition());
					LastQ = GGame->CurrentTick();
					return;
				}
				if (myHero->HasBuff("RivenTriCleave") && end - GGame->Time() <= 0.1 * (end - start))
				{
					Q->CastOnPosition(GGame->CursorPosition());
					LastQ = GGame->CurrentTick();
					return;
					
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
					return;
				}
				if (minions->GetHealth() < dmg)
				{
					W->CastOnPlayer();
					return;
				}

			}
		}
	}
}

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
					Titanic(jMinion);
					GOrbwalking->ResetAA();
				}

				if (myHero->IsValidTarget(jMinion, 385))

					if (!AutoAttack)
					{
						Tiamat_hydra(jMinion);
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

