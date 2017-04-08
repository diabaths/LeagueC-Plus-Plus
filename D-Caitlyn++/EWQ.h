#pragma once
#include "Extension.h"

inline  void burst()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1000);
	GGame->IssueOrder(myHero, kAttackUnit, GGame->CursorPosition());
	GOrbwalking->Orbwalk(Enemy, GGame->CursorPosition());
	auto mana = Q->ManaCost() + E->ManaCost() + W->ManaCost();
	if (Enemy != nullptr && myHero->IsValidTarget(Enemy, W->Range() + W->Radius()) && myHero->GetMana() >= mana)
	{
		AdvPredictionOutput prediction_output;
		E->RunPrediction(Enemy, true, kCollidesWithYasuoWall | kCollidesWithMinions, &prediction_output);

		if (E->IsReady() && prediction_output.HitChance >= kHitChanceHigh)
		{
			Vec3 Enemypos;
			GPrediction->GetFutureUnitPosition(Enemy, 0.5, true, Enemypos);
			E->CastOnPosition(Enemypos);
			if (GGame->CurrentTick() - LastWTick > 500)
			{
				W->CastOnPosition(Enemypos);
			}
			GOrbwalking->ResetAA();
		}
	}
	if (Enemy != nullptr && myHero->IsValidTarget(Enemy, Q->Range() - 50))
	{
		if (Q->IsReady() && Enemy->HasBuff("caitlynyordletrapsight"))
		{
			Q->CastOnTarget(Enemy);
		}
	}
}

inline void processEWQ(CastedSpell const& spell)
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());
	if (spell.Data_ == nullptr) return;
	if (Enemy != nullptr && spell.Caster_ == myHero && GetAsyncKeyState(EWQCombo->GetInteger()))
	{
		if (strstr(spell.Name_, "CaitlynEntrapment") || strstr(spell.Name_, "CaitlynEntrapmentMissile"))
		{
			if (W->IsReady() && myHero->IsValidTarget(Enemy, W->Range() + W->Radius()))
			{
				Vec3 Enemypos;
				GPrediction->GetFutureUnitPosition(Enemy, 0.5, true, Enemypos);
				W->CastOnPosition(Enemypos);
				return;

			}
		}
		if (Q->IsReady() && myHero->IsValidTarget(Enemy, Q->Range() - 100) && Enemy->HasBuff("caitlynyordletrapsight"))
		{
			Q->CastOnUnit(spell.Target_);
		}
	}
}
/*static void burstAfter(IUnit* source, IUnit* target)
{

	if (target != nullptr && myHero->IsValidTarget(target, Q->Range() - 100))
	{
		auto mana = Q->ManaCost() + E->ManaCost() + R->ManaCost();

		if (nowauto)
		{
			R->CastOnPosition(target->ServerPosition());
		}
		if (E->IsReady() && !R->IsReady())
		{
			E->CastOnPosition(target->ServerPosition());
			GOrbwalking->ResetAA();
		}
		if (Q->IsReady() && !R->IsReady())
		{
			Q->CastOnPosition(target->GetPosition());
		}
		if (!Q->IsReady() && W->IsReady() && !R->IsReady())
		{
			W->CastOnPosition(target->GetPosition());
		}
	}
}
*/
