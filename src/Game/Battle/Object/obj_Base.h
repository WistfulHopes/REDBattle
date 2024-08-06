#pragma once
#include <cstdint>
#include "obj_scriptinc.h"
#include "obj_BBScript.h"
#include <REDGameConstant.h>
#include "Base/Jon/TL_Jon.h"
#include "Common/tl_Filepack.h"
#include <AudioManager.h>

class OBJ_CBase;

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

class OBJ_CBaseRelativePtr
{
private:
	OBJ_CBase * m_Ptr; // 0x0
public:
	OBJ_CBaseRelativePtr() { InitOBJ_CBaseRelativePtr(); }
	void InitOBJ_CBaseRelativePtr() { m_Ptr = nullptr; }
	void SetPtr(OBJ_CBase * obj) { m_Ptr = obj; }
	void ClearPtr() { m_Ptr = nullptr; }
	OBJ_CBase * GetPtr() { return m_Ptr; }
	operator class OBJ_CBase *() { return m_Ptr; }
	OBJ_CBaseRelativePtr & operator=(OBJ_CBaseRelativePtr ptr) { m_Ptr = ptr.m_Ptr; } 
	OBJ_CBaseRelativePtr & operator=(OBJ_CBase * obj) { m_Ptr = obj; }
};

class CCreateArg
{
public:
	CCreateArg();
	void CCreateArgInit();
	CXXBYTE<32> m_CreateArg_SocketName; // 0x0
	int32_t m_CreateArg_Angle; // 0x20
	int32_t m_CreateArg_AngleY; // 0x24
	int32_t m_CreateArg_OffsetPosX; // 0x28
	int32_t m_CreateArg_OffsetPosY; // 0x2C
	int32_t m_CreateArg_OffsetPosZ; // 0x30
	int32_t m_CreateArg_ScaleX; // 0x34
	int32_t m_CreateArg_ScaleY; // 0x38
	int32_t m_CreateArg_ScaleZ; // 0x3C
	int32_t m_CreateArg_Hikitsugi0; // 0x40
	int32_t m_CreateArg_Hikitsugi1; // 0x44
	uint32_t m_CreateArg_HkrColor; // 0x48
	uint32_t m_CreateArg_MltColor; // 0x4C
	int32_t m_CreateArg_TransPriority; // 0x50
	PTDIR m_CreateArg_Direction; // 0x54
	bool m_CreateArg_SocketUse; // 0x55
	bool m_CreateArg_SocketWithRot; // 0x56
	bool m_CreateArg_NoAssert; // 0x57
	CO_TYPE m_CreateArg_SocketOwner; // 0x58
	bool m_CreateArg_LinkMaterialParticle; // 0x5C
	bool m_CreateArg_ParticleUnuseMatInstance; // 0x5D
	uint32_t m_CreateArg_Delay; // 0x60
	int32_t m_CreateArg_PointLightSide; // 0x64
	int32_t m_CreateArg_PointLightMember; // 0x68
};

class OBJ_CBase
{
private:
    int ObjBaseSyncBegin;
public:
    uint32_t m_AtkPriority;
    ACTV_STATE m_ActiveState;
    uint32_t m_ObjectSortPriority;
    bool m_IsPlayerObj;
    uint32_t m_UniqID;
    uint32_t m_ObjTimer;
    uint32_t m_BuruBuruPartsTime;
    bool m_IsDirty;
    uint32_t m_WatchedCount;
    uint32_t m_ActionChangeID;
    int32_t m_TmpWork;
    int32_t m_ObjectPriority;
    RS_RENDER_STAGE m_ObjectRenderStage;
    int32_t m_ObjectGeneration;
    SIDE_ID m_SideID;
    SIDE_ID m_FixedSideID;
    ECharaID m_CharaID;
    ECharaID m_FixedCharaID;
    EMemberID m_MemberID;
    EMemberID m_FixedMemberID;
    EBattleScript m_ScriptType;
    AA_CCollision_JON m_ClsnAnalyzer;
    AA_Filepack_FPAC m_ColPack;

    uint32_t m_ObjFlag;
    uint32_t m_ObjFlag2;
    uint32_t m_ObjFlag3;
    uint32_t m_ObjFlag4;
    uint32_t m_ObjFlag5;
    uint32_t m_ActionKeepFlag;
    uint32_t m_ObjSignal;
    uint32_t m_ActionTime;
    uint32_t m_ActionTimeMax;
    uint32_t m_ActionTimeNoStop;
    uint32_t m_OnIdlingtime;

    int32_t m_CommonActionMark;
    int32_t m_TmpReg;
    int32_t m_ActReg0;
    int32_t m_ActReg1;
    int32_t m_ActReg2;
    int32_t m_ActReg3;
    int32_t m_ActReg4;
    int32_t m_ActReg5;
    int32_t m_ActReg6;
    int32_t m_ActReg7;
    int32_t m_ObjReg0;
    int32_t m_ObjReg1;
    int32_t m_ObjReg2;
    int32_t m_ObjReg3;
    int32_t m_ObjReg4;
    int32_t m_ObjReg5;
    int32_t m_ObjReg6;
    int32_t m_ObjReg7;
    int32_t m_PgActReg0;
    int32_t m_PgActReg1;
    int32_t m_PgActReg2;
    int32_t m_PgActReg3;
    int32_t m_PgObjReg0;
    int32_t m_PgObjReg1;
    int32_t m_PgObjReg2;
    int32_t m_PgObjReg3;
    int32_t m_SoundActReg0;
    int32_t m_SoundActReg1;
    int32_t m_SoundActReg2;
    int32_t m_SoundActReg3;
    int32_t m_SoundObjReg0;
    int32_t m_SoundObjReg1;
    int32_t m_SoundObjReg2;
    int32_t m_SoundObjReg3;

    int32_t m_CPUVal0;
    int32_t m_CPUVal1;
    int32_t m_CPUVal2;
    int32_t m_CPUVal3;
    int32_t m_CPUVal4;
    int32_t m_CPUVal5;
    int32_t m_CPUVal6;
    int32_t m_CPUVal7;

    uint32_t m_HitStopTime;
    bool m_bSlowHitstop;
    uint32_t m_HitStopTimeMax;
    uint32_t m_HitStopTimeBySousai;
    uint32_t m_HitStopTimeReq;
    uint32_t m_HitStopTimeReqLevel;
    bool m_bHitStopTimeReqSlow;

    int32_t m_UltimateReq_StopTime;
    int32_t m_UltimateReq_StopTimeSelf;
    uint32_t m_UltimateReq_Flag;

    BG_TYPE m_BGType;
    int32_t m_LandingHeight;

    OBJ_CBaseRelativePtr m_pParentPly;
    OBJ_CBaseRelativePtr m_pParentObj;
    OBJ_CBaseRelativePtr m_pTargetObj;
    OBJ_CBaseRelativePtr m_pLinkObject_PushCollision;
    OBJ_CBaseRelativePtr m_pLinkObject_Angle;
    OBJ_CBaseRelativePtr m_pLinkObject_Position;
    OBJ_CBaseRelativePtr m_pLinkObject_Direction;
    OBJ_CBaseRelativePtr m_pLinkObject_DamageToEliminate;
    OBJ_CBaseRelativePtr m_pLinkObject_ChangeToEliminate;
    OBJ_CBaseRelativePtr m_pLinkObject_Stop;
    OBJ_CBaseRelativePtr m_pLinkObject_PositionCenter;
    OBJ_CBaseRelativePtr m_pLinkObject_Scale;
    OBJ_CBaseRelativePtr m_pLinkObject_Z;
    OBJ_CBaseRelativePtr m_pLinkObject_Collision;
    OBJ_CBaseRelativePtr m_pLinkObject_Color;
    OBJ_CBaseRelativePtr m_pLinkObject_MaterialSet;
    OBJ_CBaseRelativePtr m_pLinkObject_CmnMaterialParam;
    OBJ_CBaseRelativePtr m_pPrevChild;
    OBJ_CBaseRelativePtr m_pTrialObj;
    OBJ_CBaseRelativePtr m_pChildStack[9];

    uint32_t m_ActionFlag;
    uint32_t m_ActionFlag2;
    uint32_t m_CollisionFlag;
    uint32_t m_CollisionFlag2;
    uint32_t m_CollisionFlag3;
    uint32_t m_Direction;
    uint32_t m_PosX;
    uint32_t m_PosY;
    uint32_t m_PosZ;
    uint32_t m_AngleDeg_x1000;
    uint32_t m_AngleXDeg_x1000;
    uint32_t m_AngleYDeg_x1000;
    uint32_t m_AngleSpeed;
    uint32_t m_ScaleX;
    uint32_t m_ScaleY;
    uint32_t m_ScaleZ;
    uint32_t m_ScaleSpeedX;
    uint32_t m_ScaleSpeedY;
    uint32_t m_ScaleSpeedZ;
    uint32_t m_TransformCenterX;
    uint32_t m_TransformCenterY;
    uint32_t m_DrawOffsetX;
    uint32_t m_DrawOffsetY;
    uint32_t m_BoundRate;

    uint32_t m_PushPosX;
    uint32_t m_PushPosY;
    uint32_t m_PushPosZ;
    uint32_t m_PushSpeedX;
    uint32_t m_PushSpeedY;
    uint32_t m_PushGravity;
    uint32_t m_PushAcceleration;
    uint32_t m_PushAccelerationZ;
    uint32_t m_PushInertia;

    ZLINE m_ZLine;
    ZLINE_LEVEL m_ZLevel;
    float m_ZVal;
    int32_t m_ZLineNearMultiplier;

    FREDAudioHandle m_ActAudioHandle[0x10];

    int32_t m_OldPosX;
    int32_t m_OldPosY;
    int32_t m_CalcTmpPosX;
    int32_t m_CalcTmpHitBackX;
    int32_t m_ObjShakeXTime;
    int32_t m_ObjShakeXDot;
    int32_t m_Inertia;
    int32_t m_InertiaTime;
    int32_t m_SpeedX;
    int32_t m_SpeedY;
    int32_t m_Gravity;
    int32_t m_Acceleration;
    int32_t m_SpeedZ;
    int32_t m_AccelerationZ;
    int32_t m_SpeedTimeLimit;
    int32_t m_SpeedRateX;
    int32_t m_HitBackX;
    int32_t m_HitBackXModoshi;
    int32_t m_WallPushBack;
    int32_t m_WallPushBackAPBefore;

    int32_t m_PushColWidth;
    int32_t m_PushColHeight;
    int32_t m_PushColHeightLow;
    int32_t m_PushColWidthFront;

    uint32_t m_WallTouchTime;
    int32_t m_FrameMoveX;
    int32_t m_FrameMoveY;
    int32_t m_FrameMoveYCalc;
    int32_t m_FrameMoveZ;
    int32_t m_NamerakaMoveX;
    int32_t m_PassiveMoveX;
    int32_t m_PassiveMoveY;

    CXXBYTE<32> m_PreActionName;
    CXXBYTE<32> m_CurActionName;
    CXXBYTE<32> m_ParentActionName;
    CActionRequestInfo m_ActionRequestInfo;
    CActionRequestInfo m_ActionRequestInfoReg;

    CCreateArg m_CreateArg;
    CCreateArg m_CreateArgFromParent;

public:
    int ObjectInitializeOnActivate(const class CInitializeObjectExArg * arg);
    int OnDelete();
    void OnRollbackDelete();
    int ReleaseResource();

    void ObjectConstructor_ForObject();
	
    bool ActionRequestForce(const class CXXBYTE<32>& actionName);
    bool ActionRequestEx(const class CXXBYTE<32> & actionName, unsigned int flag, class OBJ_CBase * pEnemy, class CXXBYTE<32> label, unsigned int reqFlag);
};