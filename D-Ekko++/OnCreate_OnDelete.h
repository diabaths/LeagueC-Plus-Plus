#pragma once
#include "Extension.h"

PLUGIN_EVENT(void) OnCreateObject(IUnit* obj)
{
	if (obj != nullptr)
	{
		if (obj->GetClassId() != kobj_GeneralParticleEmitter && strstr(obj->GetObjectName(), "Ekko"))
		{
			Rpos = obj;
		}
	}
}
PLUGIN_EVENT(void) OnDestroyObject(IUnit* obj)
{
	if (obj != nullptr)
	{
		if (!strcmp(obj->GetObjectName(), "Ekko"))
		{
			Rpos = nullptr;
		}
		
	}
}