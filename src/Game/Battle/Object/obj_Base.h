#pragma once
#include <cstdint>
#include "obj_scriptinc.h"
#include "obj_BBScript.h"
#include <Game/REDGameConstant.h>
#include "AALib/Base/Jon/TL_Jon.h"
#include "AALib/Common/tl_Filepack.h"
#include <Game/AudioManager.h>
#include "obj_Flag.h"
#include "AALib/Common/cmn_class.h"

class OBJ_CCharBase;
class OBJ_CBase;

class CVoiceInfo
{
public:
    CVoiceInfo()
    {
    }

    void CVoiceInfoInit();
    int32_t m_VoiceTimer{}; // 0x0
    int32_t m_VoiceHistoryTimer{}; // 0x4
    CXXBYTE<16> m_VoiceHistoryName{}; // 0x8
    char m_DamageVoiceWait{}; // 0x18
    bool m_ForceVoicePlay{}; // 0x19
    bool m_IgnoreForceVoicePlay{}; // 0x1A
    VOICE_TYPE m_LastVoiceType[8]{}; // 0x1C
    CXXBYTE<16> m_LastPlayVoiceName[8]{}; // 0x3C
    int32_t m_LastRandomVoiceIndex[8]{}; // 0xBC
    int32_t m_LastVoicePriority[8]{}; // 0xDC
    int32_t m_LastVoiceRemainCount[8]{}; // 0xFC
    bool m_bDamageVoiceRequest{}; // 0x11C
    CXXBYTE<16> m_DamageVoiceName{}; // 0x11D
    struct SFinishBranchVoiceInfo
    {
        bool bSet{}; // 0x0
        CXXBYTE<16> DefaultVoice{}; // 0x1
        CXXBYTE<16> FinishVoice{}; // 0x11
        void Reset();

        SFinishBranchVoiceInfo()
        {
        }
    };

    SFinishBranchVoiceInfo m_FinishBranchVoiceInfo{}; // 0x12D
};

class GAME_CCockpitEXGage
{
public:
    uint32_t m_IconID{}; // 0x0
    uint32_t m_SplitNum{}; // 0x4
    int32_t m_MaxVal{}; // 0x8
    int32_t m_Val{}; // 0xC
    float m_DotWidth{}; // 0x10
    uint32_t m_Color{}; // 0x14
    uint32_t m_MaxColor{}; // 0x18
    uint32_t m_EXGFlag{}; // 0x1C
    bool m_Active{}; // 0x20
    GAME_CCockpitEXGage() {}

    ~GAME_CCockpitEXGage() {}

    void Reset();
};

enum ACTV_STATE
{
    ACTV_NOT_ACTIVE = 0,
    ACTV_ACTIVE = 1,
    ACTV_REQ_ACTIVE = 2,
    ACTV_REQ_NO_ACTIVE = 3,
    ACTV_WAITING_BEGIN = 4,
    ACTV_WAITING_0 = 4,
    ACTV_WAITING_1 = 5,
    ACTV_WAITING_2 = 6,
};

enum OBJ_DIR
{
    OBJDIR_RIGHT = 0,
    OBJDIR_LEFT = 1,
    OBJDIR_NUM = 2,
};

enum SNDTYPE
{
    SNDTYPE_COMMON_SE = 0,
    SNDTYPE_VOICE = 1,
    SNDTYPE_SE = 2,
    SNDTYPE_NARRATION = 3,
    SNDTYPE_PRIVATE_SE = 4,
    SNDTYPE_TUTORIAL = 5,
    SNDTYPE_COMMON_VOICE = 6,
    SNDTYPE_BG_CLASH_SE = 7,
};

enum SNDREQFLG
{
    SNDREQFLG_CENTER = 2,
    SNDREQFLG_OBJ_POS = 4,
    SNDREQFLG_TUTORIAL_GUIDE = 8,
    SNDREQFLG_VOICE_NAME_FIX = 16,
    SNDREQFLG_WITH_NORMAL_CUE = 32,
    SNDREQFLG_FORCE_LIPSYNC = 64,
};

struct sSoundReq
{
    int32_t m_Volume{}; // 0x0
    int32_t m_Pitch{}; // 0x4
    uint32_t m_SoundReqFlag{}; // 0x8
    uint32_t m_Channel{}; // 0xC
    int32_t m_RandomChannel{}; // 0x10
    ESoundBank m_Bank{}; // 0x14
    int32_t m_Priority{}; // 0x18
    sSoundReq()
    {
    }

    void sSoundReqClear();
};

class OBJ_CBaseRelativePtr
{
private:
    OBJ_CBase* m_Ptr{}; // 0x0
public:
    OBJ_CBaseRelativePtr() { InitOBJ_CBaseRelativePtr(); }
    void InitOBJ_CBaseRelativePtr() { m_Ptr = nullptr; }
    void SetPtr(OBJ_CBase* obj);
    void ClearPtr();
    OBJ_CBase* GetPtr() { return m_Ptr; }
    operator OBJ_CBase*() const { return m_Ptr; }

    OBJ_CBaseRelativePtr& operator=(OBJ_CBaseRelativePtr ptr)
    {
        m_Ptr = ptr.m_Ptr;
        return *this;
    }

    OBJ_CBaseRelativePtr& operator=(OBJ_CBase* obj)
    {
        m_Ptr = obj;
        return *this;
    }
};

enum STOP_TYPE
{
    STOP_TYPE_NON = 0,
    STOP_TYPE_HITSTOP = 1,
    STOP_TYPE_SLOW = 2,
    STOP_TYPE_ANTEN = 3,
};

class CCreateArg
{
public:
    CCreateArg()
    {
    }

    void CCreateArgInit();
    CXXBYTE<32> m_CreateArg_SocketName{}; // 0x0
    int32_t m_CreateArg_Angle{}; // 0x20
    int32_t m_CreateArg_AngleY{}; // 0x24
    int32_t m_CreateArg_OffsetPosX{}; // 0x28
    int32_t m_CreateArg_OffsetPosY{}; // 0x2C
    int32_t m_CreateArg_OffsetPosZ{}; // 0x30
    int32_t m_CreateArg_ScaleX{}; // 0x34
    int32_t m_CreateArg_ScaleY{}; // 0x38
    int32_t m_CreateArg_ScaleZ{}; // 0x3C
    int32_t m_CreateArg_Hikitsugi0{}; // 0x40
    int32_t m_CreateArg_Hikitsugi1{}; // 0x44
    uint32_t m_CreateArg_HkrColor{}; // 0x48
    uint32_t m_CreateArg_MltColor{}; // 0x4C
    int32_t m_CreateArg_TransPriority{}; // 0x50
    PTDIR m_CreateArg_Direction{}; // 0x54
    bool m_CreateArg_SocketUse{}; // 0x55
    bool m_CreateArg_SocketWithRot{}; // 0x56
    bool m_CreateArg_NoAssert{}; // 0x57
    CO_TYPE m_CreateArg_SocketOwner{}; // 0x58
    bool m_CreateArg_LinkMaterialParticle{}; // 0x5C
    bool m_CreateArg_ParticleUnuseMatInstance{}; // 0x5D
    uint32_t m_CreateArg_Delay{}; // 0x60
    int32_t m_CreateArg_PointLightSide{}; // 0x64
    int32_t m_CreateArg_PointLightMember{}; // 0x68
};

class OBJ_CBase
{
private:
    int ObjBaseSyncBegin{};

public:
    OBJ_CBase();
    virtual ~OBJ_CBase() = default;
    uint32_t m_AtkPriority{};
    ACTV_STATE m_ActiveState{};
    uint32_t m_ObjectSortPriority{};
    bool m_IsPlayerObj{};
    uint32_t m_UniqID{};
    uint32_t m_ObjTimer{};
    uint32_t m_BuruBuruPartsTime{};
    bool m_IsDirty{};
    uint32_t m_WatchedCount{};
    uint32_t m_ActionChangeID{};
    int32_t m_TmpWork{};
    int32_t m_ObjectPriority{};
    RS_RENDER_STAGE m_ObjectRenderStage{};
    int32_t m_ObjectGeneration{};
    SIDE_ID m_SideID{};
    SIDE_ID m_FixedSideID{};
    ECharaID m_CharaID{};
    ECharaID m_FixedCharaID{};
    EMemberID m_MemberID{};
    EMemberID m_FixedMemberID{};
    EBattleScript m_ScriptType{};
    AA_CCollision_JON m_ClsnAnalyzer{};
    AA_Filepack_FPAC m_ColPac{};

    uint32_t m_ObjFlag{};
    uint32_t m_ObjFlag2{};
    uint32_t m_ObjFlag3{};
    uint32_t m_ObjFlag4{};
    uint32_t m_ObjFlag5{};
    uint32_t m_ActionKeepFlag{};
    uint32_t m_ObjSignal{};
    uint32_t m_ActionTime{};
    uint32_t m_ActionTimeMax{};
    uint32_t m_ActionTimeNoStop{};
    uint32_t m_OnIdlingtime{};

    int32_t m_CommonActionMark{};
    int32_t m_TmpReg{};
    int32_t m_ActReg0{};
    int32_t m_ActReg1{};
    int32_t m_ActReg2{};
    int32_t m_ActReg3{};
    int32_t m_ActReg4{};
    int32_t m_ActReg5{};
    int32_t m_ActReg6{};
    int32_t m_ActReg7{};
    int32_t m_ObjReg0{};
    int32_t m_ObjReg1{};
    int32_t m_ObjReg2{};
    int32_t m_ObjReg3{};
    int32_t m_ObjReg4{};
    int32_t m_ObjReg5{};
    int32_t m_ObjReg6{};
    int32_t m_ObjReg7{};
    int32_t m_PgActReg0{};
    int32_t m_PgActReg1{};
    int32_t m_PgActReg2{};
    int32_t m_PgActReg3{};
    int32_t m_PgObjReg0{};
    int32_t m_PgObjReg1{};
    int32_t m_PgObjReg2{};
    int32_t m_PgObjReg3{};
    int32_t m_SoundActReg0{};
    int32_t m_SoundActReg1{};
    int32_t m_SoundActReg2{};
    int32_t m_SoundActReg3{};
    int32_t m_SoundObjReg0{};
    int32_t m_SoundObjReg1{};
    int32_t m_SoundObjReg2{};
    int32_t m_SoundObjReg3{};

    int32_t m_CPUVal0{};
    int32_t m_CPUVal1{};
    int32_t m_CPUVal2{};
    int32_t m_CPUVal3{};
    int32_t m_CPUVal4{};
    int32_t m_CPUVal5{};
    int32_t m_CPUVal6{};
    int32_t m_CPUVal7{};

    uint32_t m_HitStopTime{};
    bool m_bSlowHitstop{};
    uint32_t m_HitStopTimeMax{};
    uint32_t m_HitStopTimeBySousai{};
    uint32_t m_HitStopTimeReq{};
    uint32_t m_HitStopTimeReqLevel{};
    bool m_bHitStopTimeReqSlow{};

    int32_t m_UltimateReq_StopTime{};
    int32_t m_UltimateReq_StopTimeSelf{};
    uint32_t m_UltimateReq_Flag{};

    BG_TYPE m_BGType{};
    int32_t m_LandingHeight{};

    OBJ_CBaseRelativePtr m_pParentPly{};
    OBJ_CBaseRelativePtr m_pParentObj{};
    OBJ_CBaseRelativePtr m_pTargetObj{};
    OBJ_CBaseRelativePtr m_pLinkObject_PushCollision{};
    OBJ_CBaseRelativePtr m_pLinkObject_Angle{};
    OBJ_CBaseRelativePtr m_pLinkObject_Position{};
    OBJ_CBaseRelativePtr m_pLinkObject_Direction{};
    OBJ_CBaseRelativePtr m_pLinkObject_DamageToEliminate{};
    OBJ_CBaseRelativePtr m_pLinkObject_ChangeToEliminate{};
    OBJ_CBaseRelativePtr m_pLinkObject_Stop{};
    OBJ_CBaseRelativePtr m_pLinkObject_PositionCenter{};
    OBJ_CBaseRelativePtr m_pLinkObject_Scale{};
    OBJ_CBaseRelativePtr m_pLinkObject_Z{};
    OBJ_CBaseRelativePtr m_pLinkObject_Collision{};
    OBJ_CBaseRelativePtr m_pLinkObject_Color{};
    OBJ_CBaseRelativePtr m_pLinkObject_MaterialSet{};
    OBJ_CBaseRelativePtr m_pLinkObject_CmnMaterialParam{};
    OBJ_CBaseRelativePtr m_pPrevChild{};
    OBJ_CBaseRelativePtr m_pTrialObj{};
    OBJ_CBaseRelativePtr m_pChildStack[9]{};

    uint32_t m_ActionFlag{};
    uint32_t m_ActionFlag2{};
    uint32_t m_CollisionFlag{};
    uint32_t m_CollisionFlag2{};
    uint32_t m_CollisionFlag3{};
    uint32_t m_Direction{};
    int32_t m_PosX{};
    int32_t m_PosY{};
    int32_t m_PosZ{};
    int32_t m_AngleDeg_x1000{};
    int32_t m_AngleXDeg_x1000{};
    int32_t m_AngleYDeg_x1000{};
    int32_t m_AngleSpeed{};
    int32_t m_ScaleX{};
    int32_t m_ScaleY{};
    int32_t m_ScaleZ{};
    int32_t m_ScaleSpeedX{};
    int32_t m_ScaleSpeedY{};
    int32_t m_ScaleSpeedZ{};
    int32_t m_TransformCenterX{};
    int32_t m_TransformCenterY{};
    int32_t m_DrawOffsetX{};
    int32_t m_DrawOffsetY{};
    int32_t m_BoundRate{};

    int32_t m_PushPosX{};
    int32_t m_PushPosY{};
    int32_t m_PushPosZ{};
    int32_t m_PushSpeedX{};
    int32_t m_PushSpeedY{};
    int32_t m_PushGravity{};
    int32_t m_PushAcceleration{};
    int32_t m_PushAccelerationZ{};
    int32_t m_PushInertia{};

    ZLINE m_ZLine{};
    ZLINE_LEVEL m_ZLevel{};
    float m_ZVal{};
    int32_t m_ZLineNearMultiplier{};

    FREDAudioHandle m_ActAudioHandle[0x10]{};

    int32_t m_OldPosX{};
    int32_t m_OldPosY{};
    int32_t m_CalcTmpPosX{};
    int32_t m_CalcTmpHitBackX{};
    int32_t m_ObjShakeXTime{};
    int32_t m_ObjShakeXDot{};
    int32_t m_Inertia{};
    int32_t m_InertiaTime{};
    int32_t m_SpeedX{};
    int32_t m_SpeedY{};
    int32_t m_Gravity{};
    int32_t m_Acceleration{};
    int32_t m_SpeedZ{};
    int32_t m_AccelerationZ{};
    int32_t m_SpeedTimeLimit{};
    int32_t m_SpeedRateX{};
    int32_t m_HitBackX{};
    int32_t m_HitBackXModoshi{};
    int32_t m_WallPushBack{};
    int32_t m_WallPushBackAPBefore{};

    int32_t m_PushColWidth{};
    int32_t m_PushColHeight{};
    int32_t m_PushColHeightLow{};
    int32_t m_PushColWidthFront{};

    uint32_t m_WallTouchTime{};
    int32_t m_FrameMoveX{};
    int32_t m_FrameMoveY{};
    int32_t m_FrameMoveYCalc{};
    int32_t m_FrameMoveZ{};
    int32_t m_NamerakaMoveX{};
    int32_t m_PassiveMoveX{};
    int32_t m_PassiveMoveY{};

    int32_t m_PushScreenOffsetFront{};
    int32_t m_PushScreenOffsetBack{};
    int32_t m_PushScreenOffsetTop{};
    int32_t m_PushScreenOffsetBottom{};

    OBJ_CBaseRelativePtr m_pAttackSlave[10]{};
    OBJ_CBaseRelativePtr m_pLockLinkObj{};
    OBJ_CBaseRelativePtr m_pAttackSlaveNewest{};
    int m_AttackSlaveCount{};
    int m_AttackObjectMax{};

    OBJ_CBaseRelativePtr m_pAttackMaster;
    OBJ_CBaseRelativePtr m_pHitBackMaster;

    int32_t m_HitPoint{};
    int32_t m_HitPointMax{};
    int32_t m_RecoverHitPoint{};
    int32_t m_HitPoint_x1000{};
    int32_t m_RecoverBlueHitPoint{};
    int32_t m_RecoverBlueHitPointTime{};
    int32_t m_DistortionLevel{};
    int32_t m_DistortionLevelSpeed{};

    uint8_t* m_pMultiBufferLarge{};
    uint8_t* m_pMultiBufferSmall{};

    AA_Flag<unsigned int> m_ValidInterruptFlag[4][5]{};
    CBBSFileAnalyzeData* m_pBBSFile{};
    uint8_t* m_TopAddr{};
    uint8_t* m_CurAddr{};
    uint8_t* m_CurActionTopAddr{};

    CXXBYTE<32> m_CellName{};
    int32_t m_CellTime{};
    int32_t m_CellTimeReserve{};
    int32_t m_CellTimeMax{};
    int32_t m_CellBeginCount{};
    int32_t m_CellNoStopCellNum{};

    uint8_t* m_TmpArgAddr{};
    CXXBYTE<32> m_PreActionName{};
    CXXBYTE<32> m_CurActionName{};
    CXXBYTE<32> m_ParentActionName{};

    OBJ_CBaseRelativePtr m_pControlObject{};

    bool m_IfReturnVal{};
    bool m_IsCellTimeStop{};
    bool m_CellTimeStopOnece{};

    CActionRequestInfo m_ActionRequestInfo{};
    CActionRequestInfo m_ActionRequestInfoReg{};

    CVoiceInfo m_VoiceInfo{};

    bool m_KowareDone{};
    int32_t m_KowareCur{};
    int32_t m_KowareMax{};
    int32_t m_KowareOnEnemyDamage{};
    int32_t m_KowareOnEnemyGuard{};
    int32_t m_KowareOnObjectHit{};
    int32_t m_KowareOnSousai{};
    int32_t m_KowareOnDamageCollision{};
    int32_t m_KowareTenmetsuTime{};
    int32_t m_KowareOnDamageOnly{};

    int32_t m_DebugActionChangeCount{};

    uint32_t m_HideFlag{};

    sSoundReq m_SoundReq{};

    CCreateArg m_CreateArg{};
    CCreateArg m_CreateArgFromParent{};

    int32_t m_FirstHitDamageHoseiRate{};
    bool m_KowareDispGauge{};
    int32_t m_KowareDispOffsetX{};
    int32_t m_KowareDispOffsetY{};
    int32_t m_KowareDispWidth{};

    ON_XXXX_INTRPT m_NaguruSignal{};
    int32_t m_L{};
    int32_t m_R{};
    int32_t m_T{};
    int32_t m_B{};

    uint32_t m_ScriptFlag{};
    unsigned char* m_ScriptGotoAddr{};
    unsigned char* m_GotoForLoopAddr{};
    int32_t m_GotoTimes{};

public:
    int ObjectInitializeOnActivate(const class CInitializeObjectExArg* arg);
    int OnDelete();
    void OnRollbackDelete();
    int ReleaseResource();

    void ObjectConstructor_ForObject();

    void ObjUnactivate();
    bool ObjIsUsing();
    void ActionChangeSignal();

    OBJ_CBase* GetControlObject(CO_TYPE type);

    bool IsTrgBtnX(int offsetTime, int btnID);

    bool ActionRequestForce(const CXXBYTE<32>& actionName);
    bool ActionRequestEx(const CXXBYTE<32>& actionName, unsigned int flag, OBJ_CBase* pEnemy,
                         CXXBYTE<32> label, unsigned int reqFlag);
    STOP_TYPE CheckForceStop();
    STOP_TYPE CheckForceStopSub();

    bool ControlPhase_FrameStep();
    virtual bool ControlPhase_PreFrameStep();
    bool ControlPhase_AfterFrameStep();
    virtual bool SubControlPhase_ScriptFrameStep(int count);

    bool IsAir() { return m_ActionFlag & OBJ_ACT_AIR || m_PosY > 0; }
    virtual bool IsDead();

    OBJ_CCharBase* GetMainPlayerBase(SIDE_ID side);

    int GetPosX();
    int GetPosY();
    int GetPosYCenter();
    int GetAngleY();

    int GetPushColW();
    int GetPushColH();
    int GetPushColHLow();

    uint32_t GetObjDir();

    void GetPushWorldRect(int* L, int* T, int* R, int* B);
    void GetPushWorldRectMax(int* L, int* T, int* R, int* B);
    void GetPushWorldRectForWorldClip(int* L, int* R);
    void GetPushScreenRect(int& L, int& T, int& R, int& B);

    bool IsActionRequested();
    void ScriptFrameStep();
    virtual void BBST_OnActionBegin(const CXXBYTE<32>& actName);

    virtual int DoInterrupt(ON_XXXX_INTRPT);
    virtual void OnActionBegin(const CXXBYTE<32>& actName);
    virtual void OnActionEnd();
    void OnCellBegin(const CXXBYTE<32>& name, int time);
    void OnCellChange(const CXXBYTE<32>& name, bool isUsePrimary);
    void ActionBegin(const CXXBYTE<32>& actName);
    void CellBegin(const CXXBYTE<32>& name, int time);
    void Goto(CXXBYTE<32> label);

private:
    uint8_t* ExecuteCellBeginToCellEnd(uint8_t* addr);
    uint8_t* ExecuteNestCommand(uint8_t* addr, int recCount, bool* jumpDone, bool bJumpCheckOnly, bool* pForceStop);
    int ExecuteFunctionBlock(const CXXBYTE<32>& funcName);
    int FuncCallBySwitchCaseTable(uint8_t* addr);
    uint8_t* GetSkipBeginEndAddr(uint8_t* addr);
    uint8_t* GetActionAddr(const CXXBYTE<32> actionName, int* pOutIndex);
    virtual const char* GetContextActionName(const CXXBYTE<32>& actName);

public:
    void FuncCall(const CXXBYTE<32>& funcName);

    void SetPosXRawinBattle(int val);

    void WorldCollision(int on);
    void ScreenCollision(int on);

    void CommonSE(const CXXBYTE<32>& name);
    void Voice(const CXXBYTE<16>& name);

    void InitCharName(const CXXBYTE<16>& name);

    void ResetAirDashCount();
    void ResetAirJumpCount();

    void RequestKoware(CO_TYPE obj);

    void ZLine(ZLINE line, ZLINE_LEVEL level);

    bool IsDamage()
    {
        return m_CollisionFlag & OBJ_CLSN_DAMAGE_IMPACT && m_CollisionFlag & OBJ_CLSN_DAMAGE;
    }
};
