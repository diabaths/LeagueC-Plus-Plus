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
		if (Q->IsReady() && FarmQ->Enabled())
		{
			auto end = GBuffData->GetEndTime(myHero->GetBuffDataByName("RivenTriCleave"));
			auto start = GBuffData->GetStartTime(myHero->GetBuffDataByName("RivenTriCleave"));
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotQ);
			if (minions != nullptr && myHero->IsValidTarget(minions, Q->Range()))
			{
				Vec3 pos;
				int Qhit;
				GPrediction->FindBestCastPosition(Q->Range(), Q->Radius(), true, true, false, pos, Qhit);
				if (Qhit >= 3 && end - GGame->Time() <= 0.2 * (end - start))
				{
					Q->CastOnPosition(pos);
					return;
				}
				if (minions->GetHealth() < dmg)
				{
					Q->CastOnUnit(minions);
					return;
				}
				if (myHero->HasBuff("RivenTriCleave") && end - GGame->Time() <= 0.1 * (end - start))
				{
					Q->CastOnUnit(minions);
					return;
					
				}
			}
		}
		if (W->IsReady() && FarmW->Enabled())
		{
			auto dmg = GDamage->GetSpellDamage(myHero, minions, kSlotW);
			if (minions != nullptr && myHero->IsValidTarget(minions, W->Range()))
			{
				Vec3 pos;
				int Qhit;
				GPrediction->FindBestCastPosition(W->Range(), W->Radius(), true, true, false, pos, Qhit);
				if (Qhit >= 4)
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
					return;
				}

				if (myHero->IsValidTarget(jMinion, 385))

					if (!AutoAttack)
					{
						Tiamat_hydra(jMinion);
						GOrbwalking->ResetAA();
						return;
					}
			}
		}
		if (JungleQ->Enabled() && Q->IsReady())
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
			{
				Q->CastOnUnit(jMinion);
				AutoAttack = true;
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

