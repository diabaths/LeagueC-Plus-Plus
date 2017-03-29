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

static void ResetQ1()
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

static void ResetW()
{
	GPluginSDK->DelayFunctionCall(170, []()
	{
		GGame->Say("/d");
		GOrbwalking->ResetAA();
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition()); 
	});
}

static void ResetR2()
{
	GPluginSDK->DelayFunctionCall(150, []()
	{	
		GGame->Say("/d");
		GOrbwalking->ResetAA();
		GGame->IssueOrder(myHero, kMoveTo, GGame->CursorPosition()); 
	});
}
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
	if(!Source->HasBuffOfType(BUFF_Stun) &&	!Source->HasBuffOfType(BUFF_Fear) && !Source->HasBuffOfType(BUFF_Snare) 
		&& !Source->HasBuffOfType(BUFF_Knockup) && !Source->IsRecalling() && !Source->HasBuffOfType(BUFF_Knockback)
		&& !Source->HasBuffOfType(BUFF_Charm) && !Source->HasBuffOfType(BUFF_Taunt) &&
		!Source->HasBuffOfType(BUFF_Suppression) || Source->IsMoving())
	{
		return true;
	}
	else return false;
}

static void ELogic(IUnit* target)
{
	if (target == nullptr || target->IsDead() || !E->IsReady())
	{
		return;
	}

	if (ComboQ->Enabled() && Q->IsReady() && Qstack == 0 &&
		GetDistance(myHero, target) < myHero->GetRealAutoAttackRange(target) + 260)
	{
		return;
	}
	if (GetDistance(myHero, target) <= 650 && Qstack == 1 && Q->IsReady() && GetDistance(myHero, target) > IsInAutoAttackRange(target) + 100 && CanMoveMent(myHero))
	{
		if (Debug->Enabled())
		{
			GGame->PrintChat("E-stage_1");
		}
		E->CastOnPosition(target->GetPosition());
		return;
	}

	if (GetDistance(myHero, target) <= 325 + Wrange && W->IsReady() && GetDistance(myHero, target) > IsInAutoAttackRange(target) + 100 && CanMoveMent(myHero))
	{
		if (Debug->Enabled())
		{
			GGame->PrintChat("E-stage_2");
		}
		E->CastOnPosition(target->ServerPosition());
		return;
	}

	if (!Q->IsReady() && !W->IsReady() && GetDistance(myHero, target) < 325 + IsInAutoAttackRange(target) && GetDistance(myHero, target) > IsInAutoAttackRange(target) + 100 && CanMoveMent(myHero))
	{
		if (Debug->Enabled())
		{
			GGame->PrintChat("E-stage_3");
		}
		E->CastOnPosition(target->ServerPosition());
	}
}

static void WLogic(IUnit* target)
{
	if (target == nullptr || target->IsDead() || !W->IsReady())
	{
		return;
	}

	/*if (!Q->IsReady() && Qstack == 0)
	{
		W->CastOnPlayer();
		return;
	}*/

	//if (!target->IsFacing(myHero))
	//{
		W->CastOnPlayer();
	//}
}
static bool DontAttack()
{
	if (AutoAttack)
	{
		GPluginSDK->DelayFunctionCall(50, []()
		{
			AutoAttack = false;
		});
	}
	return false;
}

/*static void ForceItem()
{
	if (Items.CanUseItem(Item) && Items.HasItem(Item) && Item != 0) forceItem = true;
	Utility.DelayAction.Add(500, () = > forceItem = false);
}
static void ForceR()
{
	forceR = (R.IsReady() && R.Instance.Name == IsFirstR);
	Utility.DelayAction.Add(500, () = > forceR = false);
}
static void ForceR2()
{
	forceR2 = R.IsReady() && R.Instance.Name == IsSecondR;
	Utility.DelayAction.Add(500, () = > forceR2 = false);
}
static void ForceW()
{
	forceW = W.IsReady();
	Utility.DelayAction.Add(500, () = > forceW = false);
}

static void ForceCastQ(IUnit* target)
{
	forceQ = true;
	QTarget = target;
}*/
