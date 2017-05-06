#pragma once
#include "Extension.h"

PLUGIN_EVENT(void) OnCreateObject(IUnit* obj)
{

	if (obj != nullptr)
	{		
		if (strcmp(obj->GetObjectName(), "Xerath_Base_R_buf_range1_green.troy") == 0)
		{
			UltiIsUp = true;
		}
		if (strcmp(obj->GetObjectName(), "Xerath_Base_R_aoe_miss.troy") == 0)
		{
			 RemaingAmmo = ultiammo() - 1;
			 RCastTime = GGame->TickCount();
		}
		if (strcmp(obj->GetObjectName(), "Global_Trinket_Blue_ward.troy") == 0)
		{
			trinkettime = GGame->TickCount();
					}
		
	}
}
PLUGIN_EVENT(void) OnDestroyObject(IUnit* obj)
{
	if (obj != nullptr)
	{
		if (strcmp(obj->GetObjectName(), "Xerath_Base_R_buf_range1_green.troy") == 0)
		{
			UltiIsUp = false;
		}

	}
}