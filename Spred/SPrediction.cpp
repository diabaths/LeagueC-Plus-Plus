#pragma once
#include "SPrediction.h"

ISPrediction *g_SPrediction = nullptr;

#pragma region PredictionInput struct
struct PredictionInput
{
	IUnit *target_;
	struct
	{
		float delay_;
		float missile_speed_;
		float width_;
		float ring_radius_;		//only set for ring spells
		float range_;
		bool collisionable_;
		eSpellType type_;
	} spell_;
	std::vector<Vec3> path_;
	float avg_reaction_time_;
	float last_mov_change_time_;
	float avg_path_lenght_;
	float last_angle_diff_;
	Vec3 from_;
	Vec3 range_check_from_;

	PredictionInput(IUnit *target, ISpell2 *spell)
	{
		target_ = target;
		spell_.delay_ = spell->GetDelay();
		spell_.missile_speed_ = spell->Speed();
		spell_.width_ = spell->Radius();
		spell_.range_ = spell->Range();
		spell_.collisionable_ = (spell->GetCollisionFlags() & static_cast<int>(kCollidesWithMinions)) == kCollidesWithMinions;
		spell_.type_ = spell->GetType();
		path_ = target->GetWaypointList();
		if (target->IsHero())
		{
			avg_reaction_time_ = g_SPrediction->GetPathTrackerEngine().GetAvgMovChangeTime(target);
			last_mov_change_time_ = g_SPrediction->GetPathTrackerEngine().GetLastMovChangeTime(target);
			avg_path_lenght_ = g_SPrediction->GetPathTrackerEngine().GetAvgPathLenght(target);
			last_angle_diff_ = g_SPrediction->GetPathTrackerEngine().GetLastAngleDiff(target);
		}
		from_ = GEntityList->Player()->ServerPosition();
		range_check_from_ = spell->GetRangeCheckFrom();
		spell_.ring_radius_ = 0;
	}

	PredictionInput(IUnit *target, ISpell2 *spell, const Vec3& from)
		: PredictionInput::PredictionInput(target, spell)
	{
		from_ = from;
	}

	PredictionInput(IUnit *target, float delay, float speed, float radius, float range, bool collision, eSpellType type, const Vec3& from, const Vec3& range_check_from)
	{
		target_ = target;
		spell_.delay_ = delay;
		spell_.missile_speed_ = speed;
		spell_.width_ = radius;
		spell_.range_ = range;
		spell_.collisionable_ = collision;
		spell_.type_ = type;
		path_ = target->GetWaypointList();
		if (target->IsHero())
		{
			avg_reaction_time_ = g_SPrediction->GetPathTrackerEngine().GetAvgMovChangeTime(target);
			last_mov_change_time_ = g_SPrediction->GetPathTrackerEngine().GetLastMovChangeTime(target);
			avg_path_lenght_ = g_SPrediction->GetPathTrackerEngine().GetAvgPathLenght(target);
			last_angle_diff_ = g_SPrediction->GetPathTrackerEngine().GetLastAngleDiff(target);
		}
		from_ = from;
		range_check_from_ = range_check_from;
		spell_.ring_radius_ = 0;
	}

	PredictionInput(const PredictionInput& other)
	{
		target_ = other.target_;
		spell_ = other.spell_;
		path_ = other.path_;
		avg_reaction_time_ = other.avg_reaction_time_;
		last_mov_change_time_ = other.last_mov_change_time_;
		avg_path_lenght_ = other.avg_path_lenght_;
		last_angle_diff_ = other.last_angle_diff_;
		from_ = other.from_;
		range_check_from_ = other.range_check_from_;
	}
};
#pragma endregion

#pragma region PredictionResult struct
struct PredictionResult
{
	PredictionInput input_;
	IUnit *unit_;
	Vec2 cast_position_;
	Vec2 cast_position_source_;		//only set for vector spells
	Vec2 unit_position_;
	ePredictionChance hit_chance_;
	CollisionResult collision_;

	PredictionResult(PredictionInput input, IUnit *unit, Vec2 castpos, Vec2 unitpos, ePredictionChance hc, CollisionResult col)
		: input_(input)
	{
		unit_ = unit;
		cast_position_ = castpos;
		unit_position_ = unitpos;
		hit_chance_ = hc;
		collision_ = col;
	}
};
#pragma endregion

#pragma region PredictionAoeResult
struct PredictionAoeResult
{
	Vec2 cast_position_;
	Vec2 cast_position_source_;		//only set for vector spells
	CollisionResult collision_;
	uint8_t hit_count_;

	PredictionAoeResult(const Vec2& castpos, CollisionResult col, int cnt)
	{
		cast_position_ = castpos;
		collision_ = col;
		hit_count_ = cnt;
	}
};
#pragma endregion