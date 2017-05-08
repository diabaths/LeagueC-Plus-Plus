#pragma once
#include "PluginSDK.h"
#include "Geometry.h"

using namespace std;

//global variables
map<int, IInventoryItem*> AllItems;

#pragma region extension
//linqq ne`
template<class T>
vector<T> Add(vector<T> vec, T i)
{
	vector<T> newvec;
	newvec = vec;
	newvec.push_back(i);
	return newvec;
}
template<class T>
vector<T> AddRange(vector<T> vec, vector<T> vecToAdd)
{
	vector<T> newvec;
	newvec = vec;
	newvec.insert(newvec.end(), vecToAdd.begin(), vecToAdd.end());
	return newvec;
}
template<class T>
vector<T> RemoveAll(vector<T> vec, function<bool(T)> removefunc)
{
	vector<T> newvec;
	for each (T i in vec)
	{
		if (!removefunc(i))
			newvec.push_back(i);
	}
	return newvec;
}
template<class T>
vector<T> Where(vector<T> vec, function<bool(T)> wherefunc)
{
	vector<T> newvec;
	for each (T i in vec)
	{
		if (wherefunc(i))
			newvec.push_back(i);
	}
	return newvec;
}
template<class T>
bool Any(vector<T> vec, function<bool(T)> anyfunc)
{
	vector<T> newvec;
	newvec = vec;
	newvec = Where(newvec, anyfunc);
	return !newvec.empty();
}
template<class T>
bool Any(vector<T> vec)
{
	vector<T> newvec;
	newvec = vec;
	return !newvec.empty();
}
template<class T, class T2>
vector<T2> Select(vector<T> vec, function<T2(T)> selectfunc)
{
	vector<T> newvec;
	newvec = vec;
	vector<T2> returnvec;
	for each (T i in newvec)
	{
		returnvec.push_back(selectfunc(i));
	}
	return returnvec;
}
template<class T>
T FirstOrDefault(vector<T> vec, function<bool(T)> fst_function)
{
	vector<T> newvec;
	newvec = vec;

	newvec = Where(newvec, fst_function);
	if (newvec.empty())
		return T();
	return newvec.front();
}
template<class T>
T LastOrDefault(vector<T> vec, function<bool(T)> lst_function)
{
	vector<T> newvec;
	newvec = vec;

	newvec = Where(newvec, lst_function);
	if (newvec.empty())
		return T();
	return newvec.back();
}
template<class T, class T2>
T MinOrDefault(vector<T> vec, function<T2(T)> min_function)
{
	vector<T> newvec;
	newvec = vec;
	T returnelem;
	returnelem = T();
	if (newvec.empty())
		return returnelem;
	returnelem = newvec.begin();
	for each (T i in newvec)
	{
		if (min_function(i) < min_function(returnelem))
			returnelem = i;
	}
	return returnelem;
}
template<class T, class T2>
T MaxOrDefault(vector<T> vec, function<T2(T)> max_function)
{
	vector<T> newvec;
	newvec = vec;
	T returnelem;
	returnelem = T();
	if (newvec.empty())
		return returnelem;
	returnelem = newvec.begin();
	for each (T i in newvec)
	{
		if (max_function(i) < max_function(returnelem))
			returnelem = i;
	}
	return returnelem;
}
inline string SpellSlotToString(eSpellSlot slot)
{
	return slot == kSlotQ ? "Q" : slot == kSlotW ? "W" : slot == kSlotE ? "E" : slot == kSlotR ? "R" : "UnKnown";
}
// keydown
inline bool IsKeyDown(IMenuOption* menuOption)
{
	return (GetAsyncKeyState(menuOption->GetInteger()) & 0x8000) != 0;
}
//select target
inline IUnit* SelectTarget(eDamageType type, float range)
{
	return GTargetSelector->FindTarget(QuickestKill, type, range);
}

inline float GetAutoAttackRange(IUnit*target, IUnit* thistarget = GEntityList->Player())
{
	return thistarget->BoundingRadius() + thistarget->AttackRange() + target->BoundingRadius();
}
// get selected
inline IUnit* GetSelectedTarget()
{
	return GTargetSelector->GetFocusedTarget();
}
//String viet thuong
inline string ToLower(string StringToLower)
{
	auto Lowered = StringToLower;
	for (int i = 0; i < Lowered[i]; i++)
	{
		Lowered[i] = tolower(Lowered[i]);
	}
	return Lowered;
}
// string bao gom string khac
inline bool Contains(string Container, string Contained, bool Lower = true)
{
	auto LoweredContainer = Lower ? ToLower(Container) : Container;
	auto LoweredContained = Lower ? ToLower(Contained) : Contained;
	if (LoweredContainer.find(LoweredContained) != string::npos) return true;
	else return false;
}
inline bool Equals(string a, string b)
{
	if (strcmp(a.c_str(), b.c_str()) == 0)
		return true;
	return false;
}
//isward
inline bool IsWard(IUnit* target)
{
	Vec2 pos;
	return Contains(target->GetObjectName(), "ward") && !Contains(target->GetObjectName(), "corpse");
}
inline SArray<IUnit*> ValidTargets(vector<IUnit*> input)
{
	SArray<IUnit*> targets = SArray<IUnit*>(input);
	return  targets.Where([](IUnit* i) {return i != nullptr && i->IsValidTarget(); });
}
inline SArray<IUnit*> ValidAllies(vector<IUnit*> input)
{
	SArray<IUnit*> targets = SArray<IUnit*>(input);
	return  targets.Where([](IUnit* i) {return i != nullptr && !i->IsDead(); });
}
inline bool IsValidTarget(IUnit* target, float range = 100000, Vec3 RangeCheckFrom = GEntityList->Player()->GetPosition())
{
	return target != nullptr && GEntityList->Player()->IsValidTarget(target, range) && Distance(target, RangeCheckFrom) <= range;
}
inline bool IsValidAllies(IUnit* target, float range = 100000, Vec3 RangeCheckFrom = GEntityList->Player()->GetPosition())
{
	return target != nullptr && !target->IsDead() && Distance(target, RangeCheckFrom) <= range;
}
inline bool IsValidBoth(IUnit* target, float range = 100000, Vec3 RangeCheckFrom = GEntityList->Player()->GetPosition())
{
	return (target->IsEnemy(GEntityList->Player()) && IsValidTarget(target, range, RangeCheckFrom))
		|| (!target->IsEnemy(GEntityList->Player()) && IsValidAllies(target, range, RangeCheckFrom));
}
inline SArray<IUnit*> EnemyMinions(float range = 100000, Vec3 RangeCheckFrom = GEntityList->Player()->GetPosition())
{
	return SArray<IUnit*>(GEntityList->GetAllMinions(false, true, false)).Where([&](IUnit* i) {return IsValidTarget(i, range, RangeCheckFrom) && !IsWard(i) && !Contains(i->GetObjectName(), "barrel"); });
}
inline SArray<IUnit*> AllyMinions(float range = 100000, Vec3 RangeCheckFrom = GEntityList->Player()->GetPosition())
{
	return SArray<IUnit*>(GEntityList->GetAllMinions(true, false, false)).Where([&](IUnit* i) {return IsValidAllies(i, range, RangeCheckFrom) && !IsWard(i) && !Contains(i->GetObjectName(), "barrel"); });
}
inline SArray<IUnit*> NeutralMinions(float range = 100000, Vec3 RangeCheckFrom = GEntityList->Player()->GetPosition())
{
	return SArray<IUnit*>(GEntityList->GetAllMinions(false, false, true)).Where([&](IUnit* i) {return IsValidTarget(i, range, RangeCheckFrom) && !IsWard(i) && !Contains(i->GetObjectName(), "barrel"); });
}
inline SArray<IUnit*> AllMinions(float range = 100000, Vec3 RangeCheckFrom = GEntityList->Player()->GetPosition())
{
	return SArray<IUnit*>(GEntityList->GetAllMinions(true, true, true)).Where([&](IUnit* i) {return IsValidBoth(i, range, RangeCheckFrom) && !IsWard(i) && !Contains(i->GetObjectName(), "barrel"); });
}
inline SArray<IUnit*> WardMinions(float range = 100000, bool jungle = true, bool ally = true, bool enemy = true, Vec3 RangeCheckFrom = GEntityList->Player()->GetPosition())
{
	SArray<IUnit*> allwards = SArray<IUnit*>(GEntityList->GetAllMinions(true, true, true))
		.Where([&](IUnit* i) {return IsValidBoth(i, range, RangeCheckFrom) && IsWard(i); });
	SArray<IUnit*> junglewards = allwards.Where([](IUnit* i) {return i->IsJungleCreep(); });
	SArray<IUnit*> enemywards = allwards.Where([](IUnit* i) {return GEntityList->Player()->IsEnemy(i); });
	SArray<IUnit*> allywards = allwards.Where([](IUnit* i) {return !GEntityList->Player()->IsEnemy(i); });
	SArray<IUnit*> returnwards;
	if (jungle) returnwards.AddRange(junglewards);
	if (ally) returnwards.AddRange(allywards);
	if (enemy) returnwards.AddRange(enemywards);
	return returnwards;
}
inline int CountEnemiesInRange(Vec3 Position, float Range)
{
	vector<IUnit*> a;
	a = SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([&](IUnit* i) { return
		IsValidTarget(i) && Distance(i->GetPosition(), Position) <= Range; }).ToVector();
	return a.size();
}
inline int CountMinionsInRange(Vec3 Position, float Range, bool enemy = true, bool neutral = false, bool ally = false)
{
	int i = 0;
	if (enemy) i += EnemyMinions().Where([&](IUnit* i) {return Distance(i, Position) <= Range; }).Count();
	if (neutral) i += NeutralMinions().Where([&](IUnit* i) {return Distance(i, Position) <= Range; }).Count();
	if (ally) i += AllyMinions().Where([&](IUnit* i) {return Distance(i, Position) <= Range; }).Count();
	return i;
}
inline SArray<IUnit*> ValidEnemies(float range = 100000, Vec3 RangeCheckFrom = GEntityList->Player()->GetPosition())
{
	return SArray<IUnit*>(GEntityList->GetAllHeros(false, true)).Where([&](IUnit* i) {return IsValidTarget(i, range, RangeCheckFrom); });
}
inline SArray<IUnit*> ValidAllies(float range = 100000, Vec3 RangeCheckFrom = GEntityList->Player()->GetPosition())
{
	return SArray<IUnit*>(GEntityList->GetAllHeros(true, false)).Where([&](IUnit* i) {return IsValidAllies(i, range, RangeCheckFrom); });
}
inline SArray<IUnit*> ValidAllHeroes(float range = 100000, Vec3 RangeCheckFrom = GEntityList->Player()->GetPosition())
{
	return SArray<IUnit*>(GEntityList->GetAllHeros(true, true)).Where([&](IUnit* i) {return IsValidBoth(i, range, RangeCheckFrom); });
}
inline bool InAutoAttackRange(IUnit* target)
{
	return Distance(GEntityList->Player(), target) <= GEntityList->Player()->BoundingRadius() + GEntityList->Player()->AttackRange() + target->BoundingRadius();
}
inline bool InSpellRange(ISpell2* spell, IUnit* target)
{
	return Distance(GEntityList->Player(), target) <= spell->Range();
}
inline bool InSpellRange(ISpell2* spell, Vec3 position)
{
	return Distance(GEntityList->Player(), position) <= spell->Range();
}
inline double GetSpellDamage(IUnit* target, int slot)
{
	return GDamage->GetSpellDamage(GEntityList->Player(), target, slot);
}
inline bool HasSummonerSpell(ISpell*  spell)
{
	return spell->GetSpellSlot() != kSlotUnknown && spell->IsReady();
}
inline void CastItemOnUnit(int itemid, float range, IUnit* target)
{
	if (GEntityList->Player()->HasItemId(itemid))
	{
		//IInventoryItem* Item = GPluginSDK->CreateItemForId(itemid, range);
		//if (IsValidTarget(target) && Item->IsReady())
		//{
		//	Item->CastOnTarget(target);
		//}
		//if (target == nullptr)
		//{
		//	Item->CastOnPlayer();
		//}
		AllItems[itemid] = GPluginSDK->CreateItemForId(itemid, range);
		if (IsValidTarget(target) && AllItems[itemid]->IsReady())
		{
			AllItems[itemid]->CastOnTarget(target);
		}
		else if (target == nullptr)
		{
			AllItems[itemid]->CastOnPlayer();
		}
	}
}
inline bool IsCCed(IUnit * hero)
{
	return hero->HasBuffOfType(BUFF_Stun) || hero->HasBuffOfType(BUFF_Snare) || hero->HasBuffOfType(BUFF_Suppression) || hero->HasBuffOfType(BUFF_Charm) || hero->HasBuffOfType(BUFF_Snare);
}
inline bool IsEnoughMana(IMenuOption* Slider)
{
	return GEntityList->Player()->ManaPercent() >= Slider->GetInteger();
}

inline FarmLocation FindBestLineCastPosition(vector<Vec3> RangeCheckFroms, float range, float castrange, float radius, bool Minions, bool Heroes)
{
	FarmLocation result;
	result.HitCount = 0;
	for (Vec3 RangeCheckFrom : RangeCheckFroms)
	{
		auto minions = EnemyMinions(range, RangeCheckFrom);
		auto heroes = ValidEnemies(range, RangeCheckFrom);
		auto castminions = EnemyMinions(castrange, RangeCheckFrom);
		auto castheroes = ValidEnemies(castrange, RangeCheckFrom);
		SArray<IUnit*> targets;
		SArray<IUnit*> casttargets;
		if (Minions)
		{
			targets.AddRange(minions);
			casttargets.AddRange(castminions);
		}
		if (Heroes)
		{
			targets.AddRange(heroes);
			casttargets.AddRange(castheroes);
		}
		for (auto target : casttargets.ToVector())
		{
			Vec3 endpos = Extend(RangeCheckFrom, target->GetPosition(), range);
			int count = targets.Where([&](IUnit* i)
			{ return Distance(i->GetPosition(), Extend(RangeCheckFrom, endpos, -radius / 2), Extend(endpos, RangeCheckFrom, -radius / 2), true) <= radius / 2 + i->BoundingRadius(); }).Count();
			if (count > result.HitCount)
			{
				result.HitCount = count;
				result.CastPosition = endpos;
				result.CastPositionFrom = RangeCheckFrom;
				result.CastOnUnit = target;
			}
		}
	}
	return result;
}
inline Vec4 Red() { return Vec4(255, 0, 0, 255); }
inline Vec4 Green() { return Vec4(0, 255, 0, 255); }
inline Vec4 Pink() { return Vec4(255, 0, 255, 255); }
inline Vec4 Yellow() { return Vec4(255, 255, 0, 255); }

inline bool IsWallBetween(Vec3 start, Vec3 end)
{
	for (int i = 0; i < Distance(start, end); i = i + 25)
	{
		auto flag = GNavMesh->GetCollisionFlagsForPoint(Extend(start, end, i));
		if (flag&kWallMesh || flag&kBuildingMesh)
		{
			return true;
		}
	}
	auto endflag = GNavMesh->GetCollisionFlagsForPoint(end);
	if (endflag&kWallMesh || endflag&kBuildingMesh)
	{
		return true;
	}
	return false;
}
inline bool IsGoingToWard(IUnit* ThisUnit, IUnit* ToUnit)
{
	Vec3 pred;
	GPrediction->GetFutureUnitPosition(ThisUnit, 0.2f, false, pred);
	if (Distance(ToUnit, pred) < Distance(ToUnit, ThisUnit))
	{
		return true;
	}
	return false;
}
inline bool IsInAutoAttackRange(Vec3 position)
{
	return GEntityList->Player()->AttackRange() + GEntityList->Player()->BoundingRadius() * 2 >= Distance(GEntityList->Player(), position);
}
inline bool IsInAutoAttackRange(IUnit* target)
{
	return GEntityList->Player()->AttackRange() + GEntityList->Player()->BoundingRadius() + target->BoundingRadius() >= Distance(GEntityList->Player(), target);
}
inline bool IsADCanCastSpell(bool anymode = false)
{
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo || GOrbwalking->GetOrbwalkingMode() == kModeMixed || anymode)
	{
		if (CountEnemiesInRange(GEntityList->Player()->GetPosition(), GEntityList->Player()->AttackRange() + GEntityList->Player()->BoundingRadius() * 2) == 0)
			return true;
		if (GOrbwalking->CanMove() && !GOrbwalking->CanAttack())
			return true;
		return false;
	}
	else
	{
		return GOrbwalking->CanMove();
	}
}
inline IUnit*  GetOrbwalkTarget()
{
	SArray<IUnit*> ignoretargets = ValidEnemies().Where([&](IUnit*i) {return !IsInAutoAttackRange(i); });
	IUnit* target = GTargetSelector->FindTargetEx(QuickestKill, PhysicalDamage, GEntityList->Player()->AttackRange() + 400, nullptr, true, &ignoretargets.ToVector());
	return target;
}
#pragma endregion 

#pragma  region  Delayaction
struct Action
{
	Action(int time, std::function<void()> callback)
	{
		Time = time + GGame->TickCount();
		CallbackObject = callback;
	}

	void Call()
	{
		CallbackObject();
	}

	std::function<void()> CallbackObject;
	int Time;

};
struct ActionIUnit
{
	ActionIUnit(int time, IUnit* unit, std::function<void(IUnit*)> callback)
	{
		Time = time + GGame->TickCount();
		CallbackObject = callback;
		Unit = unit;
	}

	void Call()
	{
		if (Unit != nullptr)
			CallbackObject(Unit);
	}

	std::function<void(IUnit*)> CallbackObject;
	int Time;
	IUnit* Unit;
};
struct ActionPosition
{
	ActionPosition(int time, Vec3 position, std::function<void(Vec3)> callback)
	{
		Time = time + GGame->TickCount();
		CallbackObject = callback;
		Position = position;
	}

	void Call()
	{
		CallbackObject(Position);
	}

	std::function<void(Vec3)> CallbackObject;
	int Time;
	Vec3 Position;
};

class DelayAction
{
public:
	void OnGameUpdate()
	{
		Actions.erase(std::remove_if(Actions.begin(), Actions.end(), [](Action& Args)
		{
			if (GGame->TickCount() >= Args.Time)
			{
				Args.Call();
				return true;
			}

			return false;
		}), Actions.end());
		ActionsIunit.erase(std::remove_if(ActionsIunit.begin(), ActionsIunit.end(), [](ActionIUnit& Args)
		{
			if (GGame->TickCount() >= Args.Time)
			{
				Args.Call();
				return true;
			}

			return false;
		}), ActionsIunit.end());
		ActionsPosition.erase(std::remove_if(ActionsPosition.begin(), ActionsPosition.end(), [](ActionPosition& Args)
		{
			if (GGame->TickCount() >= Args.Time)
			{
				Args.Call();
				return true;
			}

			return false;
		}), ActionsPosition.end());
	}

	void Add(int Time, std::function<void()> Callback)
	{
		Actions.emplace_back(Time, Callback);
	}
	void AddIUnit(int Time, IUnit* Unit, std::function<void(IUnit*)> Callback)
	{
		ActionsIunit.emplace_back(Time, Unit, Callback);
	}
	void AddPosition(int Time, Vec3 Position, std::function<void(Vec3)> Callback)
	{
		ActionsPosition.emplace_back(Time, Position, Callback);
	}
private:
	std::vector<Action> Actions;
	std::vector<ActionIUnit> ActionsIunit;
	std::vector<ActionPosition> ActionsPosition;
};


#pragma endregion