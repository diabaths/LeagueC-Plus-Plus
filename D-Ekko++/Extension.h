#pragma once
#include "Menu.h"

static bool InFountain(IUnit *unit)
{
	//TODO: Implement
	return unit->HasBuff("kappachino");
}


inline float GetRealDistance(IUnit* sender, IUnit* target)
{
	return (sender->ServerPosition() - target->ServerPosition()).Length2D() + sender->BoundingRadius() + target->BoundingRadius();
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
static void Reset()
{
	GPluginSDK->DelayFunctionCall(290, []()
	{
		GOrbwalking->ResetAA();
		GGame->IssueOrder(myHero, kAttackTo, GOrbwalking->GetLastTarget());
		
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
static bool HittoPassive(IUnit* target)
{
	if (target != nullptr && !target->IsDead())
	{
		return target->HasBuff("EkkoStacks") && target->GetBuffCount("EkkoStacks") == 2;
	}
	return false;
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


static bool UseE(Vec3 pos)
{
		auto lowHP = UseEHP->GetInteger(); //Dont Use E if HP% <=", 1, 100, 1);
		auto undertower = EnemyUndertowerE->Enabled(); //target is under tower
		auto enemies = AoeE->Enabled(); //use E if Enemies arount
		auto enemiesarount = AoeEEnemys->GetInteger(); //set the number of enemies
		if (!undertower && GUtility->IsPositionUnderTurret(pos))
		{
			return false;
		}
		if (myHero->HealthPercent() < lowHP)
		{
			return false;
		}
		if (enemies)
		{
			return	CountEnemiesInPositionRange(pos, 600) <= enemiesarount;
		}
		return false;
	}

inline void WLogic(IUnit* Enemy)
{
	if (!CanMove(Enemy))
	{
		W->CastOnUnit(Enemy);
		}
	if (CanMove(Enemy))
	{
		if (myHero->IsFacing(Enemy) && !Enemy->IsFacing(myHero))
		{
			W->CastOnPosition(myHero->GetPosition().Extend(myHero->GetPosition(), W->Range()));
		}
		if (Enemy->IsFacing(myHero) && !myHero->IsFacing(Enemy))
		{
			W->CastOnPosition(myHero->GetPosition().Extend(Enemy->GetPosition(), W->Range() / 2));
			}
		else if (Enemy->IsFacing(myHero) && Enemy->IsMelee() && GetDistance(myHero, Enemy) <= 250)
		{
			W->CastOnPosition(myHero->GetPosition());
		}

		else
		{
			AdvPredictionOutput WPred;
			W->RunPrediction(Enemy, true, kCollidesWithNothing, &WPred);

			if (WPred.HitChance >= kHitChanceHigh)
			{
				Vec3 Enemypos;
				GPrediction->GetFutureUnitPosition(Enemy, 0.9, true, Enemypos);
				W->CastOnPosition(Enemypos);
			}
		}
	}
}

