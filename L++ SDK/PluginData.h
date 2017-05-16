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

/// <summary>
/// Used in AdvPredictionOutput to show what chance you have of hitting target.
/// Note that the comments beside each name is for core prediction and does not apply to plugin prediction overrides.
/// </summary>
enum ePredictionChance
{
	kHitChanceCollision,	// A collision will prevent you from hitting your target
	kHitChanceOutOfRange,	// The target is out of range and will not be hit
	kHitChanceImpossible,	// This won't be used in most cases but there is no possibility to hit your target
	kHitChanceLow,			// This won't be used in most cases but there is a very low chance to hit your target
	kHitChanceMedium,		// You will not reach your target until he reaches the end of his current path (e.g the cast position will always be the end of target path)
	kHitChanceHigh,			// You will hit your target somewhere on his current path before he reaches the end
	kHitChanceVeryHigh,		// Same as kHitChanceHigh except that your target has clicked to a new position within the last 100 ms
	kHitChanceDashing,		// You will hit your target somewhere along his current dash
	kHitChanceImmobile		// Target is immobile, extremely high chance of landing your shot
};

/// <summary>
/// Structure containing teleport information used for OnTeleport event.
/// </summary>
struct OnTeleportArgs
{
	IUnit* Source;	// Object that is teleporting
	int Type;		// The type of teleport (eTeleportType)
	int Status;		// The status of teleport (eTeleportStatus)
	int Duration;	// The duration of the teleport in ms
};

/// <summary>
/// Structure containing information used for OnStopCast event.
/// </summary>
struct OnStopCastArgs
{
	IUnit* Source;
	bool StopAnimation;
	bool ExecuteCastFrame;
	bool ForceStop;
	bool DestroyMissile;
};

/// <summary>
/// Structure containing information used for OnUpdateBuffCount event
/// </summary>
struct OnBuffUpdateCountArgs
{
	IUnit* Source;		// Source unit of the buff
	void* BuffData;		// Data to be passed to GPluginBuffData for more information
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

/// <summary>
/// Game structure holding pathing information, as used by IUnit::GetNavigationPath.
/// A simpler way to get this information is IUnit::GetWaypointList.
/// </summary>
struct NavigationPath
{
	int			CurrentWaypoint_;		// The current index between WaypointStart_ and WaypointEnd_ being moved along
	void*		VirtualMethodTable_;	// Virtual function table pointer (can be ignored)
	Vec3		StartPosition_;			// Beginning of navigation path
	Vec3		EndPosition;			// End of navigation path
	Vec3*		WaypointStart_;			// Pointer to an array of Vec3 holding all waypoints
	Vec3*		WaypointEnd_;			// Pointer to the end of the array of waypoints
};

/// <summary>
/// Structure containing interruptible information used for OnInterruptible event.
/// </summary>
struct InterruptibleSpell
{
	IUnit*					Source;				// Unit that casted an interruptible spell
	eInterruptibleDanger	DangerLevel;		// Danger level of this spell as defined by the core
	float					EndTime;			// Time at which this spell will end
	bool					MovementInterupts;	// True if moving will interrupt the spell (e.g Katarina R)
	void*					Data;				// Data to be passed to GPluginSpellData for extended information
};

/// <summary>
/// Structure containing dash information used for OnDash event.
/// </summary>
struct UnitDash
{
	IUnit*				Source;			// Unit that started dashing
	Vec3				StartPosition;	// Position at which the dash starts
	Vec3				EndPosition;	// Position at which the dash ends
	int					StartTick;		// Tick at which the dash started (IGame::TickCount)
	int					EndTick;		// Tick at which the dash will end (IGame::TickCount)
	int					Duration;		// Duration in ms the dash will last
	float				Speed;			// Speed at which the unit will dash from StartPosition to EndPosition
};

/// <summary>
/// Structure containing gap closer spell information used for OnGapCloser event.
/// </summary>
struct GapCloserSpell
{
	IUnit*	Source;			// Unit that casted this gap closing spell
	Vec3	StartPosition;	// Start position of the spell
	Vec3	EndPosition;	// End position of the spell
	bool	IsTargeted;		// True if the spell is targeted
	int		StartTick;		// Tick at which the spell was cast (IGame::TickCount)
	int		Slot;			// Slot of the spell
	void*	Data;			// Data to be passed to GPluginSpellData for extended information
};

/// <summary>
/// Structure containing various spell information used for events such as OnProcessSpell.
/// </summary>
struct CastedSpell
{
	IUnit*	Caster_;		// Unit that casted this spell
	IUnit*	Target_;		// Target unit or nullptr if it's not a targeted spell
	bool	AutoAttack_;	// True for AA spells
	char	Name_[64];		// Name of the spell
	float	Windup_;		// Windup time (e.g delay before the missile is actually sent, movement can possibly interrupt the cast during this time)
	float	Animation_;		// Animation time
	Vec3	Position_;		// Position this cast was sent from
	void*	Data_;			// Data to be passed to GPluginSpellData for extended information
	float	Radius_;		// Radius of the spell
	float	Speed_;			// Speed of the spell
	float	Damage_;		// Damage of the spell
	float	Range_;			// Range of the spell
	Vec3	EndPosition_;	// Position this cast was sent towards
};

/// <summary>
/// Structure containing information about a units last casted spell as taken from IUnit::GetLastCastedSpell
/// </summary>
struct LastCastedSpellArgs
{
	CastedSpell		Data; // Spell data
	int				Tick; // Tick this spell was cast (IGame::TickCount)
};

/// <summary>
/// Structure containing basic item information as taken from IUnit::AllItems
/// </summary>
struct ItemData
{
	char Name_[64];		// Name of the item
	int Id_;			// Id of the item
};

#pragma region Deprecated
/// <summary>
/// Structure passed to ISpell (deprecated) to initialize multiple skill shot variables.
/// </summary>
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
#pragma endregion

/// <summary>
/// Structure passed for OnJungleNotify event.
/// </summary>
struct JungleNotifyData
{
	/// <summary>
	/// The position of the jungle notification.
	/// </summary>
	Vec3 Position;
};

/// <summary>
/// Data structure used when finding hero masteries (IUnit::GetAllMasteries, etc.)
/// </summary>
struct HeroMastery
{
	/// <summary>
	/// The mastery page (Ferocity, Cunning, etc.)
	/// </summary>
	int PageId;

	/// <summary>
	/// The mastery identifier (Sorcery, Wanderer, etc.)
	/// </summary>
	int MasteryId;

	/// <summary>
	/// The number of points this mastery has leveled.
	/// </summary>
	int Points;
};

/// <summary>
/// Universal unit class for every type (hero, minion, turret, missile, etc.)
/// Not every function here will work for every unit type.
/// Most functions in this list will require GetType() returns nonzero.
/// Use GPluginMissileData to get extended information for missile units.
/// </summary>
class IUnit
{
public:
	virtual ~IUnit() { }

	/// <summary>
	/// Gets the attack speed.
	/// </summary>
	/// <returns>Attack speed.</returns>
	virtual float AttackSpeed() = 0;

	/// <summary>
	/// Gets the movement speed.
	/// </summary>
	/// <returns></returns>
	virtual float MovementSpeed() = 0;

	/// <summary>
	/// Gets the flat armor reduction.
	/// </summary>
	/// <returns></returns>
	virtual float ArmorReductionFlat() = 0;

	/// <summary>
	/// Gets the flat magic reduction.
	/// </summary>
	/// <returns></returns>
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
	virtual void* GetBuffDataByIndex(int Idx) = 0;
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
	virtual LastCastedSpellArgs* GetLastCastedSpell() = 0;
	virtual int GetKills() = 0;
	virtual int GetDeaths() = 0;
	virtual int GetAssists() = 0;
	virtual float GetExperience() = 0;
	virtual float GetBonusArmor() = 0;

	/// <summary>
	/// Gets the masteries for a hero.
	/// </summary>
	/// <param name="Out">Output showing all masteries.</param>
	/// <returns>True if masteries were found and at least one exists.</returns>
	virtual bool GetMasteries(std::vector<HeroMastery>& Out) = 0;

	/// <summary>
	/// Determines whether this object [is in screen space].
	/// </summary>
	/// <returns>
	///   <c>true</c> if [is on screen]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsOnScreen() = 0;

	/// <summary>
	/// Determines whether [is hp bar being rendered].
	/// </summary>
	/// <returns>
	///   <c>true</c> if [is hp bar being rendered]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool IsHpBarBeingRendered() = 0;

	/// <summary>
	/// Gets the dash data.
	/// </summary>
	/// <param name="Out">The out.</param>
	// <returns>
	///   <c>true</c> if [is dashing]; otherwise, <c>false</c>.
	/// </returns>
	virtual bool GetDashData(UnitDash* Out) = 0;

	/// <summary>
	/// Gets the unit class identifier.
	/// </summary>
	/// <returns>Object type (eGameObjectClassId).</returns>
	virtual eGameObjectClassId GetClassId() = 0;

	/// <summary>
	/// Gets the cooldown reduction percent.
	/// Calculation: Cooldown *= (GetCooldownReductionPercent() + 1.0).
	/// </summary>
	/// <returns>Cooldown Reduction Percent.</returns>
	virtual float GetCooldownReductionPercent() = 0;
};

#endif // PluginData_h__
