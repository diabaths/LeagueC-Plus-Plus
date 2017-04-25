#pragma once
#include <cstdint>
#include <PluginSDK.h>

class IPathTracker
{
public:
	virtual uint32_t GetMovImmobileTime(IUnit *hero) = 0;
	virtual uint32_t GetLastMovChangeTime(IUnit *hero) = 0;
	virtual float GetAvgMovChangeTime(IUnit *hero) = 0;
	virtual float GetAvgPathLenght(IUnit *hero) = 0;
	virtual float GetLastAngleDiff(IUnit *hero) = 0;
	virtual float GetAvgOrbwalkTime(IUnit *hero) = 0;
};