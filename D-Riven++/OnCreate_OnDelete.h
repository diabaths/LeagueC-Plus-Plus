#pragma once
#include "Extensions.h"

PLUGIN_EVENT(void) OnCreateObject(IUnit* obj)
{
	
	if (obj != nullptr)
	{
		
		if (strcmp(obj->GetObjectName(), "Riven_Base_Q_01_Wpn_Trail.troy") == 0)
		{
			LastQ = GGame->TickCount();
			Qstack = 1;
			ResetQ1();
		}
		if (strcmp(obj->GetObjectName(), "Riven_Base_Q_02_Wpn_Trail.troy") == 0)
		{
			LastQ = GGame->TickCount();
			Qstack = 2;
			ResetQ2();
		}
		if (strcmp(obj->GetObjectName(), "Riven_Base_Q_03_Wpn_Trail.troy") == 0)
		{
			LastQ = GGame->TickCount();
			Qstack = 0;
			ResetQ3();
		}
		if (strcmp(obj->GetObjectName(), "Riven_Base_W_03_Cast.troy") == 0)
		{
			ResetW();
		}
		if (strcmp(obj->GetObjectName(), "Riven_Base_R_Sword.troy") == 0)
		{
			ResetR1();
		}		
	}
}
PLUGIN_EVENT(void) OnDestroyObject(IUnit* obj)
{
	if (obj != nullptr)
	{
		/*if (strcmp(obj->GetObjectName(), "Rengar_Base_P_Buf.troy") == 0)
		{
		passivedown = true;
		GGame->PrintChat("passive");
		}
		if (strcmp(obj->GetObjectName(), "GlobalCamouflagePersistant.troy") == 0)
		{
		passivedown = true;
		}*/
		
	}
}