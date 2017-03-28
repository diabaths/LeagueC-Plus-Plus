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
					GOrbwalking->ResetAA();
				}

				if (myHero->IsValidTarget(minions, 385))

					if (!AutoAttack)
					{
						Tiamat_hydra(minions);
						GOrbwalking->ResetAA();
					}
			}
		}
		if (Q->IsReady() && FarmQ->Enabled() && !AutoAttack)
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
				}
				else if (minions->GetHealth() < dmg)
				{
					Q->CastOnUnit(minions);
				}
				else if (myHero->HasBuff("RivenTriCleave") && end - GGame->Time() <= 0.1 * (end - start))
				{
					Q->CastOnUnit(minions);
				}
			}
		}
		if (W->IsReady() && FarmW->Enabled() && !AutoAttack)
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
				} else if (minions->GetHealth()<dmg) W->CastOnPlayer();

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
		if (JungleQ->Enabled() && Q->IsReady() && !AutoAttack)
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, Q->Range()))
			{
				Q->CastOnUnit(jMinion);
			}
		}
		if (JungleW->Enabled() && W->IsReady() && !AutoAttack)
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, W->Range()))
			{
				W->CastOnPlayer();
			}
		}
		if (JungleE->Enabled() && E->IsReady() && !AutoAttack)
		{
			if (jMinion != nullptr && !jMinion->IsDead() && myHero->IsValidTarget(jMinion, E->Range()))
			{
				E->CastOnPosition(jMinion->GetPosition());
			}
		}
	}
}

