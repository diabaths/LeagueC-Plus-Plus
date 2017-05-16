#ifndef LPPConstants_h__
#define LPPConstants_h__

enum eGameObjectClassId
{
	kNeutralMinionCamp = 0,
	kFollowerObject = 1,
	kFollowerObjectWithLerpMovement = 2,
	kAIHeroClient = 3,
	kobj_AI_Marker = 4,
	kobj_AI_Minion = 5,
	kLevelPropAI = 6,
	kobj_AI_Turret = 7,
	kobj_AI_Base = 8,
	kobj_GeneralParticleEmitter = 9,
	kMissileClient = 10,
	kDrawFX = 11,
	kUnrevealedTarget = 12,
	kobj_Barracks = 13,
	kobj_BarracksDampener = 14,
	kobj_Lake = 15,
	kobj_AnimatedBuilding = 16,
	kobj_Building = 17,
	kobj_Levelsizer = 18,
	kobj_NavPoint = 19,
	kobj_SpawnPoint = 20,
	kobj_LampBulb = 21,
	kGrassObject = 22,
	kobj_HQ = 23,
	kobj_InfoPoint = 24,
	kLevelPropGameObject = 25,
	kLevelPropSpawnerPoint = 26,
	kobj_Shop = 27,
	kobj_Turret = 18
};

enum eTeleportType
{
	Teleport_Teleport,
	Teleport_Recall,
	Teleport_Shen,
	Teleport_TwistedFate,
	Teleport_Unknown
};

enum eTeleportStatus
{
	Teleport_Start,
	Teleport_Abort,
	Teleport_Finish
};

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
	Ready = 0,		// 0 Spell is ready but should also be AND'd by UnableToCast for a full check
	NotReady = (1 << 1), // 2 (Unsure, spell is not ready)
	NotLearned = (1 << 2), // 4 (Spell has not been leveled yet)
	Supressed = (1 << 3), // 8 (You are being supressed)
	Unknown16 = (1 << 4), // 16 (Unsure, used in UnableToCast flags)
	Cooldown = (1 << 5), // 32 (Spell is on CD)
	NoMana = (1 << 6), // 64 (You do not have enough mana to cast the spell)
	Unknown128 = (1 << 7), // 128 (Unsure, used in UnableToCast flags)

	UnableToCast = (Unknown128 | Cooldown | NotLearned | NotReady) // if (Spell.Flags == 0 || !(Spell.Flags & UnableToCast)) { Spell.Ready = true; }
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
	kEventOnPauseAnimation,
	kEventOnJungleNotification,
	kEventOnNewPath,
	kEventOnTeleport,
	kEventOnStopCast,
	kEventOnBuffUpdateCount
};

enum eTargetPriority
{
	QuickestKill,				/* Prioritize the quickest kill based on damage type */
	ClosestPriority,			/* Prioritize based on distance */
	ClosestToCursorPriority,	/* Prioritize based on distance from cursor */
	LowestHealthPriority,		/* Prioritize based on lowest health */
	MostStacks,					/* Prioritizes based on most stacks (e.g Vayne W, Twitch passive, etc.) */
	MostAD,						/* Prioritizes based on highest AD */
	MostAP,						/* Prioritizes based on highest AP */
	LeastAttacks,				/* Prioritizes based on least number of physical damage attacks to kill */
	LeastCasts,					/* Prioritizes based on least number of spell cast attacks to kill */
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