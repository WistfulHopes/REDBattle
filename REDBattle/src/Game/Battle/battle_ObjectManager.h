#pragma once
#include "battle_TeamManager.h"
#include "BattleEventManager.h"
#include "Game/System/game_key_flag.h"
#include "Object/obj_BBScript.h"
#include "BattlePlayerResult.h"
#include "Game/Battle/Object/obj_BaseCommon.h"
#include "Game/System/game_key.h"
#include "BattleRecord.h"

template <int V1, int V2>
class CMultiBuffer 
{
    struct MEM 
    {
        unsigned char buffer[V1];
        MEM* pPrev;
        MEM* pNext;

		MEM() 
		{
			pPrev = nullptr;
			pNext = nullptr;
		}
    };
private:
	MEM * m_pEmptyChain; // 0x0
	MEM m_Memory[V2]; // 0x8
public:
	CMultiBuffer()
	{
		m_pEmptyChain = nullptr;
	}
	void Reset() 
	{
		memset(m_Memory, 0, sizeof(m_Memory));
		m_pEmptyChain = m_Memory;

		for (int i = 0; i < V2; i++)
		{
			if (i == 0)
			{
				m_Memory[i].pPrev = nullptr;
			}
			else 
			{
				m_Memory[i].pPrev = &m_Memory[i - 1];
			}
			if (i == V2 - 1)
			{
				m_Memory[i].pNext = nullptr;
			}
			else 
			{
				m_Memory[i].pNext = &m_Memory[i + 1];
			}
		}
	}
	void * Reserve(bool);
	void Release(void * buffer)
	{
		m_pEmptyChain->pPrev = (MEM*)buffer;
	}
};

class CInitializeObjectExArg
{
public:
	CInitializeObjectExArg()
	{
		actName = "";
		argparent = nullptr;
	}
	CXXBYTE<32> actName; // 0x0
	OBJ_CBase * argparent; // 0x20
	int32_t flag; // 0x28
	DIR_FLAG dir; // 0x2C
	POS_TYPE exPoint; // 0x2D
	SIDE_ID argsideID; // 0x2E
	SIDE_ID argFixedSideID; // 0x2F
	EMemberID memberID; // 0x30
	EMemberID fixedMemberID; // 0x31
	bool isPlayer; // 0x32
	bool doScriptStep; // 0x33
	bool bIsCommonObject; // 0x34
};

class FForceEffectInfo
{
public:
	AA_Vector3 Position; // 0x0
	AA_Vector3 Direction; // 0xC
	float InnerForce; // 0x18
	float OuterForce; // 0x1C
	float Radius; // 0x20
	float InnerAngularForce; // 0x24
	float OuterAngularForce; // 0x28
	FForceEffectInfo() {}
};

enum EScriptData
{
	ScriptData_Body = 0,
	ScriptData_Effect = 1,
	ScriptData_MAX = 2,
};

enum BOMFLG
{
    BOMFLG_KEY_READY = 1,
    BOMFLG_ULTIMATE_EFFECT = 2,
    BOMFLG_NO_SCREEN_COLLISION = 4,
    BOMFLG_SOME_BODY_DIE = 8,
    BOMFLG_WINNER_CAMERA_STOP = 16,
    BOMFLG_FADE_OUT_OBJ_FOUND = 32,
    BOMFLG_ALL_WORLD_COLLISION_OFF = 64,
    BOMFLG_DANGER_TIME_DONE = 128,
    BOMFLG_COCKPIT_HIDE = 256,
    BOMFLG_ALL_WORLD_COLLISION_OFF_FOR_1ST_INIT = 512,
    BOMFLG_BATTLE_RESULT_SCREEN = 1024,
    BOMFLG_FIRST_ATTACK_DONE = 2048,
    BOMFLG_SHIN_SOUSAI_DONE = 4096,
    BOMFLG_TUTORIAL_CAMERA_MODE = 4194304,
    BOMFLG_WORLDSIDE_BREAK_L = 8388608,
    BOMFLG_WORLDSIDE_BREAK_R = 16777216,
    BOMFLG_DUST_SPEED_CTRL = 33554432,
    BOMFLG_SLOWTIME_CTRL = 67108864,
};
enum DragonBall
{
    DRAGON_BALL_STAR_1 = 1,
    DRAGON_BALL_STAR_2 = 2,
    DRAGON_BALL_STAR_3 = 4,
    DRAGON_BALL_STAR_4 = 8,
    DRAGON_BALL_STAR_5 = 16,
    DRAGON_BALL_STAR_6 = 32,
    DRAGON_BALL_STAR_7 = 64,
    DRAGON_BALL_INVALID = 128,
    DRAGON_BALL_ALL = 127,
};
enum ShenlongWish
{
    SHENLONG_WISH_RECOVER_HP = 0,
    SHENLONG_WISH_RESURRECTION = 1,
    SHENLONG_WISH_IMMORTALITY = 2,
    SHENLONG_WISH_ULTIMATEPOWER = 3,
    SHENLONG_WISH_NUM = 4,
    SHENLONG_WISH_INVALID = 255,
};
enum INPUT_DELAY_TYPE
{
    INP_DELAY_NORMAL = 0,
    INP_DELAY_RANDOM_5F = 1,
    INP_DELAY_RANDOM_10F = 2,
};
enum WORLDSID_EBREAK_PATTERN
{
    WORLDSID_EBREAK_PATTERN_DUST_SUCCESS = 0,
    WORLDSID_EBREAK_PATTERN_DUST_FAILURE = 1,
    WORLDSID_EBREAK_PATTERN_SLIDE = 2,
    WORLDSID_EBREAK_PATTERN_UP = 3,
    WORLDSID_EBREAK_PATTERN_DOWN = 4,
    WORLDSID_EBREAK_PATTERN_DEFAULT = 5,
};
namespace ENextPlayerEntry
{
    enum Type {
        FromDestructionFinish = 0,
        FromFuttobiFinish = 1,
        FromFuttobiBGTransFinish = 2,
        FromNormalFinish = 3,
    };
};

class BATTLE_CObjectManager 
{
public:
    BATTLE_CObjectManager();
    ~BATTLE_CObjectManager() {}
private:
    void BOM_ConstructorSub();
public:
    void Release();
private:
	BATTLE_TeamManager m_TeamManager[2]; // 0x0
public:
	BATTLE_TeamManager * GetTeamManager(SIDE_ID side) { return &m_TeamManager[side]; }
	void UpdateTeamTrainingMode();
	int32_t BOM_MatchOneceInitialize(bool bIs2ndCall);
	int32_t BOM_RoundAndEasyResetInitialize(bool use2ndInitialize);
	void BOM_ForceUnactivateObjects();
	uint32_t m_BOMFlag; // 0x2C0
	void AddBOMFlag(BOMFLG);
	void AddBOMFlag(uint32_t);
	void DelBOMFlag(BOMFLG);
	void DelBOMFlag(uint32_t);
	bool CheckBOMFlag(BOMFLG);
	bool CheckBOMFlag(uint32_t);
	void ResetOnRoundStart(bool);
	FINISH_BG m_FinishBG; // 0x2C4
	int32_t m_FinishAtk; // 0x2C8
	bool m_FinishAssistAtk; // 0x2CC
private:
	void ExecuteObjectManagerEvent(const BOMEventInfo * pEvent);
public:
	void ExecuteObjectManagerEvent(BattleEventManager * pBEM);
	WORLDSID_EBREAK_PATTERN m_WSBPattern; // 0x2D0
	bool IsEnableAttackCheck();
private:
	void UpdateChangeNextBGLayer();
	void BOMEventDestructionFinishStart(SIDE_ID);
	void BOMEventDramaticFinishStart(SIDE_ID);
	unsigned char m_DragonBall; // 0x2D4
	unsigned char m_Wish; // 0x2D5
	bool m_bARendaComplete; // 0x2D6
	SIDE_ID m_lastGainedDBSide; // 0x2D8
	OBJ_CBaseRelativePtr m_pShenlongSystem; // 0x2E0
	TENSION_ADD_ACTION m_lastTensionAddAction; // 0x2E8
	SIDE_ID m_CallShenlongSide; // 0x2EC
private:
	void BOMEventShenlongSystemStart();
	void GetDemoCharacters(SIDE_ID, OBJ_CCharBase * *, OBJ_CCharBase * *, OBJ_CCharBase * *);
	void BomEventEntryChara(const BOMEventInfo *);
	bool CheckEntryDramaticAction(OBJ_CCharBase *, OBJ_CCharBase *);
	void BomEventReset(bool, bool);
public:
	bool IsDemoReady();
	OBJ_CBase * ActivateObject(const CInitializeObjectExArg *);
private:
	CBBSFile m_BBSFile[2][7];
	CBBSFileAnalyzeData m_BBSFileAnalyzeData[2][7]; // 0x2F0
public:
	static int32_t GetPlayerIndexWithCommon(SIDE_ID, EMemberID);
	CBBSFileAnalyzeData * GetScriptData(SIDE_ID side, EMemberID member, EScriptData script)
	{
		auto index = side * 3 + member;
		switch (script)
		{
			case ScriptData_Body:
				return &m_BBSFileAnalyzeData[0][index];
			case ScriptData_Effect:
				return &m_BBSFileAnalyzeData[1][index];
			default:
				return nullptr;
		}
	}
	CBBSFileAnalyzeData * GetCommonScriptData(EScriptData script)
	{
		switch (script)
		{
			case ScriptData_Body:
				return &m_BBSFileAnalyzeData[0][6];
			case ScriptData_Effect:
				return &m_BBSFileAnalyzeData[1][6];
			default:
				return nullptr;
		}
	}
	OBJ_CBase * GetNoActiveObject(const OBJ_CBase *);
	OBJ_CBase * SearchLowPriorityObject(const OBJ_CBase *);
	static int32_t GetPlayerIndex(SIDE_ID, EMemberID);
	OBJ_CCharBase * GetPlayer(SIDE_ID side, EMemberID memberID) { return &m_CharVector[side * 3 + memberID]; }
	OBJ_CCharBase * GetPlayerObjFromIndex(int32_t);
	OBJ_CCharBase * GetMainPlayer(SIDE_ID);
	OBJ_CCharBase * GetSubMember(SIDE_ID, ESubMemberID);
	OBJ_CBase * GetNextActiveObject(int32_t *);
	OBJ_CBase * GetNextSortedActiveObject(int32_t *);
	OBJ_CBase * GetNextSortedActiveObjectWithCreateChokugo(int32_t *);
	OBJ_CBase * GetNextSortedActiveObjectWithCreateChokugo_Inverse(int32_t *);
	OBJ_CBase * GetNextObject(int32_t *);
	OBJ_CBase * GetNextObjectAndChar(int32_t *);
	OBJ_CBase * GetNextSortedActiveObject_Inverse(int32_t *);
	OBJ_CBase * GetNextSortedActiveObjectEx(int32_t *);
	OBJ_CBase * GetNextSortedActiveObject_InverseEx(int32_t *);
	void AllActiveCheck();
	void WorldStopUpdate();
	void DeleteCheck();
	OBJ_CBase * SearchObject(const char *, SIDE_ID, EMemberID, int32_t *, bool);
	int32_t GetObjectIndex(const OBJ_CBase *);
	int32_t m_ActiveObjectCount; // 0x8A0
	int32_t m_CreateChokugoObjectCount; // 0x8A4
	int32_t m_NoActiveObjectCount; // 0x8A8
	int32_t m_EtcActiveObjectCount; // 0x8AC
	int32_t m_ForceDeleteCount; // 0x8B0
private:
    static const uint32_t CHARA_OBJECT_NUM = 6;
    static const uint32_t OBJECT_NUM = 101;
    static const uint32_t TOTAL_OBJECT_NUM = CHARA_OBJECT_NUM + OBJECT_NUM;
	OBJ_CBase * m_ObjPtrVector[TOTAL_OBJECT_NUM]; // 0x8B8
	OBJ_CBase * m_SortedObjPtrVector[TOTAL_OBJECT_NUM]; // 0xC10
	OBJ_CBase * m_CreateChokugoObjPtrVector[TOTAL_OBJECT_NUM]; // 0xF68
	uint32_t m_UsesObjPtrVectorNum; // 0x12C0
public:
	void ControlBattleObject();
	void DrawBattleObject();
	void DrawBattleObjectIgnorePause();
	void DrawBattleObjectDebugInfo();
	void DeleteUnnecessaryBattleObject();
	void UnlockLockFlag();
private:
	void DrawBattleObject_PlayerOutIcon();
	bool m_bDrawPlayerOutIcon; // 0x12C4
	bool m_bForceDrawPlayerOutIcon; // 0x12C5
	OBJ_CBaseRelativePtr m_OutIconSettingObj; // 0x12C8
public:
	void SetDrawPlayerOutIcon(bool, OBJ_CBase *);
	void ResetDrawPlayerOutIcon(bool, OBJ_CBase *);
	void SetForceDrawPlayerOutIcon(bool);
private:
	void ControlBattleObject_KeyRenewal();
	void ControlBattleObject_Move();
	void ControlBattleObject_MoveSub_MoveExe();
	void ControlBattleObject_MoveSub_WorldClip();
	void ControlBattleObject_MoveSub_ForceEffect();
	void ControlBattleObject_UpdateForceEffect();
	void ControlBattleObject_EtcEffect();
	void ControlBattleObject_HitCollision();
	enum HCSSEQ : int32_t
	{
		HCSSEQ_EASY_SOUSAI = 0,
		HCSSEQ_ATTACK_VS_DAMAGE = 1,
		HCSSEQ_SOUSAI = 2,
		HCSSEQ_Z_REVERSAL = 3,
	};
	bool ControlBattleObject_HitCollisionSub(BATTLE_CObjectManager::HCSSEQ);
	void ControlBattleObject_ZLine();
public:
	uint32_t GenerateUniqID();
	void ResetUniqIDGenerator();
	int32_t GetAtkHitCount();
	void SetAtkHitCount(int32_t);
	uint32_t GetActionChangeCount() { return m_ActionChangeCount; }
	void SetActionChangeCount(uint32_t count) { m_ActionChangeCount = count; }
	int32_t m_AttackHitUniqIDGen; // 0x12D0
private:
	uint32_t m_UniqIDGen; // 0x12D4
	int32_t m_AtkHitCount; // 0x12D8
	uint32_t m_ActionChangeCount; // 0x12DC
public:
	void ExeWorldStop();
	void CountDownWorldStop();
	bool m_WorldBlacker; // 0x12E0
	bool m_bBackGroundStop; // 0x12E1
	int32_t m_FinishStopCount; // 0x12E4
	int32_t m_FinishStopCountMax; // 0x12E8
	int32_t m_OverrideFinishStopTime[2]; // 0x12EC
	int32_t m_OverrideSlashUITime[2]; // 0x12F4
	void PrepareReleaseWorldStopper();
	bool IsWorldStop();
	bool IsWorldStopWithStopBG();
	void SetFinishStopCount(int32_t);
	void UpdateFinishStopCount();
	bool IsFinishStop();
	bool IsSpecialFinishDoing();
	bool IsSpecialFinishFuttobi();
	bool IsSpecialFinishDestruction();
	bool IsSpecialFinishFuttobiBGTrans();
	bool IsSpecialFinishDramatic();
	bool IsBGTransitionStartDoing();
	bool IsBGTransitionFinishDoing();
	void UpdateScreenTarget();
private:
	static const int32_t FORCE_EFFECT_NUM; // 0xFFFFFFFFFFFFFFFF
	FForceEffectInfo m_ForceEffectInfo[2]; // 0x12FC
	int32_t m_ActiveForceEffectNum; // 0x1354
public:
	FForceEffectInfo & GetEmptyForceEffectInfo();
	int32_t GetForceEffectNum();
	void ResetForceEffectInfo();
	int32_t CalculateCPULevelNoLimit(SIDE_ID);
	int32_t CalculateCPULevel(SIDE_ID);
	OBJ_CBaseRelativePtr m_WorldStopper; // 0x1358
	int32_t m_WorldStopTimer; // 0x1360
	int32_t m_WorldStopTimerSelf; // 0x1364
	int32_t m_WorldStopTimerMax; // 0x1368
	int32_t m_WorldStopTimerSelfMax; // 0x136C
	int32_t m_RoundTimer; // 0x1370
	uint32_t m_DrawTimer; // 0x1374
	int32_t GetDrawTimer();
	void DebugAttakInfoRenew(OBJ_CBase *);
	void DebugAttakInfoAdd(const char *, ...);
	void DebugAttakInfoDisp();
	void ScriptAnalyze();
	void ScriptAnalyzeByTmp();
	CMultiBuffer<4,4> m_MultiBufferLarge; // 0x1378
	CMultiBuffer<4,4> m_MultiBufferSmall; // 0x13E0
	int32_t m_BurstVal[2]; // 0x1448
	int32_t m_MatchStaticValue0[2]; // 0x1450
	int32_t m_MatchStaticValue1[2]; // 0x1458
	int32_t m_Rakusyo[2]; // 0x1460
	int32_t m_YogoreLevel[2]; // 0x1468
	int32_t m_PreBurstVal[2]; // 0x1470
	int32_t m_PreMatchStaticValue0[2]; // 0x1478
	int32_t m_PreMatchStaticValue1[2]; // 0x1480
	int32_t m_PreRakusyo[2]; // 0x1488
	int32_t m_PreYogoreLevel[2]; // 0x1490
	void BackUpMatchStaticValue();
private:
	SIDE_ID m_WinnerSideID; // 0x14D0
	struct FCommonPawn;
	SIDE_ID m_IchigekiBGMRequestSideID; // 0x1598
	CXXBYTE<32> m_IchigekiBGMName; // 0x159C
	void ResetWinnerPlayerID();
	void SetWinnerSideID(SIDE_ID);
	SIDE_ID GetWinnerSideID();
	void RequestFinishCamera(ROUND_RESULT);
	void RequestBattleStartCamera();
public:
	bool IsBattleStartCameraExist();
	bool IsRequestIchigekiBGM();
	SIDE_ID GetIchigekiBGMSideID();
	const char * GetIchigekiBGMName();
	void ResetIchigekiBGM();
	void RequestIchigekiBGM(SIDE_ID, const CXXBYTE<32> &);
	OBJ_CCharBase * GetWinnerObj();
	bool m_IsForceReload; // 0x15BC
	void SetHPGaugeColor(int32_t, uint32_t, uint32_t);
	void SetTensGaugeColor(int32_t, uint32_t, uint32_t);
	bool IsPlayingCutScene();
	void TransferAirActionCount(OBJ_CCharBase* dst, OBJ_CCharBase* src);
	int32_t GetStartupPositionXBase(SIDE_ID side, EMemberID memberId);
	void TransferMemberIndexInTrainingMode();
	void SetStartupPositionInTrainingMode();
	void SetInitVitalSettingInTrainingMode();
private:
	float m_FadeOut01; // 0x15C0
	float m_BGFadeInSpeed; // 0x15C4
	float m_BGFadeOutSpeed; // 0x15C8
	float m_BGFadeAlpha; // 0x15CC
	bool m_RequestFadeOut; // 0x15D0
	bool m_bForceBGHide; // 0x15D1
	uint32_t m_DisplayFadeColor; // 0x15D4
	float m_DisplayFadeAdd; // 0x15D8
	float m_DisplayFade01; // 0x15DC
	int32_t m_DisplayFadeRenderStage; // 0x15E0
	bool m_bRequestDisplayFade; // 0x15E4
	bool m_bDrawDisplayFade; // 0x15E5
public:
	CFloatWithTimer m_BGSaturation; // 0x15E8
	void SetBGFadeInSpeed(float);
	void SetBGFadeOutSpeed(float);
	void SetBGFadeAlpha(float);
	void SetDefaultBGFadeParam();
	float GetCurrentBGFade();
	void RequestForceBGHide(bool);
	void RequestDisplayFadeOut(uint32_t, int32_t, int32_t);
	void RequestDisplayFadeIn(int32_t);
private:
	void UpdateDisplayFade();
	void DrawDisplayFade();
	void UpdateBGParam();
	void UpdateParameterForREDCamera_Battle();
public:
	AA_EasyHash<CXXBYTE<32>,200,800> m_CommonActionHash; // 0x1600
	int32_t m_ShinSousaiTimer; // 0x36D4
	int32_t m_DiffusionFilter2LevelMax; // 0x36D8
	int32_t m_DiffusionFilter2SaturationMin; // 0x36DC
	int32_t m_FinishSlowTime; // 0x36E0
	int32_t m_MotionBlurAmount; // 0x36E4
	struct SEventData
    {
        int32_t MessageTime; // 0x0
        bool bMessageSet; // 0x4
        OBJ_CBase * pManagerObj; // 0x8
        OBJ_CBase * pSpeakChara[4]; // 0x10
        int32_t LipSyncFrame; // 0x30
        bool bLipSyncFlag; // 0x34
        bool bEnd; // 0x35
        OBJ_CBase * pExChara[4]; // 0x38
        CXXBYTE<16> ExCharaID[4]; // 0x58
        OBJ_CBase * pLoadWaitObj; // 0x98
        void Update();
        SEventData() {}
    };
	SEventData m_EventData; // 0x36E8
	void InitializeEventData();
	void UpdateForEvent();
	bool m_OnlineTraining_IsSwitch; // 0x3788
	int32_t m_OnlineTraining_IsSwitchHold[2]; // 0x378C
	int32_t m_OnlineTraining_SwitchCoolTime; // 0x3794
	bool m_OnlineTraining_IsResetDone; // 0x3798
	bool m_OnlineTraining_StartSideFrip; // 0x3799
	MAAI_TYPE m_OnlineTraining_StartPos; // 0x379C
	uint32_t m_OnlineTraining_Wins[2]; // 0x37A0
private:
	CBattleInputAnalyzer m_BattleInputAnalyzer[6]; // 0x37A8
public:
	CBattleInputAnalyzer * BattleInputAnalyzer(SIDE_ID, EMemberID);
	bool IsAC15System();
	void CheckBattleFastFowardEndAC15();
private:
	bool CheckFastFowardInputAC15();
	int32_t m_StartInputTimeAC15; // 0x3A9C
public:
	ECharaID m_LastLoadedCharID[2]; // 0x3AA0
	int32_t m_EnvStylishDefence; // 0x3AA8
	int32_t m_EnvStylishTension; // 0x3AAC
	int32_t m_EnvStylishBurst; // 0x3AB0
	int32_t m_EnvDokiDokiStop; // 0x3AB4
	int32_t m_EnvDokiDokiStopHikitsuke; // 0x3AB8
	int32_t m_EnvDokiDokiStopXRangeMin; // 0x3ABC
	int32_t m_EnvDokiDokiStopXRangeMax; // 0x3AC0
	int32_t m_EnvDokiDokiStopYRangeMax; // 0x3AC4
	int32_t m_EnvDokiDokiStopHassei; // 0x3AC8
	int32_t m_EnvDokiDokiStopFinishStop; // 0x3ACC
	int32_t m_DokiDokiStopByDokiDokiKill; // 0x3AD0
	int32_t m_DokiDokiStopIgnoreTime; // 0x3AD4
	bool m_bMOMItemDesc; // 0x3AD8
	bool m_bMOMLifeDesc; // 0x3AD9
	int32_t m_TrialBossHP; // 0x3ADC
	int32_t m_TrialBossHPMax; // 0x3AE0
	int32_t m_TrialBossBarrier; // 0x3AE4
	int32_t m_TrialExVal0; // 0x3AE8
	int32_t m_TrialExVal1; // 0x3AEC
	int32_t m_TrialExVal2; // 0x3AF0
	int32_t m_TrialExVal3; // 0x3AF4
	uint32_t UpdateBattleCheckSum();
	uint32_t m_BattleCheckSumTimeCount; // 0x3AF8
	uint32_t m_BattleCheckSum; // 0x3AFC
	uint32_t m_BattleCheckSumErrorFound; // 0x3B00
	unsigned char m_BattleCheckSumErrorFoundList[2]; // 0x3B04
	uint32_t m_BOMRandomSeed; // 0x3B08
	HANDICAP_TYPE m_BattleHandiCap[2]; // 0x3B0C
	int32_t m_YogoreLv[3][2]; // 0x3B14
	void ResetYogoreLv();
private:
	unsigned char m_ComboCameraInfo[10][2]; // 0x3B2C
public:
	unsigned char GetComboCameraInfo(int32_t, int32_t);
	void SetComboCameraInfo(int32_t, int32_t, unsigned char);
	void ResetComboCameraInfo(int32_t);
	int32_t m_EventVsVoiceRandomIndex; // 0x3B40
	int32_t m_EventVsVoiceNum; // 0x3B44
	int32_t m_EntryEventRandomValue[3][2]; // 0x3B48
	bool IsUseNewRandomInEntryEvent();
private:
	INPUT_DELAY_TYPE m_delayType; // 0x3B60
	int32_t m_delayReserve; // 0x3B64
public:
	void SetInputDelayType(INPUT_DELAY_TYPE);
	int32_t GetInputDelayReserve();
	void SetInputDelayReserve(int32_t);
private:
	CBattleRecord m_BattleRecord; // 0x3B68
public:
	CBattleRecord * GetBattleRecord();
	void AddBattleRecord(SIDE_ID, BATTLE_RECORD_TYPE, unsigned short);
	void SetBattleRecord(SIDE_ID, BATTLE_RECORD_TYPE, unsigned short);
	BATTLE_RECORD_TYPE GetRecordType(const CAtkParam *, SIDE_ID, HIT_TYPE, GUARD_DAN);
private:
	int32_t m_DustSpeedX; // 0x3C50
	int32_t m_DustSpeedY; // 0x3C54
public:
	int32_t GetDustSpeedX();
	void SetDustSpeedX(int32_t);
	int32_t GetDustSpeedY();
	void SetDustSpeedY(int32_t);
private:
	float m_ParticleSpeed; // 0x3C58
	float m_LinkParticleSpeed; // 0x3C5C
	float m_LinkParticleSpeed_IgnoreSlow; // 0x3C60
	int32_t m_ExternalParticleSpeedCounter; // 0x3C64
	float m_ExternalParticleSpeed; // 0x3C68
public:
	float GetParticleSpeed();
	float GetLinkParticleSpeed();
	float GetLinkParticleSpeed_IgnoreSlow();
	void SetExternalParticleSpeed(int32_t, float);
	float GetExternalParticleSpeed();
private:
	int32_t m_TrainingHighJumpCheck[3][2]; // 0x3C6C
	bool bExecWSBFlag; // 0x3C84
	int32_t ExecWSBWaitCounter; // 0x3C88
public:
	void ExecPrevWSB();
	void ExecPostWSB();
	bool IsExecWSB();
private:
	static const int32_t FuncCallArg_Num; // 0xFFFFFFFFFFFFFFFF
	static const int32_t FuncCallArg_StackMax; // 0xFFFFFFFFFFFFFFFF
	int32_t m_FuncCallArg[4][10] {}; // 0x3C8C
	int32_t m_FuncCallArgStack {}; // 0x3D2C
	bool m_FuncCallArgStackDebug {}; // 0x3D30
public:
	void InitFuncCallArg();
	void PushFuncCallArg(int arg0, int arg1, int arg2, int arg3);
	void PopFuncCallArg();
	int32_t GetFuncCallArg(int32_t);
	void FuncCallArgDebug(bool);
	void AllCharacterStopVoice();
	void AllCharacterEndJimakuForce();
	void RequestStopCharaVoice(OBJ_CCharBase *);
	CFloatWithTimer m_BGMVolume; // 0x3D34
	CFloatWithTimer m_AmbientVolume; // 0x3D4C
	bool IsAnyMemberClockStopEnable();
	void UpdateDrawExponentialHeightFogs();
	struct SGameSpeedControlParam 
    {
        int32_t InFrame; // 0x0
        int32_t StayFrame; // 0x4
        int32_t OutFrame; // 0x8
        int32_t CurrentFrame; // 0xC
        int32_t InCurve; // 0x10
        int32_t OutCurve; // 0x14
        int32_t StartGameSpeed; // 0x18
        int32_t EndGameSpeed; // 0x1C
        int32_t CurrentGameSpeed; // 0x20
        int32_t CurrentGameSpeedFrame; // 0x24
        bool bRequestApplyParticle; // 0x28
        bool bCurrentApplyParticle; // 0x29
        void Reset();
        int32_t GetTotalFrame();
    };
	SGameSpeedControlParam GameSpeedControlParam; // 0x3D64
	void RequestGameSpeedChange(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, bool);
	float GetValueApplyGameSpeed(float);
	int32_t GetValueApplyGameSpeed(uint32_t);
	int32_t GetValueApplyGameSpeed(int32_t);
	int32_t GetCurrentGameSpeed();
	int32_t UpdateGameSpeedParam();
	void RollBack_PreBackup();
	void RollBack_PreRollBack();
	void RollBack_PostRollBack();
	void Rollback_SaveRollback_Memcpy(void *, const unsigned long long);
	void Rollback_LoadRollback_Memcpy(const void *, const unsigned long long);
	void Rollback_SaveRollback_Obj(void *, const unsigned long long);
	void Rollback_LoadRollback_Obj(const void *, const unsigned long long);
	void Rollback_SaveRollback_Char(void *, const unsigned long long);
	void Rollback_LoadRollback_Char(const void *, const unsigned long long);
	void InitializeRandomSeed();
private:
	uint32_t m_GameFrame; // 0x3D90
public:
	uint32_t GetGameFrame();
	void UpdateGameFrame();
private:
	int32_t ObjMngCopyEnd; // 0x3D94
	OBJ_CBase m_ObjVector[101]; // 0x3D98
	OBJ_CCharBase m_CharVector[6]; // 0x25E4C8
public:
	static unsigned long long GetBigBlockMemcpySize();
	static unsigned long long GetObjVectorTotalSize();
	static unsigned long long GetCharVectorTotalSize();
	const unsigned long long GetObjRBMemcpySize();
	const unsigned long long GetCharRBMemcpySize();
	BATTLE_CObjectManager & operator=(const BATTLE_CObjectManager &);
};
