#pragma once
#include "Extension.h"
#include "EWQ.h"

PLUGIN_EVENT(void) OnProcessSpellCast(CastedSpell const& spell)
{


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