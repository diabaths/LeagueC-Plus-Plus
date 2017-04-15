#pragma once

#include "ShyCombo.h"
#include "WerhliCombo.h"
#include "Sexy.h"
#include "nidalee.h"


inline void Burst()
{
	if (BurstMode == 0)
	{
		Burstshy(); 
		return;
	}
	if (BurstMode == 1)
	{
		Werhli();
		return;
	}
	if (BurstMode == 2)
	{
		Sexy();
		return;
	}
	if (BurstMode == 3)
	{
		Nidalee();
		return;
	}
}


static void afterattackBurst(IUnit* source, IUnit* target)
{
	if (BurstMode == 0)
	{
		ShyBurstafter(source, target);
		return;
	}
	if (BurstMode == 1)
	{
		WerhliBurstafter(source, target);
		return;
	}
	if (BurstMode == 2)
	{
		//SexyBurstafter(source, target);
		return;
	}
}


static void processBurst(CastedSpell const& spell)
{
	if (BurstMode == 0)
	{
		processShyBurst(spell);
		return;
	}
	if (BurstMode == 1)
	{
		processWerhliBurst(spell);
		return;
	}
	if (BurstMode == 2)
	{
		processSexyBurst(spell);
		return;
	}
	if (BurstMode == 3)
	{
		processNidaleeBurst(spell);
	}
}