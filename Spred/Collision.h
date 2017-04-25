#pragma once
#include <PluginSDK.h>

enum class CollisionFlags
{
	None = 0,
	Minions = 1,
	AllyChampions = 2,
	EnemyChampions = 4,
	Wall = 8,
	YasuoWall = 16,
};

struct CollisionResult
{
	std::vector<IUnit *> units_;
	CollisionFlags objects_;
};

class ICollision
{
public:
	virtual bool CheckCollision(const Vec2& from, const Vec2& to, float width, float delay, float missile_speed, bool check_minion = true, bool check_enemy = false, bool check_yasuowall = true, bool check_ally = false, bool check_wall = false, bool is_arc = false) = 0;
	virtual bool CheckMinionCollision(const Vec2& from, const Vec2& to, float width, float delay, float missile_speed = 0, bool is_arc = false) = 0;
	virtual bool CheckEnemyHeroCollision(const Vec2& from, const Vec2& to, float width, float delay, float missile_speed = 0, bool is_arc = false) = 0;
	virtual bool CheckAllyHeroCollision(const Vec2& from, const Vec2& to, float width, float delay, float missile_speed = 0, bool is_arc = false) = 0;
	virtual bool CheckWallCollision(const Vec2& from, const Vec2& to) = 0;
	virtual bool CheckYasuoWallCollision(const Vec2& from, const Vec2& to, float width, bool is_arc = false) = 0;
	virtual CollisionResult GetCollisions(const Vec2& from, const Vec2& to, float range, float width, float delay, float missile_speed = 0, bool is_arc = false) = 0;
};