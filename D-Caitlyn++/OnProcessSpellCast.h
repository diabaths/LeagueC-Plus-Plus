#pragma once
#include "Extension.h"
#include "EWQ.h"

PLUGIN_EVENT(void) OnProcessSpellCast(CastedSpell const& spell)
{
	if (spell.Caster_ == myHero &&  Q->IsReady() && !GetAsyncKeyState(USEE->GetInteger()))
	{
		auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

		if (Contains(spell.Name_, "CaitlynEntrapment"))
		{
			if (GetAsyncKeyState(EWQCombo->GetInteger()) || (ComboW->Enabled() && GOrbwalking->GetOrbwalkingMode() == kModeCombo))
			{
				auto enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, W->Range() + W->Radius());
				Vec3 Enemypos;
				GPrediction->GetFutureUnitPosition(enemy, 0.5, true, Enemypos);
				W->CastOnPosition(Enemypos);
			}
			if (!GetAsyncKeyState(EWQCombo->GetInteger()) && target != nullptr && AlwaysQAfterE->Enabled() && myHero->IsValidTarget(target, Q->Range()))
			{
				Q->CastOnPosition(target->GetPosition());
			}
		}
	}
	if (spell.Caster_ == myHero)
	{
		if (std::string(spell.Name_) == "CaitlynYordleTrap")
		{
			LastWTick = GGame->TickCount();
		}

		if (std::string(spell.Name_) == "CaitlynPiltoverPeacemaker" || std::string(spell.Name_) == "CaitlynEntrapment")
		{
			QCastTime = GGame->TickCount();
		}
	}
	if (spell.Caster_->IsEnemy(myHero))
	{
		if (std::string(spell.Name_) == "summonerflash" && GetDistance(myHero, spell.Caster_) < 300 && E->IsReady() && myHero->IsValidTarget(spell.Caster_, E->Range()))
		{
			E->CastOnPosition(spell.EndPosition_);
		}
	}
	if (GetAsyncKeyState(EWQCombo->GetInteger()))
	{
		processEWQ(spell);
	}
	/*if (GSpellData->GetSlot(args.Data_) == kSlotW)
	{
	LastWTick = GGame->TickCount();
	GGame->PrintChat("Last W");
	}*/
}