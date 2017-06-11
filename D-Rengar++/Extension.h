#pragma once
#include "Menu.h"
#include <algorithm>

inline float GetRealDistance(IUnit* sender, IUnit* target)
{
	return (sender->ServerPosition() - target->ServerPosition()).Length2D() + sender->BoundingRadius() + target->BoundingRadius();
}

inline int EnemiesInRange(IUnit* Source, float range)
{
	auto Targets = GEntityList->GetAllHeros(false, true);
	auto enemiesInRange = 0;

	for (auto target : Targets)
	{
		if (target != nullptr)
		{
			auto flDistance = (target->GetPosition() - Source->GetPosition()).Length();
			if (flDistance < range)
			{
				enemiesInRange++;
			}
		}
	}
	return enemiesInRange;
}

inline float GetDistance(IUnit* Player, IUnit* target)
{
	return (Player->GetPosition() - target->GetPosition()).Length2D();
}

inline float GetDistance(Vec3 from, Vec3 to)
{
	return (from - to).Length2D();
}

inline float GetDistance(IUnit* from, Vec3 to)
{
	return (from->GetPosition() - to).Length2D();
}
inline float GetDistance(Vec2 from, Vec2 to)
{
	return (from - to).Length();
}

inline int CountEnemiesInRange(float range)
{
	int enemies = 0;
	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && GetDistance(GEntityList->Player(), enemy) <= range)
		{
			enemies++;
		}
	}
	return enemies;
}

inline int  CountEnemiesInRange(Vec3 Location, int range)
{
	int Count = 0;

	for (auto Enemy : GEntityList->GetAllHeros(false, true))
	{
		if ((Enemy->GetPosition() - Location).Length() < range && Enemy->IsValidTarget() && !Enemy->IsDead())
		{
			Count++;
		}
	}
	return (Count);
}
inline int CountminionInRange(float range)
{
	int enemies = 0;
	for (auto enemy : GEntityList->GetAllMinions(false, true, false))
	{
		if (enemy != nullptr && GetDistance(GEntityList->Player(), enemy) <= range)
		{
			enemies++;
		}
	}
	return enemies;
}
inline std::string ToLower(std::string StringToLower)
{
	auto Lowered = StringToLower;
	for (int i = 0; i < Lowered[i]; i++)
	{
		Lowered[i] = tolower(Lowered[i]);
	} return Lowered;
}

inline bool Contains(std::string Container, std::string Contained)
{
	auto LoweredContainer = ToLower(Container); auto LoweredContained = ToLower(Contained);
	if (LoweredContainer.find(LoweredContained) != std::string::npos)
		return true;
	else return false;
}

inline float GetDistanceVectors(Vec3 from, Vec3 to)
{
	float x1 = from.x;
	float x2 = to.x;
	float y1 = from.y;
	float y2 = to.y;
	float z1 = from.z;
	float z2 = to.z;
	return static_cast<float>(sqrt(pow((x2 - x1), 2.0) + pow((y2 - y1), 2.0) + pow((z2 - z1), 2.0)));
}

inline Vec2 ToVec2(Vec3 vec)
{
	return Vec2(vec.x, vec.z);
}
inline Vec3 ToVec3(Vec2 vec)
{
	return Vec3(vec.x, 0, vec.y);
}
inline float Distance(Vec3 from, Vec3 to)
{
	return (from - to).Length2D();
}
inline float Distance(IUnit* from, IUnit* to)
{
	return (from->GetPosition() - to->GetPosition()).Length2D();
}
inline float Distance(IUnit* from, Vec3 to)
{
	return (from->GetPosition() - to).Length2D();
}
inline float Distance(Vec2 from, Vec2 to)
{
	return (from - to).Length();
}
static void ResetQ()
{

	GPluginSDK->DelayFunctionCall(290, []()
	{
		GOrbwalking->ResetAA();
		GGame->Taunt(kDance);
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
		GOrbwalking->SetOverridePosition(Vec3(0, 0, 0));

	});
}
static void ResetE()
{	
	GPluginSDK->DelayFunctionCall(290, []()
	{
		GOrbwalking->ResetAA();
	});
}

static bool CanMove(IUnit* Source)
{
	if (!Source->HasBuffOfType(BUFF_Stun) && !Source->HasBuffOfType(BUFF_Fear) && !Source->HasBuffOfType(BUFF_Snare)
		&& !Source->HasBuffOfType(BUFF_Knockup) && !Source->IsRecalling() && !Source->HasBuffOfType(BUFF_Knockback)
		&& !Source->HasBuffOfType(BUFF_Charm) && !Source->HasBuffOfType(BUFF_Taunt) &&
		!Source->HasBuffOfType(BUFF_Suppression) || Source->IsMoving())
	{
		return true;
	}
	return false;
}
static bool PassiveOn()
{
	return myHero->HasBuff("rengarpassivebuff");
}
static bool UltiOn()
{
	return myHero->HasBuff("RengarR");
}

inline int CountEnemiesInPositionRange(Vec3 position, int range)
{
	auto enemies = 0;

	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && (enemy->GetPosition() - position).Length() <= range)
		{
			if (enemy->IsValidTarget())
			{
				enemies++;
			}
		}
	}

	return enemies;
}




// compare units
inline bool CompareDistanceToCursor(IUnit * a, IUnit * b)
{
	return Distance(a->ServerPosition(), GGame->CursorPosition()) < Distance(b->ServerPosition(), GGame->CursorPosition());
}

inline IUnit * MinionNearPosition(Vec3 position, float range)
{
	auto v = GEntityList->GetAllMinions(false, true, true);

	// remove every minion from list thats out of range
	v.erase(std::remove_if(v.begin(), v.end(), [&](IUnit * a) { return Distance(position, a->ServerPosition()) > range; }));

	// sort closest to cursor
	std::sort(v.begin(), v.end(), [&](IUnit * a, IUnit * b) { return CompareDistanceToCursor(a, b); });

	return v.front();
}