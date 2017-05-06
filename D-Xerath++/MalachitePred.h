#pragma once
#include "malachite_Extension.h"
#include <string>

std::map<int, UnitDash*> MalachitePredAllDashData;
std::map <int, int> MalachitePredAllNewPathTicks;
Vec3 MalachitePredLastYasuoWallCastPos;
class MalachitePredOutPut
{
public:
	Vec3 CastPosition;
	Vec3 UnitPosition;
	vector<IUnit*> CollisionObjects;
	ePredictionChance HitChance = kHitChanceImmobile;
	MalachitePredOutPut(Vec3 castposition, Vec3 unitposition, vector<IUnit*> collisionobjects, ePredictionChance hitchance)
	{
		CastPosition = castposition;
		UnitPosition = unitposition;
		CollisionObjects = collisionobjects;
		HitChance = hitchance;
	}
	MalachitePredOutPut() {};
};
inline Vec3 MalachitePredGetUnitPosition(IUnit* target, float delay)
{
	delay = delay + GGame->Latency() / 1000;
	auto waypoint = target->GetWaypointList();
	if (waypoint.size() == 1)
		return waypoint.front();
	if (target->IsDashing())
	{
		auto data = MalachitePredAllDashData[target->GetNetworkId()];
		float dashdistance = delay * data->Speed;
		return dashdistance >= Distance(target, data->EndPosition) ? data->EndPosition
			: Extend(target->GetPosition(), data->EndPosition, dashdistance);
	}
	float distance = target->MovementSpeed() * delay;
	for (int i = 1; i < waypoint.size(); i = i + 1)
	{
		float waydistance = Distance(waypoint[i - 1], waypoint[i]);
		if (waydistance >= distance)
		{
			return  Extend(waypoint[i - 1], waypoint[i], distance);
		}
		if (i = waypoint.size() - 1)
			return waypoint[i];
		distance = distance - waydistance;
	}
	return target->GetPosition();
}
inline vector<IUnit*> MalachitePredGetCollisions(Vec3 From, Vec3 To, int ColiFlag, IUnit* target, ISpell2* spell)
{
	vector<IUnit *> Collisons;
	if (ColiFlag&kCollidesWithHeroes || ColiFlag&kCollidesWithMinions)
	{
		//GGame->PrintChat("a");
		SArray<IUnit*> Heroes;
		SArray<IUnit*> Minions;
		SArray<IUnit*> AllUnits;
		if (ColiFlag&kCollidesWithHeroes)
		{
			Heroes.AddRange(GEntityList->GetAllHeros(false, true));
			Heroes = Heroes.Where([&](IUnit* i) {return i != nullptr && !i->IsDead() && i->GetNetworkId() != target->GetNetworkId(); });
		}
		if (ColiFlag&kCollidesWithMinions)
		{
			//GGame->PrintChat("b");
			Minions.AddRange(EnemyMinions(Distance(From, To) + 500, From));
			Minions.AddRange(NeutralMinions(Distance(From, To) + 500, From));
			Minions.RemoveAll([&](IUnit* i) {return i->GetNetworkId() == target->GetNetworkId(); });
			//GGame->PrintChat(std::to_string(Minions.Count()).c_str());
		}
		AllUnits.AddRange(Heroes);
		AllUnits.AddRange(Minions);
		for (IUnit* hero : AllUnits.ToVector())
		{
			float delay = spell->GetDelay() + Distance(From, hero->GetPosition()) / spell->Speed();
			Vec3 pred = MalachitePredGetUnitPosition(hero, delay);
			float mindistance = hero->BoundingRadius() + spell->Radius() / 2 + 25;
			if (Distance(hero->GetPosition(), From, To, true) < mindistance
				|| Distance(pred, From, To, true) < mindistance
				|| GetSegmentSegmentIntersections(From, To, hero->GetPosition(), pred))
			{
				Collisons.push_back(hero);
			}
		}
	}
	if (ColiFlag&kCollidesWithYasuoWall)
	{
		IUnit* Wall;
		SArray<IUnit*> AllUnits;
		AllUnits.AddRange(GEntityList->GetAllUnits());
		AllUnits = AllUnits.Where([&](IUnit* i) {return i != nullptr &&  Contains(i->GetObjectName(), "w_windwall_enemy_"); });
		if (AllUnits.Any())
		{
			Wall = AllUnits.FirstOrDefault();
			float length = 300 + 5 * 5;
			Vec3 direction = Pendicular(Normalize((Wall->GetPosition() - MalachitePredLastYasuoWallCastPos)));
			Vec3 WallStart = ToVec3((ToVec2(Wall->GetPosition()) + length * ToVec2(direction) / 2));
			Vec3 WallEnd = ToVec3((ToVec2(Wall->GetPosition()) - length * ToVec2(direction) / 2));
			float mindistance = 50 + spell->Radius() / 2 + 50;
			if (Distance(WallStart, From, To, true) < mindistance
				|| Distance(WallEnd, From, To, true) < mindistance
				|| GetSegmentSegmentIntersections(From, To, WallStart, WallEnd))
			{
				Collisons.push_back(Wall);
			}
		}
	}
	return Collisons;
}
inline MalachitePredOutPut MalachitePredGetPrediction(ISpell2*  spell, IUnit*  target)
{
	MalachitePredOutPut output;
	output.HitChance = kHitChanceImpossible;
	auto waypoint = target->GetWaypointList();
	Vec3 RangeCheckFrom = spell->GetRangeCheckFrom() == Vec3(0, 0, 0) ? GEntityList->Player()->GetPosition() : spell->GetRangeCheckFrom();
	if (waypoint.size() == 1)
	{
		output.CastPosition = waypoint[0];
		output.UnitPosition = waypoint[0];
		output.HitChance = kHitChanceHigh;
	}
	float speed = target->IsDashing() ? MalachitePredAllDashData[target->GetNetworkId()]->Speed : target->MovementSpeed();
	float realspelldelay = spell->GetDelay(); /*> spell->Radius() / 2.f / speed ? spell->GetDelay() - spell->Radius() / 2.f / speed : 0.f;*/
	float time = 0.f;
	for (int i = 1; i < waypoint.size(); i = i + 1)
	{
		float distance = Distance(waypoint[i - 1], waypoint[i]);
		for (float j = 0; j <= distance; j = j + 5)
		{
			Vec3 Position = Extend(waypoint[i - 1], waypoint[i], j);

			float spelldistance = Distance(RangeCheckFrom, Position);
			float targettime = time + j / speed;
			float spelltime = realspelldelay + spelldistance / spell->Speed();
			if (abs(targettime - spelltime) < 10 / target->MovementSpeed())
			{
				output.CastPosition = Position;
				output.UnitPosition = Position;
				output.HitChance = kHitChanceHigh;
				goto ABC;
			}
		}
		time = time + distance / target->MovementSpeed();
	}
ABC:
	if (output.HitChance > kHitChanceImpossible)
	{
		if (GGame->TickCount() - MalachitePredAllNewPathTicks[target->GetNetworkId()] < 100)
			output.HitChance = kHitChanceVeryHigh;
		if (Distance(target, RangeCheckFrom) <= 300)
			output.HitChance = kHitChanceVeryHigh;
		if (target->IsDashing())
			output.HitChance = kHitChanceDashing;
		else if (waypoint.size() == 1 && IsCCed(target))
			output.HitChance = kHitChanceImmobile;
		if (Distance(output.CastPosition, RangeCheckFrom) > spell->Range() && spell->Range() != 0)
		{
			output.HitChance = kHitChanceOutOfRange;
		}
		auto collisionobjects = MalachitePredGetCollisions(RangeCheckFrom, output.CastPosition, spell->GetCollisionFlags(), target, spell);
		if (collisionobjects.size() != 0)
		{
			output.HitChance = kHitChanceCollision;
		}
		output.CollisionObjects = collisionobjects;
		return output;
	}
	output.CastPosition = waypoint.back();
	output.UnitPosition = waypoint.back();
	output.HitChance = kHitChanceImpossible;
	output.CollisionObjects = MalachitePredGetCollisions(RangeCheckFrom, output.CastPosition, spell->GetCollisionFlags(), target, spell);
	return output;
}
//cast
inline bool MalachiteCast(ISpell2* spell, IUnit* target, ePredictionChance MinHitChane = kHitChanceHigh)
{
	MalachitePredOutPut pred = MalachitePredGetPrediction(spell, target);
	if (pred.HitChance >= MinHitChane)
	{
		spell->CastOnPosition(pred.CastPosition);
		return true;
	}
	return false;
}

PLUGIN_EVENT(void) MalachitePredOnSpellCast(CastedSpell const& Args)
{
	if (Args.Caster_ != nullptr && Args.Caster_->IsEnemy(GEntityList->Player()) && Contains(GSpellData->GetSpellName(Args.Data_), "YasuoWMovingWall", false))
	{
		MalachitePredLastYasuoWallCastPos = Args.Caster_->GetPosition();
	}
}
PLUGIN_EVENT(void) MalachitePredOnDash(UnitDash* Args)
{
	if (Args->Source == nullptr)
		return;
	MalachitePredAllDashData[Args->Source->GetNetworkId()] = Args;
}
PLUGIN_EVENT(void) MalachitePredOnNewPath(IUnit* Source, const std::vector<Vec3>& Path)
{
	if (Source == nullptr)
		return;
	MalachitePredAllNewPathTicks[Source->GetNetworkId()] = GGame->TickCount();
}

inline void MalachitePredOnload()
{
	GEventManager->AddEventHandler(kEventOnDash, MalachitePredOnDash);
	GEventManager->AddEventHandler(kEventOnSpellCast, MalachitePredOnSpellCast);
	GEventManager->AddEventHandler(kEventOnNewPath, MalachitePredOnNewPath);
}
inline void MalachitePredUnload()
{
	GEventManager->RemoveEventHandler(kEventOnDash, MalachitePredOnDash);
	GEventManager->RemoveEventHandler(kEventOnSpellCast, MalachitePredOnSpellCast);
	GEventManager->RemoveEventHandler(kEventOnNewPath, MalachitePredOnNewPath);
}