#ifndef PluginSDK_h__
#define PluginSDK_h__

#include "PluginData.h"

#define PLUGIN_API			extern "C" __declspec(dllexport)
#define PLUGIN_EVENT(T)		static T __cdecl
#define PLUGIN_EVENTD(T)	T __cdecl

#define PluginSetup(x) \
	BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved) { return TRUE; }

#define PluginSDKSetup(x) \
	GPluginSDK			= x; \
	GOrbwalking			= x->GetOrbwalking(); \
	GEventManager		= x->GetEventManager(); \
	GRender				= x->GetRenderer(); \
	GEntityList			= x->GetEntityList(); \
	GGame				= x->GetGame(); \
	GDamage				= x->GetDamage(); \
	GPrediction			= x->GetPrediction(); \
	GHealthPrediction	= x->GetHealthPrediction(); \
	GTargetSelector		= x->CreateTargetSelector(); \
	GSpellData 			= x->GetSpellDataReader(); \
	GBuffData			= x->GetBuffDataReader(); \
	GMissileData		= x->GetMissileDataReader(); \
	GNavMesh			= x->GetNavMesh(); \
	GUtility			= x->GetUtility();

class IFont
{
public:
	virtual void SetColor(Vec4 const& Color) = 0;
	virtual void SetLocationFlags(int Flags) = 0;
	virtual void Render(float XPosition, float YPosition, const char* Fmt, ...) = 0;
	virtual void SetOutline(bool Enabled) = 0;
};

class ITexture
{
public:
	virtual void Scale(float ScaleBorder) = 0;
	virtual void Scale(float ScaleX, float ScaleY) = 0;
	virtual void Resize(float SizeBorder) = 0;
	virtual void Resize(float SizeX, float SizeY) = 0;
	virtual void Draw(float XPosition, float YPosition) = 0;
	virtual Vec2 const& GetSize() = 0;
	virtual void SetColor(Vec4 const& Color) = 0;
	virtual void DrawCircle(float XPosition, float YPosition, float Radius) = 0;
	virtual void SetScaleBySize(Vec2 const& WantedSize) = 0;
	virtual Vec2 const& GetScaledOffset(Vec2 const& OriginalOffset) = 0;
	virtual Vec2 const& GetScaledSize(Vec2 const& OriginalSize) = 0;
};

class IRender
{
public:
	virtual void DrawText(Vec2 const& Position, Vec4 const& Color, const char* Text, ...) = 0;
	virtual void DrawLine(Vec2 const& Position1, Vec2 const& Position2, Vec4 const& Color) = 0;
	virtual void DrawFilledBox(Vec2 const& Position, Vec2 const& Size, Vec4 const& Color) = 0;
	virtual void DrawOutinedBox(Vec2 const& Position, Vec2 const& Size, float Width, Vec4 const& Color) = 0;
	virtual void DrawOutlinedCircle(Vec3 const& Position, Vec4 const& Color, float Radius) = 0;
	virtual void DrawFilledCircle(Vec3 const& Position, Vec4 const& Color, float Radius) = 0;
	virtual ITexture* CreateTextureFromFile(const char* Filename) = 0;
	virtual ITexture* CreateTextureFromMemory(uint8_t* Data, uint32_t DataLength, const char* Filename) = 0;
	virtual Vec2 const& ScreenSize() = 0;
	virtual IFont* CreateFont(const char* Typeface, float Size, int Style = kFontWeightNormal) = 0;
	virtual void Notification(Vec4 const& Color, DWORD SecondsToShow, const char* Message, ...) = 0;
	virtual void DrawOutlinedCircle(Vec2 const& Position, Vec4 const& Color, float Radius) = 0;
	virtual void NotificationEx(Vec4 const& Color, DWORD SecondsToShow, bool PrintInChat, bool ShowInCorner, const char* Fmt, ...) = 0;
	virtual void DrawCircle(Vec3 const& Position, float Radius, Vec4 const& Color, float Width = 5.f, bool FillCircle = false, bool ZEnable = false) = 0;
};

class IEntityList
{
public:
	virtual int NumberOfEntities() = 0;
	virtual IUnit* GetEntityAt(int Idx) = 0;
	virtual IUnit* Player() = 0;
	virtual std::vector<IUnit*> GetAllHeros(bool Friendly, bool Enemy) = 0;
	virtual std::vector<IUnit*> GetAllMinions(bool Friendly, bool Enemy, bool Neutral) = 0;
	virtual std::vector<IUnit*> GetAllTurrets(bool Friendly, bool Enemy) = 0;
	virtual std::vector<IUnit*> GetAllUnits() = 0;
	virtual std::vector<IUnit*> GetAllMissiles(bool Friendly, bool Enemy) = 0;
	virtual std::vector<IUnit*> GetAllInhibitors(bool Friendly, bool Enemy) = 0;
	virtual IUnit* GetEnemyNexus() = 0;
	virtual IUnit* GetTeamNexus() = 0;
	virtual bool DoesObjectExist(IUnit* Source) = 0;
	virtual IUnit* GetEntityByNetworkId(int NetworkId) = 0;
	virtual IUnit* GetEntityByTargetId(int TargetId) = 0;
};

class IGame
{
public:
	virtual void PrintChat(const char*) = 0;
	virtual bool Projection(Vec3 const&, Vec2*) = 0;
	virtual int Latency() = 0;
	virtual int Status() = 0;
	virtual float Time() = 0;
	virtual Vec3 const& CursorPosition() = 0;
	virtual bool IssueOrder(IUnit* Source, eGameObjectOrder Order, Vec3 const& Position) = 0;
	virtual bool IssueOrder(IUnit* Source, eGameObjectOrder Order, IUnit* Target) = 0;
	virtual float IntervalPerTick() = 0;
	virtual void PrintChatEx(const char* Message, Vec3 const& Color) = 0;
	virtual bool WorldToMinimap(Vec3 const& World, Vec2& Minimap) = 0;
	virtual IUnit* GetSelectedTarget() = 0;
	virtual void ShowPing(int PingType, IUnit* Target, bool PlaySound) = 0;
	virtual void ShowPing(int PingType, Vec3 const& Position, bool PlaySound) = 0;
	virtual void SendPing(int PingType, IUnit* Target) = 0;
	virtual void SendPing(int PingType, Vec3 const& Position) = 0;
	virtual int GetGameType() = 0;
	virtual int GetMapId() = 0;
	virtual void Say(const char* Fmt, ...) = 0;
	virtual void Taunt(int TauntId) = 0;
	virtual bool BuyItem(int ItemId) = 0;
	virtual bool SellItem(int Slot) = 0;
	virtual void UndoBuy() = 0;
	virtual void SwapItems(int Slot1, int Slot2) = 0;
	virtual void Quit() = 0;
	virtual bool CanLevelUpSpell(int Slot) = 0;
	virtual bool Projection(Vec3 const&, Vec3*) = 0;
	virtual int TickCount() = 0;
	virtual int CurrentTick() = 0;
	virtual bool IsChatOpen() = 0;
	virtual void ScreenToWorld(Vec2 const& ScreenPosition, Vec3* WorldPosition) = 0;
	virtual bool WithinFogOfWar(Vec3 const& Position) = 0;
	virtual bool IsShopOpen() = 0;
	virtual bool IsScoreboardOpen() = 0;
};

class IDamage
{
public:
	virtual double GetAutoAttackDamage(IUnit* Source, IUnit* Target, bool Use_Passives) = 0;
	virtual double CalcPhysicalDamage(IUnit* Source, IUnit* Target, double Damage) = 0;
	virtual double GetSummonerSpellDamage(IUnit* Source, IUnit* Target, eSummonerSpell SummonerSpell) = 0;
	virtual double GetSpellDamage(IUnit* Source, IUnit* Target, int Slot) = 0;
	virtual double CalcMixedDamage(IUnit* Source, IUnit* Target, double PhysicalDamage, double MagicDamage, int MagicPct, int PhysicalPct, int TruePct) = 0;
	virtual double CalcMagicDamage(IUnit* Source, IUnit* Target, double Damage) = 0;
	virtual double GetSpellDamage(IUnit* Source, IUnit* Target, int Slot, int Stage) = 0;
};

class ITargetSelector
{
public:
	virtual IUnit* FindTarget(eTargetPriority Priority, eDamageType Type, float Range) = 0;
	virtual IUnit* GetFocusedTarget() = 0;
	virtual void SetOverrideFocusedTarget(IUnit* Focused) = 0;

	/// <summary>
	/// Finds the best target
	/// </summary>
	/// <param name="Priority">How to prioritize the best target</param>
	/// <param name="Type">Damage type for calculations</param>
	/// <param name="Range">Max range</param>
	/// <param name="RangeCheckFrom">Optional start position for range checks</param>
	/// <param name="IgnoreShield">If set to <c>true</c> [ignore shields].</param>
	/// <param name="IgnoredChamps">Champions to ignore</param>
	/// <param name="Conditions">Currently unused</param>
	/// <returns>Best target found or nullptr</returns>
	virtual IUnit* FindTargetEx(eTargetPriority Priority, eDamageType Type, float Range, Vec3* RangeCheckFrom = nullptr, bool IgnoreSpellShields = true, std::vector<IUnit*>* IgnoredChamps = nullptr, void* Conditions = nullptr) = 0;
};

class IPrediction
{
public:
	virtual void GetFutureUnitPosition(IUnit* Player, float FutureSeconds, bool IncludeLatency, Vec3& Out) = 0;
	virtual IUnit* SimulateMissile(Vec3 const& StartPosition, IUnit* Target, float Speed, float Radius, float Range, float Delay, int CollisionFlags, Vec3& CastPosition) = 0;
	virtual void FindBestCastPosition(float Range, float Radius, bool IsMissile, bool CheckMinions, bool CheckHeroes, Vec3& CastPosition, int& HitEnemyCount) = 0;
	virtual bool TestLineOfSight(Vec3 const& StartPosition, Vec3 const& EndPosition, Vec3& CollisionPositionOut, int& CollisionFlagsOut) = 0;
	virtual void FindBestCastPosition(float Range, float Radius, bool IsMissile, bool CheckMinions, bool CheckHeroes, Vec3& CastPosition, int& HitEnemyCount, float Delay) = 0;
	virtual int GetCollisionFlagsForPoint(Vec3 const& Position) = 0;
	virtual bool IsPointWall(Vec3 const& Position) = 0;
	virtual bool IsPointGrass(Vec3 const& Position) = 0;
	virtual void RunPrediction(AdvPredictionInput* Input, AdvPredictionOutput* Output, uint32_t PredictionVersion = 1) = 0;
};

class IMenuOption
{
public:
	virtual bool Enabled() = 0;
	virtual int GetInteger() = 0;
	virtual float GetFloat() = 0;
	virtual DWORD GetColor() = 0;
	virtual void GetColor(Vec4*) = 0;
	virtual void UpdateInteger(int) = 0;
	virtual void UpdateFloat(float) = 0;
	virtual void UpdateColor(DWORD) = 0;
};

class IMenu
{
public:
	virtual IMenu* AddMenu(const char* Title) = 0;
	virtual IMenuOption* CheckBox(const char* Name, bool Value) = 0;
	virtual IMenuOption* AddInteger(const char* Name, int MinValue, int MaxValue, int Value) = 0;
	virtual IMenuOption* AddFloat(const char* Name, float MinValue, float MaxValue, float Value) = 0;
	virtual IMenuOption* AddColor(const char* Name, DWORD Value) = 0;
	virtual IMenuOption* AddColor(const char* Name, float R, float G, float B, float A) = 0;
	virtual void SaveSettings() = 0;
	virtual void Remove() = 0;
	virtual IMenuOption* GetOption(const char* Name) = 0;
	virtual IMenuOption* AddKey(const char* Name, int DefaultKey) = 0;
	virtual IMenuOption* AddSelection(const char* Name, int DefaultIdx, std::vector<std::string> const& Names) = 0;
};

class IEventManager
{
public:
	virtual void AddEventHandler(eLeagueEvents EventId, LPVOID lpCallback) = 0;
	virtual void RemoveEventHandler(eLeagueEvents EventId, LPVOID lpCallback) = 0;
};

class IHealthPrediction
{
public:
	virtual float GetPredictedHealth(IUnit* Source, eHealthPredictionType Prediction, int TimeMs, int DelayMs) = 0;
	virtual float GetKSDamage(IUnit* Target, int SpellSlot, float Delay, bool IncludeMissiles) = 0;
};

class ISpell
{
public:
	virtual void SetupSpell(SpellParams const& Params) = 0;
	virtual bool CastOnUnit(IUnit* Target) = 0;
	virtual bool CastOnPosition(Vec3 const& Position) = 0;
	virtual bool CastFromPosition(Vec3 const& From, Vec3 const& To) = 0;
	virtual bool CastOnPlayer() = 0;
	virtual void SetSpellSlot(eSpellSlot Slot) = 0;
	virtual void SetSpellRange(float Range) = 0;
	virtual float GetSpellRange() = 0;
	virtual eSpellSlot GetSpellSlot() = 0;
	virtual bool IsReady() = 0;
	virtual void SetSkillshot(float Delay, float Width, float Speed, bool Collision, eSpellType Type) = 0;
	virtual void SetPhysicsVarsFromSpellbook(float Delay) = 0;
	virtual float GetSpeed() = 0;
	virtual float GetRadius() = 0;
	virtual float GetDelay() = 0;
	virtual float GetManaCost() = 0;
};

class ISpell2
{
public:
	virtual bool CastOnTarget(IUnit* Target, int MinimumHitChance = kHitChanceHigh) = 0;
	virtual bool CastOnTargetAoE(IUnit* Target, int MinimumChampionsLanded = 2, int MinimumHitChance = kHitChanceHigh) = 0;
	virtual bool LastHitMinion() = 0;
	virtual bool AttackMinions(int MinimumEnemiesLanded = 3) = 0;
	virtual bool CastOnPlayer() = 0;
	virtual bool CastOnPosition(Vec3 const& Position) = 0;
	virtual bool CastOnUnit(IUnit* Target) = 0;
	virtual void FindBestCastPosition(bool IncludeMinions, bool IncludeHeroes, Vec3& CastPosition, int& EnemiesLanded) = 0;
	virtual IUnit* FindTarget(eDamageType DamageType) = 0;
	virtual bool IsReady() = 0;
	virtual float ManaCost() = 0;
	virtual float Range() = 0;
	virtual float Radius() = 0;
	virtual float Speed() = 0;
	virtual float GetDelay() = 0;
	virtual void SetOverrideSpeed(float Value) = 0;
	virtual void SetOverrideDelay(float Value) = 0;
	virtual void SetOverrideRange(float Value) = 0;
	virtual void SetOverrideRadius(float Value) = 0;
	virtual void SetSkillshot(float OverrideDelay, float OverrideRadius, float OverrideSpeed, float OverrideRange) = 0;
	virtual void SetCharged(float RangeMin, float RangeMax, float DeltaTime) = 0;
	virtual bool IsCharging() = 0;
	virtual void StartCharging() = 0;
	virtual void StartCharging(Vec3 const& Position) = 0;
	virtual float GetChargePercent() = 0;
	virtual int GetSlot() = 0;
	virtual void SetFrom(Vec3 const& Position) = 0;
	virtual void SetRangeCheckFrom(Vec3 const& Position) = 0;
	virtual bool RunPrediction(IUnit* Target, bool IsAoE, int CollisionFlags, AdvPredictionOutput* Output, uint32_t PredictionVersion = 1) = 0;
	virtual bool CastFrom(Vec3 const& StartPosition, Vec3 const& EndPosition) = 0;
	virtual eSpellType GetType() = 0;
	virtual Vec3 const& GetRangeCheckFrom() = 0;
	virtual int GetCollisionFlags() = 0;
};

class IOrbwalking
{
public:
	virtual void SetOverrideTarget(IUnit* Target) = 0;
	virtual void SetOverridePosition(Vec3 const& Position) = 0;
	virtual void DisableNextAttack() = 0;
	virtual void SetMovementAllowed(bool Enabled) = 0;
	virtual void SetAttacksAllowed(bool Enabled) = 0;
	virtual IUnit* GetLastTarget() = 0;
	virtual Vec3 GetLastPosition() = 0;
	virtual eOrbwalkingMode GetOrbwalkingMode() = 0;
	virtual bool CanAttack() = 0;
	virtual bool CanMove(float Delay = 0.f) = 0;
	virtual void ResetAA() = 0;
	virtual float GetAutoAttackRange(IUnit* Target) = 0;
	virtual void Orbwalk(IUnit* Target, Vec3 const& Position) = 0;
};

class IInventoryItem
{
public:
	virtual bool IsOwned() = 0;
	virtual bool IsReady() = 0;
	virtual int Stacks() = 0;
	virtual int Charges() = 0;
	virtual const char* GetName() = 0;
	virtual const char* DisplayName() = 0;
	virtual const char* RequiredSpellName() = 0;
	virtual const char* RequiredChampion() = 0;
	virtual int RequiredLevel() = 0;
	virtual int ItemId() = 0;
	virtual int ItemSpellSlot() = 0;
	virtual int MaxStack() = 0;
	virtual int Price() = 0;
	virtual bool Consumed() = 0;
	virtual bool UsableInStore() = 0;
	virtual bool ConsumeOnAcquire() = 0;
	virtual bool Clickable() = 0;
	virtual bool ShowInActiveItemDisplay() = 0;
	virtual bool CanBeSold() = 0;
	virtual float SellBackModifier() = 0;
	virtual bool InStore() = 0;
	virtual bool CastOnPlayer() = 0;
	virtual bool CastOnTarget(IUnit* Target) = 0;
	virtual bool CastOnPosition(Vec3 const& Position) = 0;
	virtual bool IsTargetInRange(IUnit* Target) = 0;
	virtual bool IsPointInRange(Vec3 const& Position) = 0;
	virtual void SetRange(float Range) = 0;
};

class ISpellData
{
public:
	virtual IUnit* GetCaster(void* Data) = 0;
	virtual IUnit* GetTarget(void* Data) = 0;
	virtual bool IsAutoAttack(void* Data) = 0;
	virtual int NumberOfTargets(void* Data) = 0;
	virtual const char* GetSpellName(void* Data) = 0;
	virtual float GetAnimationDelay(void* Data) = 0;
	virtual float GetWindupTime(void* Data) = 0;
	virtual Vec3 GetStartPosition(void* Data) = 0;
	virtual Vec3 GetEndPosition(void* Data) = 0;
	virtual float CastConeAngle(void* Data) = 0;
	virtual float ManaCost(void* Data) = 0;
	virtual float GetRadius(void* Data) = 0;
	virtual float GetSpeed(void* Data) = 0;
	virtual float GetBaseDamage(void* Data) = 0;
	virtual float GetRange(void* Data) = 0;
	virtual float CastTargetAdditionalUnitsRadius(void* Data) = 0;
	virtual float SpellCastTime(void* Data) = 0;
	virtual int GetLevel(void* Data) = 0;
	virtual int GetSlot(void* Data) = 0;
};

class ISpellBook
{
public:
	virtual bool IsCharging() = 0;
	virtual bool IsChanneling() = 0;
	virtual float GetCastEndTime() = 0;
	virtual int GetSpellState(int Slot) = 0;
	virtual bool IsValidSpell(int Slot) = 0;
	virtual float GetNextCastTime(int Slot) = 0;
	virtual int GetLevel(int Slot) = 0;
	virtual float GetTotalCooldown(int Slot) = 0;
	virtual float GetCastConeAngle(int Slot) = 0;
	virtual float GetManaCost(int Slot) = 0;
	virtual float GetRadius(int Slot) = 0;
	virtual float GetSpeed(int Slot) = 0;
	virtual const char* GetName(int Slot) = 0;
	virtual float GetBaseDamage(int Slot) = 0;
	virtual float GetRange(int Slot) = 0;
	virtual float GetSpellCastTime(int Slot) = 0;
	virtual int GetToggleState(int Slot) = 0;
	virtual float GetCastTime() = 0;
	virtual int GetAmmo(int Slot) = 0;
};

class IBuffData
{
public:
	virtual bool IsValid(void* Data) = 0;
	virtual int GetStacks(void* Data) = 0;
	virtual IUnit* GetCaster(void* Data) = 0;
	virtual const char* GetSourceName(void* Data) = 0;
	virtual const char* GetBuffName(void* Data) = 0;
	virtual float GetStartTime(void* Data) = 0;
	virtual float GetEndTime(void* Data) = 0;
	virtual bool IsActive(void* Data) = 0;
	virtual eBuffType GetBuffType(void* Data) = 0;
};

class IMissileData
{
public:
	virtual int GetSpellSlot(void* Data) = 0;
	virtual IUnit* GetCaster(void* Data) = 0;
	virtual IUnit* GetTarget(void* Data) = 0;
	virtual Vec3 GetEndPosition(void* Data) = 0;
	virtual Vec3 GetStartPosition(void* Data) = 0;
	virtual float GetCastConeAngle(void* Data) = 0;
	virtual float GetRadius(void* Data) = 0;
	virtual float GetSpeed(void* Data) = 0;
	virtual const char* GetName(void* Data) = 0;
	virtual float GetBaseDamage(void* Data) = 0;
	virtual float GetRange(void* Data) = 0;
	virtual float GetSpellCastTime(void* Data) = 0;
	virtual bool IsAutoAttack(void* Data) = 0;
};

class INavMesh
{
public:
	virtual bool TestLineOfSight(Vec3 const& StartPosition, Vec3 const& EndPosition, Vec3& CollisionPositionOut, int& CollisionFlagsOut) = 0;
	virtual int GetCollisionFlagsForPoint(Vec3 const& Position) = 0;
	virtual bool IsPointWall(Vec3 const& Position) = 0;
	virtual bool IsPointGrass(Vec3 const& Position) = 0;
	virtual float GetHeightForPoint(Vec2 const& Position) = 0;
};

class IUtility
{
public:
	virtual bool IsLeagueWindowFocused() = 0;
	virtual bool IsPositionInFountain(Vec3 const& Source, bool CheckTeamFountain = true, bool CheckEnemyFountain = false) = 0;
	virtual bool IsPositionUnderTurret(Vec3 const& Source, bool CheckTeamTurrets = false, bool CheckEnemyTurrets = true) = 0;
	virtual void CreateDebugConsole() = 0;
	virtual void DestroyDebugConsole() = 0;
	virtual void LogConsole(const char* Fmt, ...) = 0;
	virtual void LogFile(const char* Filename, const char* Fmt, ...) = 0;
	virtual void ClearLogFile(const char* Filename) = 0;
	virtual Vec3 To3D(Vec2 const& Other) = 0;
};

class IPluginSDK
{
public:
	virtual IOrbwalking* GetOrbwalking() = 0;
	virtual IEventManager* GetEventManager() = 0;
	virtual IRender* GetRenderer() = 0;
	virtual IEntityList* GetEntityList() = 0;
	virtual IGame* GetGame() = 0;
	virtual IDamage* GetDamage() = 0;
	virtual IPrediction* GetPrediction() = 0;
	virtual ITargetSelector* CreateTargetSelector() = 0;
	virtual IMenu* AddMenu(const char*) = 0;
	virtual IHealthPrediction* GetHealthPrediction() = 0;
	virtual ISpell* CreateSpell(eSpellSlot Slot, float Range = FLT_MAX) = 0;
	virtual bool ReadFileFromURL(std::string const& Url, std::string& Out) = 0;
	virtual void GetBaseDirectory(std::string& Out) = 0;
	virtual ISpell2* CreateSpell2(eSpellSlot Slot, eSpellType Type, bool IsMissile, bool IsAoE, int/*eCollisionFlags*/ CollisionFlags) = 0;
	virtual IInventoryItem* CreateItemForId(int ItemId, float Range) = 0;
	virtual ISpellData* GetSpellDataReader() = 0;
	virtual IBuffData* GetBuffDataReader() = 0;
	virtual IMissileData* GetMissileDataReader() = 0;
	virtual PVOID GetIDirect3DDevice9Pointer() = 0;
	virtual void DelayFunctionCall(int Milliseconds, std::function<void()> Callback) = 0;
	virtual void RegisterPluginInterface(std::string const& Name, PVOID Interface) = 0;
	virtual void UnRegisterPluginInterface(std::string const& Name) = 0;
	virtual PVOID FindPluginInterface(std::string const& Name) = 0;
	virtual INavMesh* GetNavMesh() = 0;
	virtual IUtility* GetUtility() = 0;
};

extern IPluginSDK*			GPluginSDK;
extern IEventManager*		GEventManager;
extern IRender*				GRender;
extern IEntityList*			GEntityList;
extern IGame*				GGame;
extern IDamage*				GDamage;
extern IPrediction*			GPrediction;
extern IHealthPrediction*	GHealthPrediction;
extern ITargetSelector*		GTargetSelector;
extern IOrbwalking*			GOrbwalking;
extern ISpellData* 			GSpellData;
extern IBuffData* 			GBuffData;
extern IMissileData* 		GMissileData;
extern INavMesh* 			GNavMesh;
extern IUtility*			GUtility;

#endif // PluginSDK_h__