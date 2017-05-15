#pragma once
#include "Extension.h"

PLUGIN_EVENT(void) OnCreateObject(IUnit* obj)
{
	if (obj != nullptr)
	{
		if (strcmp(obj->GetObjectName(), "Ekko_Base_R_TrailEnd.troy") == 0)
		{
			Rpos = obj;
		}
	}
}
PLUGIN_EVENT(void) OnDestroyObject(IUnit* obj)
{
	if (obj != nullptr)
	{
		if (strcmp(obj->GetObjectName(), "Ekko_Base_R_Disappear.troy") == 0)
		{
			Rpos = nullptr;
		}
	}
}