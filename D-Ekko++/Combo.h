#pragma once
#include "Damage.h"
#include "Menu.h"
#include "Smite.h"
#include "Items.h"
#include "Extension.h"

inline void Combo()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1500);
	if (Enemy != nullptr && !Enemy->IsDead())
	{
		smitetarget();
		UseItems();
		auto rdmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotR);
		auto wdmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotW);
		auto mana = W->ManaCost() + R->ManaCost();
		auto autodmg = GDamage->GetAutoAttackDamage(myHero, Enemy, true);
		if (Ignite != nullptr)
		{
			if (UseIgnitecombo->Enabled() && Ignite->IsReady())
			{
				if (Enemy->IsValidTarget(myHero, 570))
				{
					if (Enemy->GetHealth() <= TotalDamage(Enemy))
					{
						Ignite->CastOnUnit(Enemy);
					}
				}
			}
		}
		ProtoBelt();
		if (ComboQ->Enabled() && Q->IsReady())
		{
			if (myHero->IsValidTarget(Enemy, Q->Range()))
			{
				AdvPredictionOutput QPred;
				Q->RunPrediction(Enemy, true, kCollidesWithNothing, &QPred);

				if (QPred.HitChance >= kHitChanceVeryHigh)
				{
					Q->CastOnUnit(Enemy);
				}
			}
		}

		if (ComboW->Enabled() && W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
		{
			WLogic(Enemy);
		}
		if (ComboE->Enabled() && E->IsReady())
		{
			auto harasspos = myHero->GetPosition().Extend(GGame->CursorPosition(), E->Range());
			if (myHero->IsValidTarget(Enemy, E->Range() + 475) && GetDistance(myHero->ServerPosition(), Enemy->ServerPosition()) <= E->Range() + 475
				&& UseE(harasspos))
			{
				E->CastOnPosition(harasspos);
				GGame->IssueOrder(GEntityList->Player(), kAutoAttack, Enemy);
			}
		}
		if (ComboR->Enabled() && R->IsReady())
		{
			if (Rpos != nullptr)
			{
				if (Enemy->GetHealth() < TotalDamage(Enemy))
				{					
					if (Enemy->IsValidTarget(Rpos, R->Range()))
					{
						
							R->CastOnPlayer();
						
					}
				}
				if (myHero->HealthPercent() <= 4)
				{
					if (myHero->IsValidTarget(Enemy, Q->Range()))
					{
						auto Qdmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotQ);
						auto Edmg = GDamage->GetSpellDamage(myHero, Enemy, kSlotE);
						auto attack = GDamage->GetAutoAttackDamage(myHero, Enemy, true);
						if (CountEnemiesInRange(W->Range()) <= 1 && Enemy->GetHealth() < Qdmg && Q->IsReady() && Q->CastOnTarget(Enemy, kHitChanceHigh)) return;
						if (CountEnemiesInRange(W->Range()) <= 1 && Enemy->GetHealth() < Edmg && E->IsReady() && UseE(Enemy->GetPosition()) && E->CastOnPosition(Enemy->GetPosition())) return;
						if (CountEnemiesInRange(W->Range()) <= 1 && Enemy->GetHealth() < attack && myHero->GetRealAutoAttackRange(Enemy)) return;
						if (Usezhonyas->Enabled() && zhonyas->IsOwned() && zhonyas->IsReady())
						{
							zhonyas->CastOnPlayer();
							return;
						}
						if ((zhonyas->IsOwned() && !zhonyas->IsReady() || !zhonyas->IsOwned() || !Usezhonyas->Enabled()) && R->IsReady())
						{
							R->CastOnPlayer();
							return;
						}
					}
				}
			}
		}
		if (ComboRAOE  && R->IsReady())
		{
			if (Rpos != nullptr)
			{
				if (CountEnemiesInPositionRange(Rpos->GetPosition(), R->Range()) >= ComboRAOEUse->GetInteger())
				{
					R->CastOnPlayer();
				}
			}
		}
	}
}