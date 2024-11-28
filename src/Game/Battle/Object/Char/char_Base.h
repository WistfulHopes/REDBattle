#pragma once
#include <Game/Battle/Object/obj_base.h>
#include "char_ActFlag.h"
#include "Game/Battle/Object/obj_AttackParam.h"

enum SKILL_FLAG
{
    SKLFLG_HITSTOP_CANCEL = 1,
    SKLFLG_CHAIN_ONLY = 2,
    SKLFLG_NO_CANCEL_ONLY = 4,
    SKLFLG_CPU_AVAILABLE = 8,
    SKLFLG_HUM_AVAILABLE = 16,
    SKLFLG_RECIPE = 32,
    SKLFLG_6 = 64,
    SKLFLG_NOT_SAME = 128,
    SKLFLG_INP_DIR_RIGHT = 256,
    SKLFLG_AIR_DASH_KEEP = 512,
    SKLFLG_TRIAL_ONLY = 1024,
    SKLFLG_ETC_LEVER_MOVE_JUMP_SEAL = 2048,
    SKLFLG_TRIAL_ONLY_EX = 4096,
    SKLFLG_STYLISH = 8192,
    SKLFLG_STYLISH_COMBO_SLOT = 16384,
    SKLFLG_STYLISH_ONE_BUTTON = 32768,
    SKLFLG_STYLISH_BEGIN_CANCEL = 65536,
    SKLFLG_NO_JUMP_CANCEL_CANCEL = 131072,
    SKLFLG_AIR_DASH_FINISH = 262144,
    SKLFLG_RECIPE_MUST_DAMAGE = 536870912,
    SKLFLG_RECIPE_MUST_DAMAGE_OR_GUARD = 1073741824,
    SKLFLG_RECIPE_MUST_DIRECTION = -2147483648,
};

enum SKLEST : uint32_t
{
    SKLEST_Guard = 1,
    SKLEST_Combo = 2,
    SKLEST_Panashi = 4,
    SKLEST_XNearPanashi = 8,
    SKLEST_XFarPanashi = 16,
    SKLEST_XMidPanashi = 32,
    SKLEST_Kiten = 64,
    SKLEST_Chudan = 128,
    SKLEST_Gedan = 256,
    SKLEST_Nage = 512,
    SKLEST_Taiku = 1024,
    SKLEST_UseResource = 2048,
    SKLEST_BigDamage = 4096,
    SKLEST_Kugurare = 8192,
    SKLEST_Kuguri = 16384,
    SKLEST_Tobare = 32768,
    SKLEST_Tobi = 65536,
    SKLEST_Muteki = 131072,
    SKLEST_ShotMuteki = 262144,
    SKLEST_Shot = 524288,
    SKLEST_Sukidarake = 1048576,
    SKLEST_KuNage = 2097152,
    SKLEST_Gamenhashi = 4194304,
    SKLEST_FromDash = 8388608,
    SKLEST_NoCombo = 16777216,
    SKLEST_NoAirCombo = 33554432,
    SKLEST_MOMBoss = 67108864,
    SKLEST_DoNotEstimate = 134217728,
    SKLEST_BonusRecipe = 268435456,
    SKLEST_BerserkRecipe = 536870912,
    SKLEST_OnHighEstimationOnly = 1073741824,
    SKLEST_Namepu = 0x80000000,
};

enum SKILL_ACTIVE_FLAG
{
    SAF_CHAIN = 1,
    SAF_FLEX_CHAIN = 16,
    SAF_PD_CHAIN = 32,
    SAF_CONDITION_READY = 64,
    SAF_REQUESTED = 128,
    SAF_LOW_ESTIMATION = 256,
    SAF_ARENDA_CHAIN = 512,
    SAF_ARENDA_FLEX_CHAIN = 1024,
    SAF_ARENDA_CHAIN_PD = 2048,
    SAF_BRENDA_CHAIN = 4096,
    SAF_BRENDA_FLEX_CHAIN = 8192,
    SAF_BRENDA_CHAIN_PD = 16384,
    SAF_CRENDA_CHAIN = 32768,
    SAF_CRENDA_FLEX_CHAIN = 65536,
    SAF_CRENDA_CHAIN_PD = 131072,
    SAF_REQUEST_RESERVE = -2147483648,
};

enum SKILL_CND_RET
{
    SCC_FALSE = 0,
    SCC_CHAIN = 1,
    SCC_DIRECT_INPUT = 2,
    SCC_SOUSAI = 3,
    SCC_BEGIN_CANCEL = 4,
    SCC_ARENDA_CHAIN = 5,
    SCC_BRENDA_CHAIN = 6,
    SCC_CRENDA_CHAIN = 7,
};

enum SKILL_RENDASMASH_INPUT_TYPE
{
    SRS_INPUT_NONE = 0,
    SRS_INPUT_NORMAL = 1,
    SRS_INPUT_NORMAL_RENDA = 2,
    SRS_INPUT_RENDA = 3,
};

class CSkillInfo
{
public:
    CSkillInfo();
    CXXBYTE<32> m_SkillName{}; // 0x0
    CXXBYTE<32> m_SkillNameCopyFrom{}; // 0x20
    CXXBYTE<32> m_ReqActName{}; // 0x40
    uint32_t m_ReqActFlag{}; // 0x60
    uint32_t m_SkillFlag{}; // 0x64
    uint32_t m_SkillEst{}; // 0x68
    INPUT_ID m_SkillInputList[16]{}; // 0x6C
    CXXBYTE<32> m_RecipeFirstSkillName{}; // 0xAC
    int32_t m_RecipeStopFrame{}; // 0xCC
    int32_t m_RecipeDataBufferStartIndex{}; // 0xD0
    int32_t m_RecipeDataBufferUseNum{}; // 0xD4
    int32_t m_AtkBoxX{}; // 0xD8
    int32_t m_AtkBoxY{}; // 0xDC
    int32_t m_AtkBoxW{}; // 0xE0
    int32_t m_AtkBoxH{}; // 0xE4
    CXXBYTE<32> m_ChainCountGroup{}; // 0xE8
    int32_t m_EnemyHitPointRate{}; // 0x108
    CXXBYTE<32> m_FuncName{}; // 0x10C
    CXXBYTE<32> m_ConditionCheckFunc{}; // 0x12C
    int32_t m_SkillHeightLimit{}; // 0x14C
    int32_t m_SkillEnemyXNear{}; // 0x150
    int32_t m_SkillEnemyYRangeMin{}; // 0x154
    int32_t m_SkillEnemyYRangeMax{}; // 0x158
    uint32_t m_SkillForceDisableFlag{}; // 0x15C
    int32_t m_BasePoint{}; // 0x160
    int32_t m_LevelLimit{}; // 0x164
    int32_t m_IntervalBase{}; // 0x168
    int32_t m_SkillFunctionGroup{}; // 0x16C
    int32_t m_SkillFunctionPriority{}; // 0x170
    int32_t m_RBMemcpyBegin{}; // 0x174
    BitArrayRED<129, CD_CONDITION> m_ConditionBitArray{}; // 0x178
    int32_t m_IntervalCountDown{}; // 0x18C
    int32_t m_TsubusareCnt{}; // 0x190
    int32_t m_IntervalMini{}; // 0x194
    int32_t m_IntervalEx{}; // 0x198
    int32_t m_ChusenMoreTimer{}; // 0x19C
    int32_t m_ChusenMorePer{}; // 0x1A0
    int32_t m_NewCPUPoint{}; // 0x1A4
    int32_t m_NewCPUPointRand{}; // 0x1A8
    uint32_t m_SkillActiveFlag{}; // 0x1AC
    int32_t m_SkillLastInputTimer[2]{}; // 0x1B0
    int32_t m_SkillLastInputTimerStop[2]{}; // 0x1B8
    int32_t m_SkillSenkoInputTime{}; // 0x1C0
    int32_t m_ScriptEstimateValue{}; // 0x1C4
    int32_t m_RendaSmashLastInputTimer[3]{}; // 0x1C8
    int32_t m_RendaSmashLastInputTimerStop[3]{}; // 0x1D4
    bool m_OneButtonSkill{}; // 0x1E0
    bool m_NormalInputSuccess{}; // 0x1E1
    bool m_AlternativeInput{}; // 0x1E2
    bool m_CancelDoing{}; // 0x1E3
    bool m_BeginCancelReq{}; // 0x1E4
    bool m_RomanCancelSpecialCancelReq{}; // 0x1E5
    short m_SkillSelfIndex{}; // 0x1E6
    short m_SkillSelfIndexStylishComboSlotBaseSkill{}; // 0x1E8
    SKILL_CATEGORY m_SkillCategory{}; // 0x1EA
    SKILL_SUB_CATEGORY m_SkillSubCategory{}; // 0x1EB
    SKILL_STANCE m_SkillStance{}; // 0x1EC
    CO_TYPE m_SkillInputDirectionBaseObject{}; // 0x1ED
    SRSF_TYPE m_RecipeStopFrameType{}; // 0x1EE
    SRSFN_TYPE m_RecipeStopFrameTypeN{}; // 0x1EF
    SKLDG m_SkillDG{}; // 0x1F0
    CPUTsuyosa m_TsuyosaLimit{}; // 0x1F1
    unsigned char m_SkillPriority{}; // 0x1F2
    char m_ChainCountMax{}; // 0x1F3
    char m_ChainCount{}; // 0x1F4
    SKILL_CND_RET m_SkillCondition_Chain{}; // 0x1F5
    SKILL_CND_RET m_SkillCondition_ChainPreAct{}; // 0x1F6
    bool m_SkillCondition_Other{}; // 0x1F7
    bool m_SkillCondition_OtherPreAct{}; // 0x1F8
    SKILL_RENDASMASH_INPUT_TYPE m_RendaSmashInputType{}; // 0x1F9
    int32_t m_RBMemcpyEnd{}; // 0x1FC
    void AddSkillEst(SKLEST);
    void DelSkillEst(SKLEST);
    bool CheckSkillEst(SKLEST);
    void CSkillInfoStaticDataInit();
    void CSkillInfoVolatileDataInit();
    void CSkillInfoInit();
    const unsigned long long GetRBMemcpySize();
    void* GetRBMemcpyBegin();
};

enum RPINP : int32_t
{
	RPINP_NON = 0,
	RPINP_KEY = 1,
	RPINP_SKILL = 2,
	RPINP_WAIT = 3,
};

struct sRecipeInputKey
{
	RPINP m_Type; // 0x0
	unsigned short m_RecFlg; // 0x4
	unsigned short m_Time; // 0x6
};
struct sRecipeInputSkill
{
	RPINP m_Type; // 0x0
	CXXBYTE<32> m_SkillNameRE; // 0x4
	sRecipeInputSkill();
};
struct sRecipeWaitType
{
	RPINP m_Type; // 0x0
	SRW_TYPE m_SRWType; // 0x4
	int32_t m_Time; // 0x8
};

class CSkillInfoList
{
public:
	CSkillInfoList();
	void CSkillInfoListInit();
	enum
	{
		SKILL_INFO_NUM = 180,
	};
	CSkillInfo m_SkillInfo[180]; // 0x0
	int32_t m_RBMemcpyBegin; // 0x16800
	int32_t m_SkillRegisterIndexList[180]; // 0x16804
	int32_t m_SkillRegisterNum; // 0x16AD4
	unsigned char m_RecipeDataBuffer[8000]; // 0x16AD8
	uint32_t m_RecipeDataBufferTotal; // 0x18A18
	int32_t m_SkillInfoCount; // 0x18A1C
	int32_t m_SkillSettingID; // 0x18A20
	int32_t m_RBMemcpyEnd; // 0x18A24
	AA_EasyHash<CXXBYTE<32>,200,800> m_SkillNameMap; // 0x18A28
	CSkillInfo * GetCurSettingSkillInfo();
	CSkillInfo * GetSkillInfo(int32_t);
	const unsigned long long GetRBMemcpySize();
	const unsigned long long GetRBTotalMemcpySize();
	const void * GetRBMemcpyBegin();
	void SaveRollbackParam(void *, const unsigned long long);
	void LoadRollbackParam(const void *, const unsigned long long);
};

enum GUARD_DAN
{
    GUARD_DAN_NON = 0,
    GUARD_DAN_AIR = 1,
    GUARD_DAN_STAND = 2,
    GUARD_DAN_CROUCH = 3,
};

enum SBRS_STATE
{
    SBRS_DEFAULT = 0,
    SBRS_REQ = 1,
    SBRS_DONE = 2,
    SBRS_END = 3,
};

enum RCELMFLG
{
    RCELMFLG_HIT = 1,
    RCELMFLG_GUARD = 4,
};

class CCPUInfo
{
public:
	CCPUInfo();
	void CCPUInfoReset();
	int32_t m_LastInitializedLevel; // 0x0
	int32_t m_Level; // 0x4
	int32_t m_LastInitializedGuardLevelBonus; // 0x8
	float m_LevelF01; // 0xC
	float m_LevelF01Katayori; // 0x10
	CSkillInfo * m_PlayingSkill; // 0x18
	const CSkillInfo * m_PlayingSkillLastForDisp; // 0x20
	int32_t m_RecipeStopTypeForDebug; // 0x28
	int32_t m_RecipePlayElmTimer; // 0x2C
	int32_t m_RecipePlayElmTimerWithStop; // 0x30
	uint32_t m_RecipePlayElmFlag; // 0x34
	int32_t m_RecipePlayingTime; // 0x38
	int32_t m_RecipePlayingTimeWithStop; // 0x3C
	int32_t m_RecipeLandNeutralTime; // 0x40
	int32_t m_RecipePlayIndex; // 0x44
	sRecipeInputKey * m_RecipeElmCurPtr; // 0x48
	int32_t m_RecipePlayElmDone; // 0x50
	CSkillInfo * m_SkillByRecipe; // 0x58
	int32_t m_RecipePlayElmCount; // 0x60
	int32_t m_KeyDirection; // 0x64
	unsigned short m_KeyFlagReg; // 0x68
	int32_t m_InputWait; // 0x6C
	int32_t m_DefGuard; // 0x70
	int32_t m_DefSwitchGuard; // 0x74
	int32_t m_DefJustGuard; // 0x78
	int32_t m_DefBarrierGuard; // 0x7C
	int32_t m_RangeGuard; // 0x80
	int32_t m_RangeSwitchGuard; // 0x84
	int32_t m_RangeJustGuard; // 0x88
	int32_t m_RangeBarrierGuard; // 0x8C
	int32_t m_FDKeizoku; // 0x90
	int32_t m_GuardShitaiTime; // 0x94
	int32_t m_GuardReversalTime; // 0x98
	int32_t m_Guard; // 0x9C
	int32_t m_SwitchGuard; // 0xA0
	int32_t m_JustGuard; // 0xA4
	int32_t m_BarrierGuard; // 0xA8
	int32_t m_BarrierGuardSub; // 0xAC
	int32_t m_Ukemi; // 0xB0
	int32_t m_LockReject; // 0xB4
	int32_t m_NCHandanWait; // 0xB8
	CCmnRect m_DlEnemyCollision; // 0xBC
	int32_t m_DlEnemyPosX; // 0xCC
	int32_t m_DlEnemyPosY; // 0xD0
	int32_t m_DlKuguriChikuseki; // 0xD4
	int32_t m_DlKuguriSaikin; // 0xD8
	int32_t m_DlShotChikuseki; // 0xDC
	int32_t m_DlShotSaikin; // 0xE0
	int32_t m_DlTobiChikuseki; // 0xE4
	int32_t m_DlTobiSaikin; // 0xE8
	int32_t m_DlSukidarakeSaikin; // 0xEC
	int32_t m_DlEnemyCrouchTimer; // 0xF0
	int32_t m_DlEnemyNoAttackTimer; // 0xF4
	int32_t m_DlReversalTimer; // 0xF8
	int32_t m_DlStress; // 0xFC
	int32_t m_DlNageReady; // 0x100
	CSkillInfo * m_DlEnemyLastUseSkill; // 0x108
	CSkillInfo * m_DlEnemyLastDelayUpdateSkill; // 0x110
	CPUTsuyosa m_CPUTsuyosa; // 0x118
	RPINP m_RecipePlayStructType; // 0x119
	SBRS_STATE m_SkillByRecipeState; // 0x11A
	bool m_isRecipePlaying; // 0x11B
	GUARD_DAN m_PrevGuardDan; // 0x11C
	bool m_NCNowHandan; // 0x11D
	bool m_DlEnemyDamage; // 0x11E
	bool m_DlEnemyGuard; // 0x11F
	bool m_DlEnemyAttacking; // 0x120
	GUARD_DAN m_DlEnemyGuardDan; // 0x121
};

enum ADAT_TYPE : int32_t
{
	ADAT_UNKNOWN = 0,
	ADAT_FRONT = 1,
	ADAT_BACK = 2,
	ADAT_VERT = 3,
	ADAT_WALLBOUND = 4,
};

enum RCCOLOR : int32_t
{
	RCCOLOR_R = 0,
	RCCOLOR_Y = 1,
	RCCOLOR_V = 2,
	RCCOLOR_INVALID = 3,
};

enum MOVE_X_USAGE : int32_t
{
	MOVE_X_USAGE_ETC = 0,
	MOVE_X_USAGE_FWALK = 1,
	MOVE_X_USAGE_BWALK = 2,
	MOVE_X_USAGE_FDASH = 3,
	MOVE_X_USAGE_BDASH = 4,
	MOVE_X_USAGE_FAIRDASH = 5,
	MOVE_X_USAGE_BAIRDASH = 6,
	MOVE_X_USAGE_FJUMP = 7,
	MOVE_X_USAGE_BJUMP = 8,
};

enum : int32_t
{
	FINISH_INPUT_NONE = 0,
	FINISH_INPUT_CHANGE1 = 1,
	FINISH_INPUT_CHANGE2 = 2,
};

struct AuraEffectInfo
{
	int32_t m_scaleX; // 0x0
	int32_t m_scaleY; // 0x4
	int32_t m_scaleZ; // 0x8
	CXXBYTE<32> m_name; // 0xC
	AuraEffectInfo();
};

enum POS_BODY_3D : int32_t
{
	BODY_3D_HEAD = 0,
	BODY_3D_CHEST = 1,
	BODY_3D_PELVIS = 2,
	BODY_3D_SHOULDER_L = 3,
	BODY_3D_SHOULDER_R = 4,
	BODY_3D_ELBOW_L = 5,
	BODY_3D_ELBOW_R = 6,
	BODY_3D_HAND_L = 7,
	BODY_3D_HAND_R = 8,
	BODY_3D_CALF_L = 9,
	BODY_3D_CALF_R = 10,
	BODY_3D_FOOT_L = 11,
	BODY_3D_FOOT_R = 12,
	BODY_3D_NUM = 13,
};

struct FDamageCellEX
{
    CXXBYTE<32> DamageCellExName{}; // 0x0
    CXXBYTE<32> ExCellName{}; // 0x20
    FDamageCellEX()
    {
    }

    void Init();
};

class OBJ_CCharBase : public OBJ_CBase
{
    enum BTN_ID
    {
        BTN_A = 0,
        BTN_B = 1,
        BTN_C = 2,
        BTN_D = 3,
        BTN_E = 4,
        BTN_F = 5,
        BTN_G = 6,
        BTN_H = 7,
        BTN_NUM = 8,
    };

    enum EChangeRequestCategory
    {
        CRC_EnterCutscene = 0,
        CRC_EnterNormal = 1,
        CRC_EnterAttack = 2,
        CRC_EnterAttackUltimate1 = 3,
        CRC_EnterAttackUltimate2 = 4,
        CRC_AssistAttack = 5,
        CRC_AssistAttackUltimate = 6,
        CRC_GuardCancelEnterAttack = 7,
        CRC_AssistAttackReady = 8,
        CRC_EnterNormalReady = 9,
        CRC_EnterAttackReady = 10,
        CRC_EnterAttackUltimate1Ready = 11,
        CRC_EnterAttackUltimate2Ready = 12,
        CRC_GuardCancelEnterAttackReady = 13,
        CRC_None = 14,
    };

    struct VSCharMouthTable
    {
        ECharaID m_id{};
        AA_EasyMap<CXXBYTE<16>, CXXBYTE<128>, 32, 1> m_mouthTable{};
    };
	
	struct FEntrySubMemberDispInfo
	{
		int32_t x; // 0x0
		int32_t y; // 0x4
		int32_t z; // 0x8
		bool bDispOn; // 0xC
		FEntrySubMemberDispInfo();
	};

	struct FVoiceSetting
	{
		VOICE_TYPE Type; // 0x0
		char RandomNum; // 0x4
		char PlayPercent; // 0x5
	};

private:
    int32_t CharBaseSyncBegin{};

protected:
    uint32_t m_PlayerFlag{}; // 0x5F74
    uint32_t m_PlayerFlag2{}; // 0x5F78
    uint32_t m_PlayerFlag3{}; // 0x5F7C
    uint32_t m_PlayerFlag4{}; // 0x5F80
    uint32_t m_PlayerFlag5{}; // 0x5F84
    uint32_t m_PlayerFlagTrial{}; // 0x5F88
    uint32_t m_CtrlDir{}; // 0x5F8C
    uint32_t m_EnableFlag{}; // 0x5F90
    uint32_t m_Enable2Flag{}; // 0x5F94
    uint32_t m_EnableFlagPreAction{}; // 0x5F98
    uint32_t m_AttackFlag{}; // 0x5F9C
    uint32_t m_AttackFlag2{}; // 0x5FA0
    double m_LocalWorldTimer{}; // 0x5FA8

public:
    int32_t m_GuardStopCount{}; // 0x5FB0
    int32_t m_AirJumpCount{}; // 0x5FB4
    int32_t m_AirDashCount{}; // 0x5FB8
    int32_t m_AirDashTimer{}; // 0x5FBC
    int32_t m_AirDashTimerMax{}; // 0x5FC0
    int32_t m_AirDashGravity{}; // 0x5FC4
    VSCharMouthTable m_VsCharMouthTable[3]{};
    int32_t m_VsCharMouthTableIdx{}; // 0x976C
    int32_t m_IgnoreSkillTime{}; // 0x9770
    int32_t m_StunCount{}; // 0x9774
    int32_t m_StunCountZeroTimer{}; // 0x9778
    int32_t m_LockWaitTime{}; // 0x977C
    int32_t m_StunCountMax{}; // 0x9780
    uint32_t m_ChangeDir{}; // 0x9784
    int32_t m_ChangeHeight{}; // 0x9788
    int32_t ply_FWalkSpeed{}; // 0x978C
    int32_t ply_BWalkSpeed{}; // 0x9790
    int32_t ply_FDashStartSpeed{}; // 0x9794
    int32_t ply_BDashXSpeed{}; // 0x9798
    int32_t ply_BDashYSpeed{}; // 0x979C
    int32_t ply_BDashGravity{}; // 0x97A0
    int32_t ply_FJumpXSpeed{}; // 0x97A4
    int32_t ply_BJumpXSpeed{}; // 0x97A8
    int32_t ply_JumpSpeed{}; // 0x97AC
    int32_t ply_JumpGravity{}; // 0x97B0
    int32_t ply_FHighJumpXSpeed{}; // 0x97B4
    int32_t ply_BHighJumpXSpeed{}; // 0x97B8
    int32_t ply_HighJumpSpeed{}; // 0x97BC
    int32_t ply_HighJumpGravity{}; // 0x97C0
    int32_t ply_FDashAccelSpeed{}; // 0x97C4
    int32_t ply_FDashReduce{}; // 0x97C8
    int32_t ply_HomingJumpMaxYSpeed{}; // 0x97CC
    int32_t ply_HomingJumpMaxXSpeed{}; // 0x97D0
    int32_t ply_HomingJumpXReduce{}; // 0x97D4
    int32_t ply_HomingJumpYOffset{}; // 0x97D8
    int32_t ply_AirDashHeightLimit{}; // 0x97DC
    int32_t ply_AFDashTime{}; // 0x97E0
    int32_t ply_ABDashTime{}; // 0x97E4
    int32_t ply_Kizetsu{}; // 0x97E8
    int32_t ply_Defence{}; // 0x97EC
    int32_t ply_Guts{}; // 0x97F0
    int32_t ply_Critical{}; // 0x97F4
    int32_t ply_DamageWeight{}; // 0x97F8
    int32_t ply_AirDashCountMax{}; // 0x97FC
    int32_t ply_AirJumpCountMax{}; // 0x9800
    int32_t ply_AirFDashNoAttackTime{}; // 0x9804
    int32_t ply_AirBDashNoAttackTime{}; // 0x9808
    int32_t ply_FWalkTension{}; // 0x980C
    int32_t ply_FJumpTension{}; // 0x9810
    int32_t ply_FDashTension{}; // 0x9814
    int32_t ply_AirFDashTension{}; // 0x9818
    int32_t ply_GBDefence{}; // 0x981C
    int32_t ply_GBRecover{}; // 0x9820
    int32_t ply_JGTension{}; // 0x9824
    int32_t ply_AFDashStartSpeed{}; // 0x9828
    int32_t ply_ABDashStartSpeed{}; // 0x982C
    int32_t ply_PushColWidthStand{}; // 0x9830
    int32_t ply_PushColHeightStand{}; // 0x9834
    int32_t ply_PushColWidthCrouch{}; // 0x9838
    int32_t ply_PushColHeightCrouch{}; // 0x983C
    int32_t ply_PushColWidthAir{}; // 0x9840
    int32_t ply_PushColHeightAir{}; // 0x9844
    int32_t ply_PushColHeightLowAir{}; // 0x9848
    int32_t ply_NearSlashRange{}; // 0x984C
    int32_t ply_JumpMotionFrame_v_up{}; // 0x9850
    int32_t ply_JumpMotionFrame_v_dn{}; // 0x9854
    int32_t ply_JumpMotionFrame_f_up{}; // 0x9858
    int32_t ply_JumpMotionFrame_f_dn{}; // 0x985C
    int32_t ply_JumpMotionFrame_b_up{}; // 0x9860
    int32_t ply_JumpMotionFrame_b_dn{}; // 0x9864
    uint32_t ply_PlayerPrivateFlag{}; // 0x9868
    int32_t ply_HomingJumpYOffset_RED{}; // 0x986C
    int32_t ply_JumpLandingStiffFrame{}; // 0x9870
    CHARSHOES_TYPE ply_ShoesType{}; // 0x9874
    int32_t ply_LandingStiffTime{}; // 0x9878
    int32_t ply_LandingStiffTimeTmp{}; // 0x987C
    int32_t ply_LandingStiffTimeForKy{}; // 0x9880
    int32_t ply_NegativeAnti{}; // 0x9884
    bool ply_ForceNormalDemoAction{}; // 0x9888
    int32_t ply_CPUYowameruRate{}; // 0x988C
    int32_t ply_CPUTokuiKyori{}; // 0x9890
    int32_t ply_CPUTokuiKyoriKodawari{}; // 0x9894
    short ply_TBalanceExec{}; // 0x9898
    short ply_TBalanceFWalk{}; // 0x989A
    short ply_TBalanceFJump{}; // 0x989C
    short ply_TBalanceFDash{}; // 0x989E
    short ply_TBalanceFAirDash{}; // 0x98A0
    short ply_TBalanceBWalk{}; // 0x98A2
    short ply_TBalanceBJump{}; // 0x98A4
    short ply_TBalanceBDash{}; // 0x98A6
    short ply_TBalanceBAirDash{}; // 0x98A8
    short ply_TBalanceAtkHit[5]{}; // 0x98AA
    short ply_TBalanceAtkHitGuard{}; // 0x98B4
    short ply_TBalanceGuard[5]{}; // 0x98B6
    short ply_TBalanceJGuard[5]{}; // 0x98C0
    short ply_TBalanceNoTouch{}; // 0x98CA
    short ply_TBalanceNoTouchTime{}; // 0x98CC
    short ply_TBalanceSide{}; // 0x98CE
    short ply_TBalanceSideTime{}; // 0x98D0
    short ply_NegativeExec{}; // 0x98D2
    short ply_NegativeBWalk{}; // 0x98D4
    short ply_NegativeBJump{}; // 0x98D6
    short ply_NegativeBDash{}; // 0x98D8
    short ply_NegativeBAirDash{}; // 0x98DA
    short ply_NegativeNoTouch{}; // 0x98DC
    short ply_NegativeNoTouchTime{}; // 0x98DE
    short ply_NegativeSide{}; // 0x98E0
    short ply_NegativeSideTime{}; // 0x98E2
    short ply_TBalanceMagnify[10]{}; // 0x98E4
    short ply_NegativeMagnify[10]{}; // 0x98F8
    short ply_DistanceThreshold[3]{}; // 0x990C
    short ply_TBalanceDistanceMagnify[3]{}; // 0x9912
    short ply_NegativeDistanceMagnify[3]{}; // 0x9918
    short ply_PositiveBonus{}; // 0x991E
    short ply_PositiveTPenalty{}; // 0x9920
    short ply_NegativeWarning{}; // 0x9922
    short ply_NegativeWarningTension{}; // 0x9924
    short ply_NegativeTensionPenalty{}; // 0x9926
    short ply_NegativeTensionBalance{}; // 0x9928
    short ply_GuardTension[5]{}; // 0x992A
    short ply_BarrierGuardStop{}; // 0x9934
    short ply_BarrierGuardStopAir{}; // 0x9936
    short ply_BarrierGuardTension[5]{}; // 0x9938
    short ply_BarrierGuardTensionShotPer{}; // 0x9942
    short ply_BarrierUseTension{}; // 0x9944
    short ply_BarrierUseTensionAir{}; // 0x9946
    short ply_BarrierAirSpeedX{}; // 0x9948
    short ply_BarrierAirSpeedY{}; // 0x994A
    short ply_BarrierGravity{}; // 0x994C

private:
    short ply_CDT_Assist{}; // 0x994E
    short ply_CDT_Change{}; // 0x9950
    short ply_CDT_UltimateChange{}; // 0x9952
    short ply_CDT_GuardCancelChange{}; // 0x9954
    short ply_CDT_ForceChange{}; // 0x9956
    short ply_CooldownHoseiTime{}; // 0x9958
    short ply_CDT_Inner{}; // 0x995A
    int32_t ply_HPRecoverPerFrame{}; // 0x995C
    int32_t ply_HPRecoverPerFrameInBurst{}; // 0x9960
    CHAR_PHYSIQUE ply_Physique{}; // 0x9964
    CHAR_ATTR_TYPE ply_AttrType{}; // 0x9968
    int32_t ply_Weight{}; // 0x996C

public:
    CXXBYTE<32> ply_DamageCell[57]{}; // 0x9970
    FDamageCellEX ply_DamageCellEx[128]{}; // 0xA090
    uint32_t m_ComboCount{}; // 0xC090
    uint32_t m_ComboBreakTime{}; // 0xC094
    uint32_t m_ComboCountAddTime{}; // 0xC098
    uint32_t m_ComboCountAddTimeWithStop{}; // 0xC09C
    int32_t m_ComboDamage{}; // 0xC0A0
    int32_t m_ComboDamageFromBSCA{}; // 0xC0A4
    int32_t m_ComboDamageTotal{}; // 0xC0A8
    int32_t m_ComboDamageDisp{}; // 0xC0AC
    int32_t m_ComboPreDamage{}; // 0xC0B0
    int32_t m_ComboTime{}; // 0xC0B4
    int32_t m_ComboTimeWithOutAnten{}; // 0xC0B8
    int32_t m_ComboHoseiOnceDone{}; // 0xC0BC
    int32_t m_ComboDamageRate{}; // 0xC0C0
    int32_t m_ComboDamageRomanCancel{}; // 0xC0C4
    float m_ComboDamageRedF01{}; // 0xC0C8
    uint32_t m_OwnComboCount{}; // 0xC0CC
    CXXBYTE<32> m_ComboAcceptActionName{}; // 0xC0D0
    CXXBYTE<32> m_ComboLastDamageActionName{}; // 0xC0F0
    bool m_IsImperfectCombo{}; // 0xC110
    bool m_IsImperfectComboAddFlag{}; // 0xC111
    bool m_UkemiMiss{}; // 0xC112
    bool m_NagenukeMiss{}; // 0xC113
    bool m_ComboNoDie{}; // 0xC114
    int32_t m_ImperfectComboLog[3]{}; // 0xC118
    int32_t m_KizetsuPoint{}; // 0xC124
    int32_t m_KizetsuMax{}; // 0xC128
    int32_t m_KizetsuTime{}; // 0xC12C
    int32_t m_KizetsuTimeMax{}; // 0xC130
    int32_t m_KizetsuDecForTutorial{}; // 0xC134
    int32_t m_GuardSustain{}; // 0xC138
    int32_t m_GuardOshikomareSustain{}; // 0xC13C
    int32_t m_GuardOshikomareCount{}; // 0xC140
    int32_t m_ThrowResistTime{}; // 0xC144
    int32_t m_LockRejectInputTime{}; // 0xC148
    int32_t m_LockRejectDisableTime{}; // 0xC14C
    bool m_LockRejectIsRenda{}; // 0xC150
    int32_t m_JustGuardAutoKeyBackTime{}; // 0xC154
    int32_t m_TensionVal{}; // 0xC158
    int32_t m_TensionLimitTime{}; // 0xC15C
    bool m_IsOldBarrier{}; // 0xC160
    int32_t m_AccelVal{}; // 0xC164
    int32_t m_KeyBackMaintain{}; // 0xC168
    int32_t m_GuardDirectionWithMekuri{}; // 0xC16C
    int32_t m_MekuriMaintain{}; // 0xC170
    bool m_IamLeft{}; // 0xC174
    bool m_IamLeftPrev{}; // 0xC175
    ID_CMNACT m_CurCommonActionID{}; // 0xC178
	unsigned char m_InpFlag[324][2]; // 0xC17C
	int32_t m_BtnLastTrgCount[8]; // 0xC404
	int32_t m_BtnLastTrgOffCount[8]; // 0xC424
	int32_t m_BtnHoldCount[8]; // 0xC444
	int32_t m_BtnRendaCount[8]; // 0xC464
	int32_t m_BtnRendaAddTime[8]; // 0xC484
	int32_t m_UkemiBtnTime; // 0xC4A4
	int32_t m_BtnHoldCountWithoutGuard[8]; // 0xC4A8
	unsigned char m_PreFRCInput; // 0xC4C8
	unsigned char m_PreTenkey; // 0xC4C9
	unsigned char m_DashTime1st[2]; // 0xC4CA
	unsigned char m_DashTime2nd[2]; // 0xC4CC
	unsigned char m_DashChangeTenkey[2]; // 0xC4CE
	unsigned char m_JustGuardInputTime[2]; // 0xC4D0
	unsigned char m_JustGuardPenaltyTime[2]; // 0xC4D2
	unsigned char m_PreTenkeyEasy; // 0xC4D4
	unsigned char m_DashTime1stEasy[2]; // 0xC4D5
	unsigned char m_DashTime2ndEasy[2]; // 0xC4D7
	unsigned char m_DashChangeTenkeyEasy[2]; // 0xC4D9
	int32_t m_stylishComboCount; // 0xC4DC
	int32_t m_PrivateVal[8]; // 0xC4E0
	int32_t m_SkillCheckBit; // 0xC500

private:
	int32_t m_ChargeShotVal[4]; // 0xC504
	unsigned char m_CameraComboOnce[10]; // 0xC514
	unsigned char m_RendaSmashStartType[3]; // 0xC51E
	unsigned char m_RendaSmashType[3]; // 0xC521

public:
	
	int32_t m_DemoTimer; // 0xC524
	GAME_CCockpitEXGage m_ExGage[5]; // 0xC528
	int32_t m_DashInputKeepTime; // 0xC5DC
	int32_t m_PlayerAttackRate; // 0xC5E0
	int32_t m_PlayerDefenceRate; // 0xC5E4
	int32_t m_CharacterAddAttackRate; // 0xC5E8
	int32_t m_CharacterAddDefenceRate; // 0xC5EC
	int32_t m_PlayerCrushRate; // 0xC5F0
	int32_t m_PlayerTensionRate; // 0xC5F4
	int32_t m_SousaiCancelTime; // 0xC5F8
	int32_t m_ReactionWait; // 0xC5FC
	CXXBYTE<32> m_TmpLabel; // 0xC600
	int32_t m_AirTimer; // 0xC620
	int32_t m_DamageColX; // 0xC624
	int32_t m_DamageColY; // 0xC628
	int32_t m_DamageColW; // 0xC62C
	int32_t m_DamageColH; // 0xC630
	uint32_t m_ActionRequestFlagForJumpTmp; // 0xC634
	HACT_HitAction m_HitAction; // 0xC638
	ADAT_TYPE m_AirDamageAngleType; // 0xC63C
	int32_t m_SkyDashCorrect; // 0xC640
	int32_t m_BackStepInvalidTime; // 0xC644
	int32_t m_BoundReadyTime; // 0xC648
	int32_t m_ExKizetsu; // 0xC64C
	int32_t m_RomanCancelRsvSpeedX; // 0xC650
	int32_t m_LongSenkoInputActiveTime; // 0xC654
	int32_t m_LongSenkoInputActiveTimeForDust; // 0xC658
	bool m_LongSenkoInputActiveOnCurAction; // 0xC65C
	int32_t m_OldPosXDebug; // 0xC660
	int32_t m_OldPosYDebug; // 0xC664
	int32_t m_AttackTimeDebug; // 0xC668
	int32_t m_DustHomingTime; // 0xC66C
	int32_t m_DustHomingSubTime; // 0xC670
	int32_t m_DustBoundTime; // 0xC674
	int32_t m_NewDustHomingTime; // 0xC678
	int32_t m_CmnActObjReg0; // 0xC67C
	int32_t m_CmnActObjReg1; // 0xC680
	int32_t m_CmnActObjReg2; // 0xC684
	int32_t m_CmnActObjReg3; // 0xC688
	int32_t m_CmnActObjReg4; // 0xC68C
	int32_t m_CmnActObjReg5; // 0xC690
	int32_t m_CmnActObjReg6; // 0xC694
	int32_t m_CmnActObjReg7; // 0xC698
	int32_t m_ForceRomanCancelYoyakuTimer; // 0xC69C
	int32_t m_ForceRomanCancelTimer; // 0xC6A0
	int32_t m_ForceRomanCancelDoneTimer; // 0xC6A4
	int32_t m_ForceRomanCancelIgnoreTimer; // 0xC6A8
	int32_t m_NandemoCancelTime; // 0xC6AC
	int32_t m_ExPointForPGX; // 0xC6B0
	int32_t m_ExPointForPGY; // 0xC6B4
	int32_t m_GuardBalance; // 0xC6B8
	int32_t m_GuardBalanceStopTime; // 0xC6BC
	int32_t m_GuardBalanceMaxTime; // 0xC6C0
	uint32_t m_TmpSkillForceDisableFlag; // 0xC6C4
	CSkillInfo * m_LastSkillAttackPtr; // 0xC6C8
	int32_t m_AttackLastHitTime; // 0xC6D0
	CXXBYTE<16> m_CommonVoiceTable[120]; // 0xC6D4
	int32_t m_SlowTime; // 0xCE54
	int32_t m_SlowTimeBySC; // 0xCE58
	int32_t m_RomanCancelEndTime; // 0xCE5C
	int32_t m_RomanCancelEndTimeByAttack; // 0xCE60
	int32_t m_RomanCancelEndTimeByAttackTmp; // 0xCE64
	int32_t m_RomanCancelBattenTime; // 0xCE68
	int32_t m_IchigekiGage; // 0xCE6C
	CXXBYTE<32> m_JimakuName; // 0xCE70
	int32_t m_JimakuTime; // 0xCE90
	int32_t m_JimakuForceTime; // 0xCE94
	int32_t m_JimakuBGTime; // 0xCE98
	int32_t m_DemoEnd_YoinTime; // 0xCE9C
	CXXBYTE<32> m_EntryActionNameSelf; // 0xCEA0
	CXXBYTE<32> m_EntryActionNameEnemy; // 0xCEC0
	CXXBYTE<32> m_EntryActionNameReady; // 0xCEE0
	int32_t m_HeliumTime; // 0xCF00
	int32_t m_GTmpReg[8]; // 0xCF04
	int32_t m_JitabataHitStopHendou; // 0xCF24
	int32_t m_BurstYomiTime; // 0xCF28
	int32_t m_ComboVoiceSpeakingTimer; // 0xCF2C
	int32_t m_ComboVoiceUkemiWait; // 0xCF30
	int32_t m_ComboVoiceReadyTimer; // 0xCF34
	int32_t m_JumpCancelSenkoActiveTime; // 0xCF38
	CXXBYTE<32> m_MeshSetNameExchangeTable[20]; // 0xCF3C
	CXXBYTE<32> m_AnimeNameExchangeTable[8]; // 0xD1BC
	float m_HitPointLengthDispMaxF01; // 0xD2BC
	int32_t m_AirJumpTime; // 0xD2C0
	bool m_AirJumpFlyMOM; // 0xD2C4
	int32_t m_WinActionButton; // 0xD2C8
	int32_t m_TrainingValue; // 0xD2CC
	int32_t m_GGBlockingOKTime; // 0xD2D0
	int32_t m_GGBlockingIgnoreTime; // 0xD2D4
	int32_t m_ThrowInputTime; // 0xD2D8
	int32_t m_NoNagenukeTime; // 0xD2DC
	int32_t m_HomingDashTsuigekiTime; // 0xD2E0
	int32_t m_DokiDokiStopTime; // 0xD2E4
	int32_t m_DokiDokiStopDamage; // 0xD2E8
	uint32_t m_TimeWithoutAnten; // 0xD2EC
	int32_t m_DustHomingDash2HoseiBase; // 0xD2F0
	int32_t m_DustHomingDash2HoseiUntilBound; // 0xD2F4
	int32_t m_NearSlashObjectDistance; // 0xD2F8
	int32_t m_RedRomanCancelTime; // 0xD2FC
	int32_t m_FaultlessDefenceDisableTime; // 0xD300
	int32_t m_SlowRate; // 0xD304
	int32_t m_HitPointRecover; // 0xD308
	int32_t m_HitPointRecoverStopTime; // 0xD30C
	int32_t m_TrainingHPRecoverWait; // 0xD310
	short m_SenkoInputNormal; // 0xD314
	short m_SenkoInputSpecial; // 0xD316
	short m_SenkoInputUltimate; // 0xD318
	int32_t m_DeadCounter; // 0xD31C
	int32_t m_DmgColCounter; // 0xD320
	int32_t m_AssistAttackPosZ; // 0xD324
	int32_t m_JumpDir; // 0xD328
	unsigned char m_CmdSuccessInAnten; // 0xD32C
	unsigned char m_DownFromSlideDown; // 0xD32D
	int32_t m_WorldSideBreakPoint; // 0xD330
	int32_t m_CmnCharaReg[24]; // 0xD334
	int32_t m_CmnCharaActReg[8]; // 0xD394
	int32_t m_DamageActionCount; // 0xD3B4
	int32_t m_FuwafuwaDownTimer; // 0xD3B8
	CXXBYTE<32> m_DamageTransferInterruptFunc; // 0xD3BC
	int32_t m_RedRCTime; // 0xD3DC
	unsigned short m_WSBEstimateDamage; // 0xD3E0
	CXXBYTE<32> m_ComboSameNameStack[100]; // 0xD3E2
	int32_t m_SameAttackGravity; // 0xE064
	int32_t m_BoundAddGravity; // 0xE068
	CAtkParam m_AtkParamForGGThrowStack; // 0xE070
	CAtkParamEx m_AtkParamCHForGGThrowStack; // 0xE468
	CAtkParamEx m_AtkParamNHForGGThrowStack; // 0xE520
	int32_t m_TensionBalance; // 0xE5D8
	int32_t m_TensionPenaltyTime; // 0xE5DC
	int32_t m_BurstPenaltyTime; // 0xE5E0
	int32_t m_TensionGG; // 0xE5E4
	int32_t m_TensionGGUseDisp; // 0xE5E8
	int32_t m_BurstLog; // 0xE5EC
	int32_t m_TensionNoTouchTime; // 0xE5F0
	int32_t m_NegativeVal; // 0xE5F4
	int32_t m_TensionMovePenaltyTime; // 0xE5F8
	int32_t m_TensionSideTime; // 0xE5FC
	FEntrySubMemberDispInfo m_EntrySubMemberDispInfo[2]; // 0xE600
	FVoiceSetting m_VoiceSettingTable[100]; // 0xE620

private:
    bool m_Entry{}; // 0xE940
    bool m_EntryBattle{}; // 0xE941
    bool m_EntryBattleDoing{}; // 0xE942
    bool m_LeaveRequest{}; // 0xE943
    bool m_LeaveRequestImm{}; // 0xE944
    EChangeRequestCategory m_ChangeRequestCategory{};
    bool m_Win{}; // 0xE94C
    CXXBYTE<32> m_DefaultMeshSet{}; // 0xE94D
    CXXBYTE<32> m_WinCameraObjName{}; // 0xE96D
    short m_CooldownTime{}; // 0xE98E
    short m_CooldownTimeMax{}; // 0xE990
    short m_InnerCooldownTime{}; // 0xE992
    bool m_bFullCooldownTime{}; // 0xE994
    bool m_bPlayReadySE{}; // 0xE995
    int32_t m_ResultWinPos{}; // 0xE998
    bool m_isAddUltimateChangeCommand{}; // 0xE99C
    EMemberID m_callingChar{}; // 0xE9A0
    EMemberID m_calledChar{}; // 0xE9A4

public:
    int32_t m_HomingDashCount{}; // 0xE9E8
    int32_t m_HomingDashCountMax{}; // 0xE9EC
    bool m_bChangeHomingDash{}; // 0xE9F0
    bool m_bGCHomingDash{}; // 0xE9F1
    int32_t m_MikiwameMoveCount{}; // 0xEA0C
    int32_t m_MikiwameMoveCountMax{}; // 0xEA10
    unsigned char m_MikiwameMoveCancelAvailable{}; // 0xEA14
    unsigned char m_MemberChangeUltimateAvailable{}; // 0xEA15

private:
    int32_t CharBaseSyncEnd;
    
public:
    CXXBYTE<16> m_CharName{}; // 0xEF5C
    CXXBYTE<16> m_CharNameForVoice{}; // 0xEF6C
    int32_t m_VoiceCond_MyHP[10]{}; // 0xEF7C
    int32_t m_VoiceCond_OpponentHP[10]{}; // 0xEFA4
    bool m_VoiceCond_OpponentCharaEnable[10]{}; // 0xEFCC
    bool m_VoiceCond_OpponentChara[32][10]{}; // 0xEFD6
    VAR_Type m_VoiceCond_Var[10]{}; // 0xF118

public:
	CCPUInfo m_CPUInfo; // 0xF158    
	CSkillInfoList m_SkillInfoList; // 0xF280
	AA_EasyHash<CXXBYTE<16>,120,480> m_CommonVoiceHash; // 0x29D7C
	AA_EasyHash<CXXBYTE<16>,100,400> m_VoiceSettingHash; // 0x2A9B0
	AA_EasyHash<CXXBYTE<32>,20,80> m_MeshSetNameExchangeHash; // 0x2B3DC
	AA_EasyHash<CXXBYTE<32>,600,2400> m_MeshSetCellHash; // 0x2B728
	unsigned char m_MeshSetCellTable[600]; // 0x3199C
	AA_EasyHash<CXXBYTE<32>,8,32> m_AnimeNameExchangeHash; // 0x31BF4
	AA_EasyMap<CXXBYTE<16>,CXXBYTE<128>,128,1> m_MouthTable; // 0x31D48

    OBJ_CCharBase();
    ~OBJ_CCharBase() override {}
    void ObjectConstructor_ForPlayer();
    void PlayerInitializeOnEasyReset();

    short GetChangeCDT() { return ply_CDT_Change; }
    short GetUltimateChangeCDT() { return ply_CDT_UltimateChange; }
    short GetGuardCancelCDT() { return ply_CDT_GuardCancelChange; }
    short GetForceChangeCDT() { return ply_CDT_ForceChange; }
    short GetInnerCDT() { return ply_CDT_Inner; }
    bool CheckPlayerFlag(PLAYER_FLAG flag) { return m_PlayerFlag & flag; }
    bool CheckPlayerFlag2(PLAYER_FLAG2 flag) { return m_PlayerFlag2 & flag; }
    void DelPlayerFlag2(PLAYER_FLAG2 flag) { m_PlayerFlag2 &= ~flag; }
    void AddPlayerFlag4(PLAYER_FLAG4 flag) { m_PlayerFlag4 |= flag; }
    void DelPlayerFlag4(PLAYER_FLAG4 flag) { m_PlayerFlag4 &= ~flag; }
    bool CheckPlayerFlag4(PLAYER_FLAG4 flag) { return m_PlayerFlag4 & flag; }
    bool DelAttackFlag(PLATTACK_FLAG flag) { return m_AttackFlag &= ~flag; }
    bool CheckAttackFlag(PLATTACK_FLAG flag) { return m_AttackFlag & flag; }

    const char* GetContextActionName(const CXXBYTE<32>& actName) override;

public:
	int32_t CommandFlagUpdate();

    bool IsDead() override;
    void SetEntry(bool entry) { m_Entry = entry; }
    bool IsEntry() { return m_Entry; }
	bool IsEntryBattle() { return m_EntryBattle; }
    bool IsEntryBattleDoing() { return m_EntryBattleDoing; }
    void SetCallingChar(EMemberID memberID) { m_callingChar = memberID; }
    void SetCalledChar(EMemberID memberID) { m_calledChar = memberID; }

    void SetImmLeaveRequest(bool bImmidiate) { m_LeaveRequestImm = bImmidiate; }

    bool IsLeaveRequest() { return !(m_ObjFlag2 & OBJ_FLG_2_LINK_MATCH_RESULT_CAMERA) && m_LeaveRequest; }

    void ChangeEnterRequest() { m_ChangeRequestCategory = CRC_EnterNormal; }
    void ChangeEnterAttackRequest() { m_ChangeRequestCategory = CRC_EnterAttack; }
    void GuardCancelChangeEnterAttackRequest() { m_ChangeRequestCategory = CRC_GuardCancelEnterAttack; }
    void ChangeAttackUltimate1ReadyRequest() { m_ChangeRequestCategory = CRC_EnterAttackUltimate1; }
    void ChangeAttackUltimate2ReadyRequest() { m_ChangeRequestCategory = CRC_EnterAttackUltimate2; }
    void SetCooldownTime(int32_t frame, int32_t innerFrame, bool bPlaySE);
};
