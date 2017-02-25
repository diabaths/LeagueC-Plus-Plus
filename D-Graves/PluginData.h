#ifndef PluginData_h__
#define PluginData_h__

#include <Windows.h>
#include <vector>
#include <cstdint>
#include <functional>

#include "Vector3.h"
#include "LPPConstants.h"

class IUnit;
class ISpellBook;

enum ePredictionChance
{
	kHitChanceCollision,
	kHitChanceOutOfRange,
	kHitChanceImpossible,
	kHitChanceLow,
	kHitChanceMedium,
	kHitChanceHigh,
	kHitChanceVeryHigh,
	kHitChanceDashing,
	kHitChanceImmobile
};

struct AdvPredictionInput
{
	Vec3 FromPosition;				// Start position for casting
	Vec3 RangeCheckFromPosition;	// Start position for prediction range checks
	bool IsAoE;						// True for area of effect spells
	bool AddBoundingRadius;			// Adds target bounding radius to prediction
	int CollisionFlags;				// (Example kCollidesWithMinions|kCollidesWithYasuoWall)
	float Delay;					// Delay in seconds for cast (e.g WindupTime)
	float Radius;					// Radius of the spell
	float Range;					// Range of the spell
	float Speed;					// Speed of the spell
	int Type;						// Type of the spell (e.g kLineCast)
	IUnit* Target;					// Unit to run prediction for
};

struct AdvPredictionOutput
{
	int HitChance;						// Odds of hitting target (e.g kHitChanceHigh)
	Vec3 CastPosition;					// Predicted position of where you should cast
	Vec3 TargetPosition;				// Predicted position of unit when spell will land
	std::vector<IUnit*> AoETargetsHit;	// Vector of all targets hit when using AoE prediction
};

struct NavigationPath
{
	int			CurrentWaypoint_;
	void*		VMT;
	Vec3		StartPosition_;
	Vec3		EndPosition;
	Vec3*		WaypointStart_;
	Vec3*		WaypointEnd_;
};

struct InterruptibleSpell
{
	IUnit*					Target;
	eInterruptibleDanger	DangerLevel;
	float					EndTime;
	bool					MovementInterupts;
	void*					Data;
};

struct UnitDash
{
	IUnit*				Source;
	Vec3				StartPosition;
	Vec3				EndPosition;
	int					StartTick;
	int					EndTick;
	int					Duration;
	float				Speed;
};

struct GapCloserSpell
{
	IUnit* Sender;
	Vec3 StartPosition;
	Vec3 EndPosition;
	bool IsTargeted;
	int StartTick;
	int Slot;
	void* Data;
};

struct CastedSpell
{
	IUnit*	Caster_;
	IUnit*	Target_;
	bool	AutoAttack_;
	char	Name_[64];
	float	Windup_;
	float	Animation_;
	Vec3	Position_;
	void*	Data_;
	float	Radius_;
	float	Speed_;
	float	Damage_;
	float	Range_;
	Vec3	EndPosition_;
};

struct ItemData
{
	char Name_[64];
	int Id_;
};

struct SpellParams
{
	SpellParams() { ZeroMemory(this, sizeof(*this)); }

	SpellParams(float Delay, float Speed, float Width = 0, bool Collision = false, eSpellType Type = kLineCast)
	{
		Delay_ = Delay;
		Speed_ = Speed;
		Width_ = Width;
		Collision_ = Collision;
		SpellType_ = Type;
	}

	float		Delay_;
	float		Speed_;
	float		Width_;
	bool		Collision_;
	eSpellType	SpellType_;
};

struct JungleNotifyData
{
	Vec3 Position;
};

class IUnit
{
public:
	virtual ~IUnit() { }

	virtual float AttackSpeed() = 0;
	virtual float MovementSpeed() = 0;
	virtual float ArmorReductionFlat() = 0;
	virtual float MagicReductionFlat() = 0;
	virtual float ArmorReductionPercent() = 0;
	virtual float MagicReductionPercent() = 0;
	virtual float ArmorPenetrationPercent() = 0;
	virtual float MagicPenetrationPercent() = 0;
	virtual float ArmorPenetrationFlat() = 0;
	virtual float MagicPenetrationFlat() = 0;
	virtual float PercentMagicDamageMod() = 0;
	virtual float Armor() = 0;
	virtual float MagicResist() = 0;
	virtual float PhysicalDamage() = 0;
	virtual float BonusDamage() = 0;
	virtual float PhysicalDamageMod() = 0;
	virtual float MagicDamage() = 0;
	virtual float BonusMagicDamage() = 0;
	virtual float AttackRange() = 0;
	virtual float TotalPhysicalDamage() = 0;
	virtual float TotalMagicDamage() = 0;
	virtual Vec3 const& ServerPosition() = 0;
	virtual NavigationPath* GetNavigationPath() = 0;
	virtual float BoundingRadius() = 0;
	virtual Vec3 const& GetPosition() = 0;
	virtual bool IsMelee() = 0;
	virtual bool IsRanged() = 0;
	virtual int GetTargetId() = 0;
	virtual const char* SkinName() = 0;
	virtual float GetMana() = 0;
	virtual float GetMaxMana() = 0;
	virtual float ManaPercent() = 0;
	virtual float HealthPercent() = 0;
	virtual int GetLevel() = 0;
	virtual bool HasBuff(const char*) = 0;
	virtual bool GetBounds(Vec3* Out_Min, Vec3* Out_Max) = 0;
	virtual bool GetHitboxCenter(Vec3* Out_Hitbox) = 0;
	virtual int GetNetworkId() = 0;
	virtual bool HasItem(const char*) = 0;
	virtual const char* GetObjectName() = 0;
	virtual int GetTeam() = 0;
	virtual bool IsEnemy(IUnit* other) = 0;
	virtual int UnitFlags() = 0;
	virtual int GetType() = 0;
	virtual bool IsCreep() = 0;
	virtual bool IsHero() = 0;
	virtual bool IsTurret() = 0;
	virtual bool IsMissile() = 0;
	virtual bool IsJungleCreep() = 0;
	virtual bool IsDead() = 0;
	virtual float GetHealth() = 0;
	virtual float GetMaxHealth() = 0;
	virtual eSpellState GetSpellState(eSpellSlot) = 0;
	virtual std::vector<ItemData> AllItems() = 0;
	virtual float WindupTime() = 0;
	virtual float AnimationTime() = 0;
	virtual bool HasItemId(int) = 0;
	virtual CastedSpell const& GetAutoAttack() = 0;
	virtual bool IsValidTarget(IUnit*, float) = 0;
	virtual bool IsVisible() = 0;
	virtual eSpellSlot GetSpellSlot(const char*) = 0;
	virtual std::vector<Vec3> GetWaypointList() = 0;
	virtual int GetBuffCount(const char*) = 0;
	virtual int GetSpellLevel(int) = 0;
	virtual const char* ChampionName() = 0;
	virtual bool IsChasing(IUnit* Other) = 0;
	virtual bool HasIncomingDamage() = 0;
	virtual bool IsRecalling() = 0;
	virtual bool HasBuffOfType(eBuffType Type) = 0;
	virtual int NumberOfDebuffs() = 0;
	virtual float HPRegenRate() = 0;
	virtual float GetRealAutoAttackRange(IUnit* Other) = 0;
	virtual void SetSkinId(int Id) = 0;
	virtual int GetSkinId() = 0;
	virtual bool IsInvulnerable() = 0;
	virtual bool IsTargetable() = 0;
	virtual int MaxSpells() = 0;
	virtual const char* GetSpellName(int Slot) = 0;
	virtual float GetSpellRemainingCooldown(int Slot) = 0;
	virtual float GetSpellTotalCooldown(int Slot) = 0;
	virtual bool GetHPBarPosition(Vec2& Out) = 0;
	virtual float GetBuffStartTime(const char* Name) = 0;
	virtual IUnit* GetClone() = 0;
	virtual bool IsClone() = 0;
	virtual Vec3 const Direction() = 0;
	virtual bool IsFacing(IUnit* Other) = 0;
	virtual void LevelUpSpell(int Slot) = 0;
	virtual int GetCharacterState() = 0;
	virtual bool IsWindingUp() = 0;
	virtual bool IsValidTarget() = 0;
	virtual bool IsCastingImportantSpell(float* EndTime) = 0;
	virtual void* GetBuffDataByName(const char* Name) = 0;
	virtual void* GetBuffByIndex(int Idx) = 0;
	virtual int GetNumberOfBuffs() = 0;
	virtual ISpellBook* GetSpellBook() = 0;
	virtual IUnit* GetBuffCaster(const char* Name) = 0;
	virtual void GetAllBuffsData(std::vector<void*>& Out) = 0;
	virtual IUnit* GetPet() = 0;
	virtual float BonusArmorPenetrationPercent() = 0;
	virtual float Crit() = 0;
	virtual bool IsMoving() = 0;
	virtual float CritDamageMultiplier() = 0;
	virtual int GetTimeVisibleMs() = 0;
	virtual bool IsWard() = 0;
	virtual bool IsValidObject() = 0;
	virtual const char* GetClassIdentifier() = 0;
	virtual bool IsDashing() = 0;
	virtual bool CreatePath(Vec3 const& EndPosition, std::vector<Vec3>& Out) = 0;
	virtual bool CreatePath2D(Vec2 const& EndPosition, std::vector<Vec2>& Out) = 0;
	virtual const char* GetBaseSkinName() = 0;
	virtual float GetBonusMana() = 0;
};

#endif // PluginData_h__