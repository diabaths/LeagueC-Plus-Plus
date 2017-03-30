#pragma once
#include "Menu.h"
#include "Spells.h"

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

static bool InFountain(IUnit *unit)
{
	//TODO: Implement
	return unit->HasBuff("kappachino");
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

/*static void ResetQ1()
{
	GPluginSDK->DelayFunctionCall(QDelay1->GetInteger(), []()
	{

		GGame->Say("/d");
		GOrbwalking->ResetAA();
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	});
}
static void ResetQ2()
{
	GPluginSDK->DelayFunctionCall(QDelay2->GetInteger(), []()
	{
		GGame->Say("/d");
		GOrbwalking->ResetAA();
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	});
} //myHero->GetPosition().Extend(GGame->CursorPosition(), GetDistanceVectors(myHero->GetPosition(), GGame->CursorPosition()) + 10)
static void ResetQ3()
{
	GPluginSDK->DelayFunctionCall(QDelay3->GetInteger(), []()
	{
		GGame->Taunt(kLaugh);
		GOrbwalking->ResetAA();
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	});
}
*/
static void ResetQ()
{
	GPluginSDK->DelayFunctionCall(75, []()
	{
		GGame->Say("/d");
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	});
}

static void ResetE()
{
	GPluginSDK->DelayFunctionCall(75, []()
	{
		GGame->Taunt(kDance);
		GOrbwalking->ResetAA();
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	});	
}
static void ResetR()
{
	GPluginSDK->DelayFunctionCall(75, []()
	{
		GGame->Taunt(kLaugh);
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	});
}
/*
static void ResetR2()
{
	GPluginSDK->DelayFunctionCall(150, []()
	{
		GGame->Say("/d");
		GOrbwalking->ResetAA();
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	});
}*/
static void AAcancel()
{
	GPluginSDK->DelayFunctionCall(150, []()
	{
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition());
	});
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
inline bool Equals(std::string a, std::string b)
{
	if (strcmp(a.c_str(), b.c_str()) == 0)
		return true;
	else return false;
}

inline bool IsInAutoAttackRange(Vec3 position)
{
	return GEntityList->Player()->GetRealAutoAttackRange(GEntityList->Player()) >= GetDistance(myHero, position);
}

inline bool IsInAutoAttackRange(IUnit* target)
{
	return GEntityList->Player()->GetRealAutoAttackRange(target) >= GetDistance(myHero, target);
}

static bool CanMoveMent(IUnit* Source)
{
	if (!Source->HasBuffOfType(BUFF_Stun) && !Source->HasBuffOfType(BUFF_Fear) && !Source->HasBuffOfType(BUFF_Snare)
		&& !Source->HasBuffOfType(BUFF_Knockup) && !Source->IsRecalling() && !Source->HasBuffOfType(BUFF_Knockback)
		&& !Source->HasBuffOfType(BUFF_Charm) && !Source->HasBuffOfType(BUFF_Taunt) &&
		!Source->HasBuffOfType(BUFF_Suppression) || Source->IsMoving())
	{
		return true;
	}
	else return false;
}

inline int CountEnemiesInPositionRange(Vec3 position, float range)
{
	auto enemies = 0;

	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && GetDistance(position, enemy->GetPosition()) <= range)
		{
			if (enemy->GetPosition() != position)
			{
				enemies++;
			}
		}
	}

	return enemies;
}

inline void smitetarget()
{
	if (smite == nullptr) return;
	if (!usesmitetarget->Enabled() || !smite->IsReady()) return;
	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy != nullptr && myHero->IsValidTarget(enemy, 570))
		{
			auto Dmg = GDamage->GetSummonerSpellDamage(myHero, enemy, kSummonerSpellSmite);

			smite->CastOnUnit(enemy);
		}
	}
}

inline void Smiteuse()
{
	if (smite != nullptr && smite->IsReady())
	{
		auto minions = GEntityList->GetAllMinions(false, false, true);
		for (IUnit* minion : minions)
		{
			auto smitestage = usesmitejungle->GetInteger();
			if (smitestage == 0)
			{
				if (strstr(minion->GetObjectName(), "Blue") || strstr(minion->GetObjectName(), "Gromp")
					|| strstr(minion->GetObjectName(), "Murkwolf") || strstr(minion->GetObjectName(), "Razorbeak")
					|| strstr(minion->GetObjectName(), "RiftHerald") || strstr(minion->GetObjectName(), "Red")
					|| strstr(minion->GetObjectName(), "Krug") || strstr(minion->GetObjectName(), "Dragon")
					|| strstr(minion->GetObjectName(), "Baron"))
				{
					auto Dmg = GDamage->GetSummonerSpellDamage(myHero, minion, kSummonerSpellSmite);
					if (minion != nullptr && !minion->IsDead() && minion->GetHealth() <= Dmg && myHero->IsValidTarget(minion, 570))
					{
						smite->CastOnUnit(minion);
					}
				}
			}
			if (smitestage == 1)
			{
				if (strstr(minion->GetObjectName(), "RiftHerald") || strstr(minion->GetObjectName(), "Dragon")
					|| strstr(minion->GetObjectName(), "Baron"))
				{
					auto Dmg = GDamage->GetSummonerSpellDamage(myHero, minion, kSummonerSpellSmite);
					if (minion != nullptr && !minion->IsDead() && minion->GetHealth() <= Dmg && myHero->IsValidTarget(minion, 570))
					{
						smite->CastOnUnit(minion);
					}
				}
			}
		}
	}
}

