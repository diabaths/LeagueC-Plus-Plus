#pragma once
#include "RETWQ.h"
#include "RETQW.h"
#include "REQWT.h"

inline void Combo()
{
	
	if (ComboMode == 0)
	{
		RETQW();
		return;
	}
	if (ComboMode == 1)
	{
		REQWT();
		return;
	}
	if (ComboMode == 2)
	{
		RETWQ();
	}
}

inline void Combo(CastedSpell const& spell)
{
	if (ComboMode == 0)
	{
		RETQW(spell);
		return;
	}
	if (ComboMode == 1)
	{
		REQWT(spell);
		return;
	}
	if (ComboMode == 2)
	{
		RETWQ();
	}
}