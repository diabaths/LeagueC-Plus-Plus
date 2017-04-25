#pragma once
#include <PluginSDK.h>
#include "Collision.h"
#include "PathTracker.h"

struct PredictionInput;
struct PredictionResult;
struct PredictionAoeResult;

class ISPrediction
{
public:
	virtual bool CastSpell(ISpell2 *spell, IUnit *target, ePredictionChance hit_chance = kHitChanceHigh, bool aoe = false, uint8_t min_hit = 1) = 0;
	virtual bool CastArcSpell(ISpell2 *spell, IUnit *target, ePredictionChance hit_chance = kHitChanceHigh, bool aoe = false, uint8_t min_hit = 1) = 0;
	virtual bool CastRingSpell(ISpell2 *spell, IUnit *target, float ring_radius, ePredictionChance hit_chance = kHitChanceHigh) = 0;
	virtual bool CastVectorSpell(ISpell2 *spell, IUnit *target, ePredictionChance hit_chance = kHitChanceHigh, bool aoe = false, uint8_t min_hit = 1) = 0;
	virtual PredictionResult GetPrediction(ISpell2 *spell, IUnit *target) = 0;
	virtual Vec2 GetFastUnitPosition(IUnit *target, float delay, float missile_speed = 0, float distance_set = 0, float move_speed = 0) = 0;
	virtual Vec2 GetFastUnitPosition(IUnit *target, const Vec3& from, float delay, float missile_speed = 0, float distance_set = 0, float move_speed = 0) = 0;
	virtual ICollision& GetCollisionEngine() = 0;
	virtual IPathTracker& GetPathTrackerEngine() = 0;
};

extern ISPrediction *g_SPrediction;

#define SPredicitonSDKSetup(x) g_SPrediction = reinterpret_cast<ISPrediction *>(x->FindPluginInterface("SPrediction"))