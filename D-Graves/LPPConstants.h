#ifndef LPPConstants_h__
#define LPPConstants_h__

enum eDamageItems
{
	kHexgun,
	kDfg,
	kBotrk,
	kBilgewater,
	kTiamat,
	kHydra,
	kBlackFireTorch,
	kOdingVeils,
	kFrostQueenClaim,
	kLiandrysTorment,
};

enum eSummonerSpell
{
	kSummonerSpellIgnite,
	kSummonerSpellSmite
};

enum eSpellSlot
{
	kSlotQ,
	kSlotW,
	kSlotE,
	kSlotR,
	kSummonerSlot1,
	kSummonerSlot2,
	kItem1,
	kItem2,
	kItem3,
	kItem4,
	kItem5,
	kItem6,
	kSlotTrinket,
	kSlotRecall,
	kSlotUnknown = -1
};

enum eBuffType
{
	BUFF_Internal,
	BUFF_Aura,
	BUFF_CombatEnchancer,
	BUFF_CombatDehancer,
	BUFF_SpellShield,
	BUFF_Stun,
	BUFF_Invisibility,
	BUFF_Silence,
	BUFF_Taunt,
	BUFF_Polymorph,
	BUFF_Slow,
	BUFF_Snare,
	BUFF_Damage,
	BUFF_Heal,
	BUFF_Haste,
	BUFF_SpellImmunity,
	BUFF_PhysicalImmunity,
	BUFF_Invulnerability,
	BUFF_Sleep,
	BUFF_NearSight,
	BUFF_Frenzy,
	BUFF_Fear,
	BUFF_Charm,
	BUFF_Poison,
	BUFF_Suppression,
	BUFF_Blind,
	BUFF_Counter,
	BUFF_Shred,
	BUFF_Flee,
	BUFF_Knockup,
	BUFF_Knockback,
	BUFF_Disarm
};

enum GameObjectCharacterState
{
	State_CanAttack = (1 << 0),
	State_CanCast = (1 << 1),
	State_CanMove = (1 << 2),
	State_Immovable = (1 << 5),
	State_RevealSpecificUnit = (1 << 6),
	State_Taunted = (1 << 7),
	State_Feared = (1 << 8),
	State_Fleeing = (1 << 9),
	State_Supressed = (1 << 10),
	State_Asleep = (1 << 11),
	State_NearSight = (1 << 12),
	State_Ghosted = (1 << 13),
	State_GhostProof = (1 << 14),
	State_Charmed = (1 << 15)
};

enum eSpellState
{
	Ready = 0,
	NotLearned = (1 << 2),
	DisabledOne = (1 << 3),
	DisabledTwo = (1 << 4),
	Cooldown = (1 << 5),
	NoMana = (1 << 6),
};

enum eUnitTeam
{
	kNeutral = 44,
	kTeam1 = 100,
	kTeam2 = 200
};

enum eUnitType
{
	FL_INVALID = 0,
	FL_CREEP = 12,
	FL_HERO = 20,
	FL_TURRET = 36,
	FL_MISSILE = 128
};

enum eGameObjectOrder
{
	kHoldPosition = 1,
	kMoveTo = 2,
	kAttackUnit = 3,
	kAutoAttackPet = 4,
	kAutoAttack = 5,
	kMovePet = 6,
	kAttackTo = 7,
	kStop = 10
};

enum eSpellType
{
	kTargetCast,
	kLineCast,
	kCircleCast,
	kConeCast
};

enum eHealthPredictionType
{
	kLastHitPrediction,
	kLaneClearPrediction
};

enum eMeshType
{
	kStaticMesh = 0,
	kGrassMesh = (1 << 0),
	kWallMesh = (1 << 1),
	kBuildingMesh = (1 << 6),
	kPropMesh = (1 << 7),
};

enum eLeagueEvents
{
	kEventOrbwalkBeforeAttack,
	kEventOrbwalkOnAttack,
	kEventOrbwalkAfterAttack,
	kEventOrbwalkTargetChange,
	kEventOrbwalkNonKillableMinion,
	kEventOnGameUpdate,
	kEventOnRender,
	kEventOnSpellCast,
	kEventOnUnitDeath,
	kEventOnCreateObject,
	kEventOnDestroyObject,
	kEventOnDoCast,
	kEventOnInterruptible,
	kEventOnGapCloser,
	kEventOnIssueOrder,
	kEventOnBuffAdd,
	kEventOnBuffRemove,
	kEventOnGameEnd,
	kEventOnLevelUp,
	kEventOnPreCast,
	kEventOrbwalkFindTarget,
	kEventOnDash,
	kEventOnD3DPresent,
	kEventOnD3DPreReset,
	kEventOnD3DPostReset,
	kEventOnRenderBehindHud,
	kEventOnWndProc,
	kEventOnEnterVisible,
	kEventOnExitVisible,
	kEventOnUpdateChargedSpell,
	kEventOnPlayAnimation,
	kEventOnPauseAnimation
};

enum eTargetPriority
{
	QuickestKill,				/* Prioritize the quickest kill based on damage type */
	ClosestPriority,			/* Prioritize based on distance */
	ClosestToCursorPriority,	/* Prioritize based on distance from cursor */
	LowestHealthPriority		/* Prioritize based on lowest health */
};

enum eDamageType
{
	TrueDamage,
	PhysicalDamage,
	SpellDamage
};

enum eInterruptibleDanger
{
	kLowDanger,
	kMediumDanger,
	kHighDanger
};

enum eObjectTeam
{
	kTeamUnknown = 0,
	kTeamOrder = 100,
	kTeamChaos = 200,
	kTeamNeutral = 300,
};

enum eFontWeight
{
	kFontWeightThin,
	kFontWeightNormal,
	kFontWeightBold,
	kFontWeightHeavy
};

enum eFontLocation
{
	kFontLocationNormal,
	kFontLocationCenterVertical,
	kFontLocationCenterHorizontal,
	kFontLocationCenter
};

enum eCollisionFlags
{
	kCollidesWithNothing = 0,
	kCollidesWithMinions = (1 << 1),	// Spell collides with enemy minions
	kCollidesWithHeroes = (1 << 2),		// Spell collides with enemy champions
	kCollidesWithYasuoWall = (1 << 3),	// Spell collides with Yasuo wall
	kCollidesWithWalls = (1 << 4),		// Spell collides with walls
	kCollidesWithAllies = (1 << 5)		// Spell collides with ally champions
};

enum eOrbwalkingMode
{
	kModeLastHit,
	kModeMixed,
	kModeLaneClear,
	kModeCombo,
	kModeFreeze,
	kModeCustom,
	kModeNone
};

enum eGameUnitClass
{
	kClassUnknown,
	kNeutralMinionCamp,
	kObj_AI_Base,
	kFollowerObject,
	kFollowerObjectWithLerpMovement,
	kObj_AI_Hero,
	kObj_AI_Marker,
	kObj_AI_Minion,
	kLevelPropAI,
	kObj_AI_Turret,
	kObj_GeneralParticleEmitter,
	kObj_SpellChainMissile,
	kObj_SpellCircleMissile,
	kObj_SpellLineMissile,
	kObj_SpellMissile,
	kMissile,
	kMissileClient,
	kDrawFX,
	kUnrevealedTarget,
	kObj_LampBulb,
	kObj_Barracks,
	kObj_BarracksDampener,
	kObj_AnimatedBuilding,
	kObj_Building,
	kObj_Levelsizer,
	kObj_NavPoint,
	kObj_SpawnPoint,
	kObj_Lake,
	kObj_HQ,
	kObj_InfoPoint,
	kLevelPropGameObject,
	kLevelPropSpawnerPoint,
	kObj_Shop,
	kObj_Turret,
	kGrassObject
};

enum ePingCategory
{
	kPingNormal = 0,
	kPingDanger = 2,
	kPingEnemyMissing = 3,
	kPingOnMyWay = 4,
	kPingFallback = 5,
	kPingAssistMe = 6
};

enum eGameType
{
	kGameNormal,
	kGameDominion,
	kGameTutorial,
	kGameARAM,
	kGameFirstBlood,
	kGameAscension,
};

enum eMapType
{
	kMapCrystalScar = 8,
	kMapTwistedTreeline = 10,
	kMapSummonersRift = 11,
	kMapHowlingAbyss = 12,
};

enum eTaunt
{
	kDance,
	kTaunt,
	kLaugh,
	kJoke,
	kToggle,
};

#endif // LPPConstants_h__