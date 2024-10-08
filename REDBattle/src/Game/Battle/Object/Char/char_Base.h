#pragma once
#include <Game/Battle/Object/obj_base.h>
#include "char_ActFlag.h"

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

enum SKLEST
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

public:
    int32_t m_ExKizetsu{}; // 0xC64C

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

public:
    CXXBYTE<16> m_CharName{}; // 0xEF5C
    CXXBYTE<16> m_CharNameForVoice{}; // 0xEF6C
    int32_t m_VoiceCond_MyHP[10]{}; // 0xEF7C
    int32_t m_VoiceCond_OpponentHP[10]{}; // 0xEFA4
    bool m_VoiceCond_OpponentCharaEnable[10]{}; // 0xEFCC
    bool m_VoiceCond_OpponentChara[32][10]{}; // 0xEFD6
    VAR_Type m_VoiceCond_Var[10]{}; // 0xF118

public:
    OBJ_CCharBase();
    void ObjectConstructor_ForPlayer();
    void PlayerInitializeOnEasyReset();

    short GetChangeCDT() { return ply_CDT_Change; }
    short GetUltimateChangeCDT() { return ply_CDT_UltimateChange; }
    short GetGuardCancelCDT() { return ply_CDT_GuardCancelChange; }
    short GetForceChangeCDT() { return ply_CDT_ForceChange; }
    short GetInnerCDT() { return ply_CDT_Inner; }
    bool CheckPlayerFlag(PLAYER_FLAG flag) { return m_PlayerFlag & flag; }
    void DelPlayerFlag2(PLAYER_FLAG2 flag) { m_PlayerFlag2 &= ~flag; }
    void AddPlayerFlag4(PLAYER_FLAG4 flag) { m_PlayerFlag4 |= flag; }
    void DelPlayerFlag4(PLAYER_FLAG4 flag) { m_PlayerFlag4 &= ~flag; }
    bool CheckPlayerFlag4(PLAYER_FLAG4 flag) { return m_PlayerFlag4 & flag; }
    bool CheckAttackFlag(PLATTACK_FLAG flag) { return m_AttackFlag & flag; }

    const char* GetContextActionName(const CXXBYTE<32>& actName) override;

    bool IsDead() override;
    void SetEntry(bool entry) { m_Entry = entry; }
    bool IsEntry() { return m_Entry; }
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
