#pragma once
#include <cstdint>
#include "AALib/Common/cmn_typedef.h"
#include "obj_scriptinc.h"

enum APFLG
{
	APFLG_MAIN_COMBO_RATE_IGNORE = 2,
	APFLG_GUARD_EFFECT_ECONOMY = 4,
	APFLG_KEEP_OUT_POWER = 8,
	APFLG_SHUT_UP = 16,
	APFLG_EFFECT_SLASH_DOUBLE_FIX = 32,
	APFLG_NO_HIT_GUARD = 64,
	APFLG_ENEMY_CELL_FIX = 128,
	APFLG_NO_SOUSAI = 256,
	APFLG_ARMOR_THROUGH = 512,
	APFLG_NEXT_HIT_ICHIGEKI_ONLY = 1024,
	APFLG_FATAL_COUNTER = 2048,
	APFLG_LOCK_KEEP = 4096,
	APFLG_WALL_BOUND_FIX = 8192,
	APFLG_AIR_NOKEZORI = 16384,
	APFLG_MULTI_COUNTERHIT = 32768,
	APFLG_HELL_FIRE = 65536,
	APFLG_DIRECTION_REVERSE = 131072,
	APFLG_GUARD_BREAK_EX = 262144,
	APFLG_TATE = 524288,
	APFLG_ANTIAIR = 1048576,
	APFLG_NO_HIT_THROW_RESIST = 2097152,
	APFLG_WALL_HARITSUKI_KUDARI_OK = 4194304,
	APFLG_GG_AUTO_PARAM = 8388608,
	APFLG_EASY_SOUSAI = 16777216,
	APFLG_SHORTHITSTOP = 33554432,
	APFLG_NOHITSTOP = 67108864,
	APFLG_NOSELFHITSTOP = 134217728,
	APFLG_NO_HIT_LOSE_BALANCE = 268435456,
	APFLG_WALLBOUND_FOR_DUST = 536870912,
	APFLG_WALLBOUND_FOR_DUST_1 = 1073741824,
	APFLG_NOENEMYHITSTOP = 0x80000000,
};
enum APFLG2
{
	APFLG2_DEAD_ANGLE = 1,
	APFLG2_MUTEKI_IGNORE = 2,
	APFLG2_LOCK_EXE = 4,
	APFLG2_NO_HOSEI_WEIGHT = 8,
	APFLG2_NO_HOSEI_STUN = 16,
	APFLG2_NO_HOSEI_HITBACK = 32,
	APFLG2_NO_HOSEI_DOWN_ZOKUSEI = 64,
	APFLG2_NO_HOSEI_DUST = 128,
	APFLG2_NO_HOSEI_DAMAGE = 256,
	APFLG2_NO_HOSEI_DOWN_ZOKUSEI_HUTTOBI = 512,
	APFLG2_NO_HOSEI_ATKVECTORY = 1024,
	APFLG2_NO_HOSEI_ATKVECTORX = 2048,
	APFLG2_REFRACT = 4096,
	APFLG2_BALLMOF = 8192,
	APFLG2_BALLMOF_FIRST = 16384,
	APFLG2_NO_EFFECT = 32768,
	APFLG2_HOSEI_TADAN = 65536,
	APFLG2_NO_HIT_NOT_KILL_COMBO = 131072,
	APFLG2_NO_HIT_COMBO = 262144,
	APFLG2_NO_HIT_DOWN_ZOKUSEI = 524288,
	APFLG2_BURST = 1048576,
	APFLG2_PLAYER_HIT_ONLY = 2097152,
	APFLG2_PUSH_OFF = 4194304,
	APFLG2_NAGE_OR_DAGEKI_IS_NAGE = 8388608,
	APFLG2_ENEMY_DAMAGE_TO_MUTEKI_FORCE = 16777216,
	APFLG2_POSITIVE_BONUS = 33554432,
	APFLG2_RISC_DECPER_OFF = 67108864,
	APFLG2_COMBO_FORCE_HIT = 134217728,
	APFLG2_MOM_ITEM = 268435456,
	APFLG2_BURST_BLUE = 536870912,
	APFLG2_SHUT_UP_DANMATSUMA = 1073741824,
	APFLG2_BLITZ_BREAK = 0x80000000,
};
enum APFLG3
{
	APFLG3_LOCK = 1,
	APFLG3_LOCK_REJECT = 2,
	APFLG3_ATK_FORCE_EXPAND = 4,
	APFLG3_IGNORE_BURST = 8,
	APFLG3_LAND_HIT_ONLY = 16,
	APFLG3_AIR_HIT_ONLY = 32,
	APFLG3_NO_HIT_CROUCH = 64,
	APFLG3_IGNORE_OUT_POWER = 128,
	APFLG3_IGNORE_CAUTION = 256,
	APFLG3_SLEEP_STUN_LAND_HIT_ONLY = 512,
	APFLG3_BOUND_KEEP_GRAVITY = 1024,
	APFLG3_EFFECT_STRIKE = 2048,
	APFLG3_EFFECT_SLASH = 4096,
	APFLG3_EFFECT_TSUKI = 8192,
	APFLG3_EFFECT_FIRE = 16384,
	APFLG3_EFFECT_ELECTRIC = 32768,
	APFLG3_EFFECT_ICE = 65536,
	APFLG3_EFFECT_SPECIAL = 131072,
	APFLG3_EFFECT_ONPA = 262144,
	APFLG3_EFFECT_ELECTRICDARK = 524288,
	APFLG3_ARMOR_BREAK = 1048576,
	APFLG3_NO_STAGGER_UI = 2097152,
	APFLG3_NO_FINISH_STOP = 4194304,
	APFLG3_NO_FINISH_CAMERA = 8388608,
	APFLG3_SOUSAI_ONLY = 16777216,
	APFLG3_SOUSAI_HITSTOP = 33554432,
	APFLG3_MULTI_HIT = 67108864,
	APFLG3_JITABATA_NO_RECOVER = 134217728,
	APFLG3_HELL_FIRE_DAMAGE_UP_DONE = 268435456,
	APFLG3_SLOW_HIT = 536870912,
	APFLG3_COMBO_COUNT_NO_ADD = 1073741824,
	APFLG3_HELL_FIRE_IGNORE_DEMO = 0x80000000,
};
enum APFLG4
{
	APFLG4_VECTOR_X_GENSUI = 1,
	APFLG4_NAGENUKE = 2,
	APFLG4_DUST_ATTACK = 4,
	APFLG4_DUST_ATTACK_SUPER = 8,
	APFLG4_CHIJOUTUUJOUNAGE_TSUKAMI = 16,
	APFLG4_KUUCHUUTUUJOUNAGE_TSUKAMI = 32,
	APFLG4_CHIJOUTUUJOUNAGE_EXE = 64,
	APFLG4_KUUCHUUTUUJOUNAGE_EXE = 128,
	APFLG4_DAMAGE_NOT_INITIALIZED = 256,
	APFLG4_BURST_ULTIMATE = 512,
	APFLG4_NEO_BLITZ = 1024,
	APFLG4_YOGORE = 2048,
	APFLG4_BLITZ_HAJIKI = 4096,
	APFLG4_Z_REVERSAL = 8192,
	APFLG4_MAIN_PLAYER_HIT_ONLY = 16384,
	APFLG4_SHOT_IGNORE_Z_REVERSAL = 32768,
	APFLG4_SUIKOMI = 65536,
	APFLG4_ENABLE_LAND_UKEMI = 131072,
	APFLG4_RUSHSOUSAI_JIZOKU_END = 262144,
	APFLG4_HITCOUNT_DOUBLE = 524288,
	APFLG4_EASY_GUARD_ATTACK = 1048576,
	APFLG4_FUTTOBI_FINISH = 2097152,
	APFLG4_DESTRUCTION_FINISH = 4194304,
	APFLG4_EFFECT_BEAM_SOUSAI = 8388608,
	APFLG4_IGNORE_SOUSAI_SAMELEVEL = 16777216,
	APFLG4_SEVERE_SOUSAI_CONDITION = 33554432,
	APFLG4_BOTH_MAIN_PLAYER_HIT_ONLY = 67108864,
	APFLG4_FORCE_CHANGE = 134217728,
	APFLG4_THROW_IN_NOKEZORI = 268435456,
	APFLG4_DOWN_TUIGEKI_AVAILABLE = 536870912,
	APFLG4_SOUSAI_AVAILABLE_ONLYCOMMAND = 1073741824,
	APFLG4_COMBO_FORCE_HIT_EX = 0x80000000,
};
enum APFLG5
{
	APFLG5_WORLDSIDE_BREAK = 1,
	APFLG5_WSB_WALL_STAMP = 2,
	APFLG5_WSB_WALL_STAMP_DAMAGE = 4,
	APFLG5_FLOAT_DMG_HEAD = 8,
	APFLG5_FLOAT_DMG_BODY = 16,
	APFLG5_NOKEZORI_BOTTOM = 32,
	APFLG5_SLOW_HITSTOP_ATTACK = 64,
	APFLG5_SLOW_HITSTOP_DAMAGE = 128,
	APFLG5_GUARD_LANDING_ACTION = 256,
	APFLG5_NOT_SHAKE_X_BY_ATTACK_ACTION = 512,
	APFLG5_TARGET_PLAYER_HIT_ONLY = 1024,
	APFLG5_WALLBOUND_VECTOR_PARAM_RESET = 2048,
	APFLG5_WSB_POINT_NOT_UPDATE = 4096,
	APFLG5_NOT_CAMERA_SHAKE_LOCK_ATK_ACT = 8192,
	APFLG5_NOT_EXTRA_GRAVITY = 16384,
	APFLG5_TADAN_HOSEI_TYPE_ATK_HISTORY = 32768,
	APFLG5_NO_PUNISH = 65536,
};
struct AtkShakeCameraParam
{
	CXXBYTE<32> patternName{}; // 0x0
	int32_t scale{}; // 0x20
	int32_t inFrame{}; // 0x24
	int32_t stayFrame{}; // 0x28
	int32_t outFrame{}; // 0x2C
	AtkShakeCameraParam() {}
};
enum AtkEasyGuardReadyFlg
{
	EASY_GUARD_NONE = 0,
	EASY_GUARD_READY_OK = 1,
	EASY_GUARD_READY_AIRONLY = 2,
	EASY_GUARD_READY_INVALID = 3,
};
class CAtkParam
{
public:
	CAtkParam() {}
	void CAtkParamInit();
	bool IsGedan();
	bool IsChudan();
	bool IsJodan();
	bool IsKuuGaHuka();
	bool IsShot();
	int32_t SolveAtkHitStopTime(GUARD_OR_HIT_OR_COUNTER, bool);
	bool IsTate();
	bool IsAtkHead();
	bool IsTensionAddOnlyEnemy();
	void SetTensionAddOnlyEnemy(bool);
	void AddAtkFlag(APFLG);
	void DelAtkFlag(APFLG);
	void OnOffAtkFlag(APFLG, bool);
	uint32_t CheckAtkFlag(APFLG);
	void AddAtkFlag2(APFLG2);
	void DelAtkFlag2(APFLG2);
	void OnOffAtkFlag2(APFLG2, bool);
	uint32_t CheckAtkFlag2(APFLG2);
	void AddAtkFlag3(APFLG3);
	void DelAtkFlag3(APFLG3);
	void OnOffAtkFlag3(APFLG3, bool);
	uint32_t CheckAtkFlag3(APFLG3);
	void AddAtkFlag4(APFLG4);
	void DelAtkFlag4(APFLG4);
	void OnOffAtkFlag4(APFLG4, bool);
	uint32_t CheckAtkFlag4(APFLG4);
	void AddAtkFlag5(APFLG5);
	void DelAtkFlag5(APFLG5);
	void OnOffAtkFlag5(APFLG5, bool);
	uint32_t CheckAtkFlag5(APFLG5);
	int32_t m_AtkType{}; // 0x0
	int32_t m_AtkLevel{}; // 0x4
	int32_t m_AtkLevelForSousai{}; // 0x8
	int32_t m_AtkDamage{}; // 0xC
	int32_t m_AtkFlag{}; // 0x10
	int32_t m_AtkFlag2{}; // 0x14
	int32_t m_AtkFlag3{}; // 0x18
	int32_t m_AtkFlag4{}; // 0x1C
	int32_t m_AtkFlag5{}; // 0x20
	int32_t m_AtkHitStopTimeEnemyAddition[3]{}; // 0x24
	int32_t m_AtkHitStopTime{}; // 0x30
	int32_t m_AtkLockWaitTime{}; // 0x34
	int32_t m_AtkGuardTime{}; // 0x38
	int32_t m_AtkAirGuardTimeAddition{}; // 0x3C
	int32_t m_AtkRangeMaxX{}; // 0x40
	int32_t m_AtkRangeMaxY{}; // 0x44
	int32_t m_AtkRangeMinX{}; // 0x48
	int32_t m_AtkRangeMinY{}; // 0x4C
	int32_t m_AtkPushRangeX{}; // 0x50
	CXXBYTE<32> m_AtkLockAction{}; // 0x54
	CXXBYTE<32> m_AtkDamageEffectName{}; // 0x74
	CXXBYTE<32> m_AtkGuardEffectName{}; // 0x94
	int32_t m_AtkBarrierDamageRate{}; // 0xB4
	int32_t m_AtkEffectScale{}; // 0xB8
	CXXBYTE<32> m_AtkNextHitActionName{}; // 0xBC
	int32_t m_AtkHitPositionX{}; // 0xDC
	int32_t m_AtkHitPositionY{}; // 0xE0
	int32_t m_AtkExHitParamAddVal{}; // 0xE4
	COperand m_AtkExHitParamOperand{}; // 0xE8
	int32_t m_AtkExHitParamMax{}; // 0xF0
	int32_t m_AtkExHitParamMin{}; // 0xF4
	int32_t m_AtkPoisonTime{}; // 0xF8
	int32_t m_AtkPoisonDamage{}; // 0xFC
	int32_t m_AtkLockRejectType{}; // 0x100
	int32_t m_AtkFixDamageRate{}; // 0x104
	int32_t m_AtkKizetsuDamage{}; // 0x108
	CXXBYTE<32> m_AtkGGThrowCell{}; // 0x10C
	int32_t m_AtkHitBack{}; // 0x12C
	int32_t m_AtkFDMinHitBack{}; // 0x130
	int32_t m_AtkHitBackGuardBreak{}; // 0x134
	int32_t m_AtkHitBackForHit{}; // 0x138
	int32_t m_AtkWallPushBack{}; // 0x13C
	int32_t m_AtkLandStunTimeCrouchAddition{}; // 0x140
	int32_t m_AtkAirStunTime_FromLandAddition{}; // 0x144
	int32_t m_AtkAngle{}; // 0x148
	int32_t m_AtkJitabataTime{}; // 0x14C
	int32_t m_AtkTensionGG{}; // 0x150
	CXXBYTE<32> m_AtkHitCommonSE{}; // 0x154
	CXXBYTE<32> m_AtkHitCommonSEAppend[3]{}; // 0x174
	CXXBYTE<32> m_AtkGuardCommonSE{}; // 0x1D4
	CXXBYTE<32> m_AtkGuardCommonSEAppend[3]{}; // 0x1F4
	int32_t m_AtkLevelForGuard{}; // 0x254
	int32_t m_AtkGuardBalance{}; // 0x258
	int32_t m_AtkHosei{}; // 0x25C
	int32_t m_AtkHoseiRateFirst{}; // 0x260
	int32_t m_AtkHoseiRateForce{}; // 0x264
	int32_t m_AtkHoseiFirst{}; // 0x268
	int32_t m_AtkHoseiOnece{}; // 0x26C
	int32_t m_AtkKezuriGG{}; // 0x270
	int32_t m_AtkKezuriRate{}; // 0x274
	int32_t m_AtkNoBurstTime{}; // 0x278
	int32_t m_AtkMutekiTime{}; // 0x27C
	int32_t m_AtkDustMutekiTime{}; // 0x280
	int32_t m_AtkDrain{}; // 0x284
	CXXBYTE<32> m_AtkTrialName{}; // 0x288
	CXXBYTE<32> m_AtkTrialDrawName{}; // 0x2A8
	int32_t m_AtkSuikomiPowerX{}; // 0x2C8
	int32_t m_AtkSuikomiPowerY{}; // 0x2CC
	int32_t m_AtkRecoverDamageRate{}; // 0x2D0
	int32_t m_AtkAdditionalHitCount{}; // 0x2D4
	int32_t m_AtkRushSousaiJizokuFrame{}; // 0x2D8
	int32_t m_ExplosionFinishActCountLimit{}; // 0x2DC
	int32_t m_AtkGuardBalanceHosei{}; // 0x2E0
	int32_t m_AtkFixBoundSpeed{}; // 0x2E4
	int32_t m_AtkHitBackAir{}; // 0x2E8
	int32_t m_AtkAirGuardVectorX{}; // 0x2EC
	int32_t m_AtkAirGuardVectorY{}; // 0x2F0
	int32_t m_AtkDmgActCount{}; // 0x2F4
	int32_t m_AtkDmgActCountFirst{}; // 0x2F8
	int32_t m_AtkGuardGravity{}; // 0x2FC
	int32_t m_AtkAngleGuardForce{}; // 0x300
	int32_t m_AtkHajikareTime{}; // 0x304
	int32_t m_AtkDmgActCountRateX{}; // 0x308
	int32_t m_AtkDmgActCountRateY{}; // 0x30C
	int32_t m_AtkFixBoundSpeed2{}; // 0x310
	int32_t m_AtkFixWallBoundSpeed{}; // 0x314
	int32_t m_AtkFixWallBoundSpeed2{}; // 0x318
	int32_t m_AtkConsiderVectorPerX{}; // 0x31C
	int32_t m_AtkConsiderVectorPerY{}; // 0x320
	int32_t m_AtkSameAttackNum{}; // 0x324
	int32_t m_AtkSameAttackGravity{}; // 0x328
	int32_t m_AtkPreGuardRangeDot{}; // 0x32C
	int32_t m_AtkPreGuardRangeDotY{}; // 0x330
	CXXBYTE<32> m_AtkWallBoundNextAction{}; // 0x334
	CXXBYTE<32> m_AtkLandBoundNextAction{}; // 0x354
	AtkShakeCameraParam m_ShakeCamera{}; // 0x374
	SKILL_CATEGORY m_AtkSkillCategory{}; // 0x3A4
	CHT_TYPE m_AtkCounterHitType{}; // 0x3A8
	HIT_EFFECT m_AtkDamageEffectType{}; // 0x3A9
	HIT_EFFECT m_AtkGuardEffectType{}; // 0x3AA
	ATK_FRONT m_AtkFrontDirection{}; // 0x3AB
	KILL_TYPE m_AtkKillType{}; // 0x3AC
	FINISH_BG m_AtkFinishBG{}; // 0x3AD
	HIT_POSITION_TYPE m_AtkHitPositionType{}; // 0x3AE
	CO_TYPE m_AtkExHitParamObjType{}; // 0x3AF
	ATKDAN m_AtkDan{}; // 0x3B0
	DMG_CELL m_AtkDamageCell{}; // 0x3B1
	EDT_TYPE m_AtkExDamageType{}; // 0x3B2
	POS_TYPE m_AtkSuikomiPos{}; // 0x3B3
	FACE_TYPE m_AtkDamageFace{}; // 0x3B4
	ESoundBank m_AtkHitSEBankId{}; // 0x3B5
	ESoundBank m_AtkGuardSEBankId{}; // 0x3B6
	EDestructionFinish m_AtkDestFinish{}; // 0x3B7
	EDestructionFinishEffect m_AtkDestFinishEffect{}; // 0x3B8
	AtkEasyGuardReadyFlg m_AtkEasyGuardReady{}; // 0x3B9
	CHT_PROCESS m_AtkCounterHitProcess{}; // 0x3BA
	char m_AtkShotLevel{}; // 0x3BB
	unsigned char m_AtkEffectLimit{}; // 0x3BC
	unsigned char m_AtkExHitParamFlag{}; // 0x3BD
	OBJ_CBase * m_AtkTargetObj{}; // 0x3C0
	CXXBYTE<32> m_AtkDamageCellEx{}; // 0x3C8
	unsigned char m_AtkDamageMouthType{}; // 0x3E8
	unsigned char m_AtkHead{}; // 0x3E9
	unsigned char m_AtkDownTuigekiAvailable{}; // 0x3EA
	unsigned char m_AtkTensionAddOnlyEnemy{}; // 0x3EB
	unsigned char m_AtkGuardCancel{}; // 0x3EC
	unsigned char m_AtkBlowOffGravityIsZero{}; // 0x3ED
	unsigned char m_AtkHitOnceInCombo{}; // 0x3EE
	unsigned char m_AtkHitNoTensionSelfDamage{}; // 0x3EF
	unsigned char m_AtkSuikomiBasePos{}; // 0x3F0
	unsigned char m_AtkDamageToRecovery{}; // 0x3F1
	unsigned char m_AtkInitialLeft{}; // 0x3F2
	unsigned char m_AtkSubObjectSousai{}; // 0x3F3
	bool m_bAtkHitBankSEFromSet{}; // 0x3F4
	bool m_bAtkHitBankSEOverwrite{}; // 0x3F5
	bool m_bAtkGuardBankSEFromSet{}; // 0x3F6
	bool m_bAtkGuardBankSEOverwrite{}; // 0x3F7
	int32_t CalcAtkDamage(int32_t, uint32_t, const OBJ_CBase *);
	int32_t CalcAtkHitStopTime(int32_t, uint32_t);
	int32_t CalcAtkGuardTime(int32_t, uint32_t);
	int32_t CalcAtkAirGuardTimeAddition(int32_t, uint32_t);
	int32_t CalcAtkBarrierDamageRate(int32_t, uint32_t);
	int32_t CalcAtkLandStunTimeCrouchAddition(int32_t, uint32_t);
	int32_t CalcAtkRecoverDamageRate(int32_t, uint32_t);
	int32_t CalcAtkRushSousaiJizokuFrame(uint32_t);
};

struct AtkTimeCtrlParam
{
	int32_t startTime{}; // 0x0
	int32_t endTime{}; // 0x4
	int32_t value1{}; // 0x8
	void Init();
	bool IsSet();
};
class CAtkParamEx
{
public:
	CAtkParamEx() {}
	void CAtkParamExInit();
	void CAtkParamExBunanInit();
	int32_t m_AtkVectorX{}; // 0x0
	int32_t m_AtkVectorY{}; // 0x4
	int32_t m_AtkGravity{}; // 0x8
	int32_t m_AtkWallBoundRate{}; // 0xC
	int32_t m_AtkLandBoundRate{}; // 0x10
	int32_t m_AtkLandStunTime{}; // 0x14
	int32_t m_AtkAirStunTime{}; // 0x18
	int32_t m_AtkWallBoundCount{}; // 0x1C
	int32_t m_AtkLandBoundCount{}; // 0x20
	int32_t m_AtkSleepStunTime{}; // 0x24
	int32_t m_AtkLandHitAction{}; // 0x28
	int32_t m_AtkAirHitAction{}; // 0x2C
	int32_t m_AtkWallHaritsukiTime{}; // 0x30
	int32_t m_AtkWallBoundWorldOnly{}; // 0x34
	int32_t m_AtkKorogariTime{}; // 0x38
	int32_t m_AtkSlideDownTime{}; // 0x3C
	int32_t m_AtkWallBoundWaitTime{}; // 0x40
	int32_t m_AtkKorogariUnlimited{}; // 0x44
	int32_t m_AtkQuickDownFlag{}; // 0x48
	int32_t m_AtkWSBPoint{}; // 0x4C
	int32_t m_AtkIgnoreWSB{}; // 0x50
	int32_t m_AtkWSBBlowOffType{}; // 0x54
	int32_t m_AtkWSBLimitTime{}; // 0x58
	int32_t m_AtkFinishStopTime{}; // 0x5C
	int32_t m_AtkSlashUITime{}; // 0x60
	int32_t m_AtkWallBoundGravity{}; // 0x64
	int32_t m_AtkLandBoundGravity{}; // 0x68
	int32_t m_AtkWallBoundStunTime{}; // 0x6C
	int32_t m_AtkLandBoundStunTime{}; // 0x70
	int32_t m_AtkWallBoundStunTimeAddition{}; // 0x74
	int32_t m_AtkLandBoundStunTimeAddition{}; // 0x78
	int32_t m_AtkWallBoundRateY{}; // 0x7C
	int32_t m_AtkLandBoundRateX{}; // 0x80
	int32_t m_AtkFuwafuwaDown{}; // 0x84
	AtkTimeCtrlParam m_AtkVectorXPer{}; // 0x88
	AtkTimeCtrlParam m_AtkVectorYPer{}; // 0x94
	AtkTimeCtrlParam m_AtkGravityAdd{}; // 0xA0
	int32_t m_AtkBlowOffLabel{}; // 0xAC
	int32_t m_AtkBomberRate{}; // 0xB0
	int32_t m_AtkRedRCTime{}; // 0xB4
	bool CheckWSBLimitTime();
	int32_t CalcAtkVectorX(uint32_t, CAtkParam *, CAtkParamEx *, int32_t);
	int32_t CalcAtkVectorY(uint32_t, CAtkParam *, CAtkParamEx *, int32_t);
	int32_t CalcAtkGravity(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkWallBoundRate(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkLandBoundRate(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkLandStunTime(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkAirStunTime(uint32_t, CAtkParam *, CAtkParamEx *, int32_t);
	int32_t CalcAtkWallBoundCount(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkLandBoundCount(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkSleepStunTime(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkLandHitAction(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkAirHitAction(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkWallHaritsukiTime(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkWallBoundWorldOnly(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkKorogariTime(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkWallBoundWaitTime(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkKorogariUnlimited(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkSlideDownTime(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkQuickDownFlag(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkWSBPoint(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkIgnoreWSB(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkWSBBlowOffType(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkWSBLimitTime(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkFinishStopTime(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkSlashUITime(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkWallBoundGravity(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkLandBoundGravity(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkWallBoundStunTime(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkLandBoundStunTime(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkWallBoundStunTimeAddition(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkLandBoundStunTimeAddition(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkFuwafuwaDown(uint32_t, CAtkParam *, CAtkParamEx *);
	void CalcAtkVectorXPer(uint32_t, CAtkParamEx *, CAtkParamEx *);
	void CalcAtkVectorYPer(uint32_t, CAtkParamEx *, CAtkParamEx *);
	void CalcAtkGravityAdd(uint32_t, CAtkParamEx *, CAtkParamEx *);
	int32_t CalcAtkBlowOffLabel(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkBomberRate(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkRedRCTime(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkWallBoundRateY(uint32_t, CAtkParam *, CAtkParamEx *);
	int32_t CalcAtkLandBoundRateX(uint32_t, CAtkParam *, CAtkParamEx *);
};