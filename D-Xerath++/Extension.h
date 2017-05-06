#pragma once
#include "Menu.h"
#include "MalachitePred.h"

static bool InFountain(IUnit *unit)
{
	//TODO: Implement
	return unit->HasBuff("kappachino");
}

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

static  bool PassiveUp()
{
	if (myHero->HasBuff("xerathascended2onhit"))
	{
		return true;
	}
	return false;
}
static bool IsChargingUltimate()
{
	return myHero->HasBuff("XerathLocusOfPower2"); //|| (ObjectManager.Player.LastCastedSpellName() == "XerathLocusOfPower2" && Utils.TickCount - ObjectManager.Player.LastCastedSpellT() < 500);
}

inline int ultiammo()
{
	
	if (myHero->GetSpellBook()->GetLevel(kSlotR) > 0)
	{
		if (myHero->GetSpellBook()->GetLevel(kSlotR) == 1)
		{
			Rammo = 3;
		}
		if (myHero->GetSpellBook()->GetLevel(kSlotR) == 1)
		{
			Rammo = 4;
		}
		if (myHero->GetSpellBook()->GetLevel(kSlotR) == 1)
		{
			Rammo = 5;
		}
	}
	return Rammo;
}

static bool ChargingQ()
{
	if( myHero->HasBuff("XerathArcanopulseChargeUp"))
	{
		return true;
	}
return false;
}

inline void QCast(IUnit* target)
{

	if (target != nullptr && myHero->IsValidTarget(target, 1600) && !UltiIsUp)

		if (!ChargingQ())
			Q->StartCharging();
		else
		{
			MalachiteCast(Q, target, kHitChanceHigh);

			auto distance = GetDistance(myHero->ServerPosition(), target->ServerPosition()) + target->BoundingRadius() * 2;
			if (distance > 1600)
				distance = 1600;

			if (Q->Range() >= distance)
				MalachiteCast(Q, target, kHitChanceHigh);
		}
}
inline void Rcast(IUnit* target)
{
	if (target != nullptr && myHero->IsValidTarget(target, R->Range()))
	{
		if (GGame->TickCount() >= RDashTime)
		{
			if (myHero->IsDashing())
			{
				RDashTime = GGame->TickCount() + Combordash->GetInteger();
			}

			if (GGame->TickCount() - RCastTime > Combormin->GetInteger())
			{
				MalachiteCast(R, target, kHitChanceHigh);
			}
		}
	}
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

