#pragma once
#include <cstdint>
#include <Game/REDGameConstant.h>

class BattleEventManager;

enum BOM_EVENT
{
	BOM_EVENT_ENTRY = 0,
	BOM_EVENT_ONLYDRAMA_BATTLE_SETUP = 1,
	BOM_EVENT_ARCADE_EVENT_SETUP = 2,
	BOM_EVENT_ARCADE_EVENT_FINISH = 3,
	BOM_EVENT_ENTRY_EVENT_SETUP = 4,
	BOM_EVENT_ENTRY_EVENT_FINISH = 5,
	BOM_EVENT_ENTRY_BG = 6,
	BOM_EVENT_ENTRY_CHARA = 7,
	BOM_EVENT_RESULT_CHARA = 8,
	BOM_EVENT_RESET = 9,
	BOM_EVENT_SET_KEY_FLAG = 10,
	BOM_EVENT_BATTLE_START = 11,
	BOM_EVENT_RESULT_SCREEN_SETUP_FOR_STORY = 12,
	BOM_EVENT_WIN_ACTION = 13,
	BOM_EVENT_MATCH_WIN_ACTION = 14,
	BOM_EVENT_MATCH_RESULT_WAIT = 15,
	BOM_EVENT_DECISION = 16,
	BOM_EVENT_BATTLE_START_CAMERA = 17,
	BOM_EVENT_REQUEST_FINISH_STOP = 18,
	BOM_EVENT_REQUEST_FINISH_CAMERA = 19,
	BOM_EVENT_ENTRY_SCREEN_CONTROL = 20,
	BOM_EVENT_WIN_SCREEN_CONTROL = 21,
	BOM_EVENT_RESET_REMATCH = 22,
	BOM_EVENT_MAIN_MEMBER_CHANGE = 23,
	BOM_EVENT_RESET_ON_MEMBER_CHANGE = 24,
	BOM_EVENT_MATCH_START_EFFECT = 25,
	BOM_EVENT_FINISH_SLOW = 26,
	BOM_EVENT_DESTRUCTION_FINISH_START = 27,
	BOM_EVENT_DRAMATIC_FINISH_START = 28,
	BOM_EVENT_SHENLONG_SYSTEM = 29,
	BOM_EVENT_RESULT_VOICE_COMMON = 30,
	BOM_EVENT_RESULT_VOICE_SPECIAL = 31,
	BOM_EVENT_STOP_RESULT_VOICE = 32,
	BOM_EVENT_DRAMATIC_FINISH_UI_AND_STOP = 33,
	BOM_EVENT_HUD_TUTORIAL_START = 34,
	BOM_EVENT_ENTRY_START = 35,
	BOM_EVENT_ADV_DISP_BATTLE = 36,
	BOM_EVENT_RANNYU_SAVER = 37,
	BOM_EVENT_BBS_EVENT_SETUP = 38,
	BOM_EVENT_BBS_EVENT_FINISH = 39,
	BOM_EVENT_ROUND_RESET_FOR_BG = 40,
	BOM_EVENT_INVALID = 41,
	BOM_EVENT_MAX = 42,
};
enum BEM_STATE
{
	BEM_ModeCheck = 0,
	BEM_OnlyDramaBattle = 1,
	BEM_EntryEvent = 2,
	BEM_EntryChara = 3,
	BEM_RoundReset = 4,
	BEM_DispBattleBegin = 5,
	BEM_DispRound = 6,
	BEM_CheckBattle = 7,
	BEM_CheckBattleOnAdvertise = 8,
	BEM_CheckBattleOnSparring = 9,
	BEM_CheckBattleOnTraining = 10,
	BEM_QuickResetBattle = 11,
	BEM_DispRoundResult = 12,
	BEM_RoundEnd = 13,
	BEM_RoundEndWinAction = 14,
	BEM_MatchEndWinAction = 15,
	BEM_MatchEndWinAction2 = 16,
	BEM_MatchEndDrawAction = 17,
	BEM_MatchEndWinActionLocationTest = 18,
	BEM_MatchResult = 19,
	BEM_AdvertiseBattleEnd = 20,
	BEM_SparringBattleEnd = 21,
	BEM_FinishEvent = 22,
	BEM_NewChallengerMatchEnd = 23,
	BEM_VSReMatchMenuOnly = 24,
	BEM_RematchMenuSceneTransition = 25,
	BEM_NextPlayerEntryAction = 26,
	BEM_MemberChangeReset = 27,
	BEM_MatchStartAfterBGTrans = 28,
	BEM_NextNetworkReplay = 29,
	BEM_FinishBattleNoResult = 30,
	BEM_ReplayResult = 31,
	BEM_SpectorResult = 32,
	BEM_ScriptEvent = 33,
	BEM_IdleState = 34,
	BEM_STATE_MAX = 35,
	BEM_STATE_INVALID = 36,
};
enum SCRIPTEVENT_TYPE
{
	SCREVT_FIRST_ENTRY = 0,
	SCREVT_FIRST_LEAVE_LOSE = 1,
	SCREVT_FIRST_LEAVE_WIN = 2,
	SCREVT_INTRUDER_ENTRY = 3,
	SCREVT_INTRUDER_LEAVE = 4,
	SCREVT_BOSS_INTRUDER_ENTRY_1 = 5,
	SCREVT_BOSS_INTRUDER_ENTRY_2 = 6,
	SCREVT_BOSS_INTRUDER_LEAVE_1 = 7,
	SCREVT_BOSS_INTRUDER_LEAVE_2 = 8,
	SCREVT_BOSS_ENTRY = 9,
	SCREVT_BOSS_LEAVE_1 = 10,
	SCREVT_BOSS_LEAVE_2 = 11,
	SCREVT_RIVAL_ENTRY = 12,
	SCREVT_RIVAL_LEAVE_1 = 13,
	SCREVT_RIVAL_LEAVE_2 = 14,
	SCREVT_EXBOSS_ENTRY = 15,
	SCREVT_EXBOSS_LEAVE = 16,
	SCREVT_TUTORIAL_START = 17,
	SCREVT_TUTORIAL_FINAL_ROUND = 18,
	SCREVT_TUTORIAL_END = 19,
	SCREVT_INVALID = 20,
};
struct BOMEventInfo
{
	BOM_EVENT eventID {}; // 0x0
	int32_t param0 {}; // 0x4
	int32_t param1 {}; // 0x8
	int32_t param2 {}; // 0xC
	void Reset()
	{
		eventID = BOM_EVENT_ENTRY_EVENT_SETUP;
		param0 = 0;
		param1 = 0;
		param2 = 0;
	}
};
struct DemoEndCheck
{
	bool isDemoEnd[2] {}; // 0x0
	bool isMemberDemoEnd[3][2] {}; // 0x2
	DemoEndCheck();
	void Reset();
};

class BattleEventBase
{
private:
	bool m_Started {}; // 0x8
	bool m_CounterReset {}; // 0x9
	uint32_t m_Counter {}; // 0xC
	int32_t m_DemoTimeoutCounter {}; // 0x10
	int32_t m_SubState {}; // 0x14
	DemoEndCheck m_DemoEndCheck {}; // 0x18
	bool m_EnableDemoEndCheck {}; // 0x20
	enum START_RESULT
	{
		START_RESULT_EXECUTE = 0,
		START_RESULT_WAIT = 1,
	};
	enum EDuplicateArg
	{
		DuplicateArg = 0,
	};
protected:
	bool SubStateInTrigger();
public:
	BattleEventBase(EDuplicateArg);
	BattleEventBase(const char *);
	~BattleEventBase() {}
	BEM_STATE ExecuteEvent(BattleEventManager *);
	START_RESULT Start(BattleEventManager *);
	BEM_STATE Execute(BattleEventManager *);
	uint32_t Counter();
	void ResetCounter();
	void BeginDemoEndCheck();
	bool EnableDemoEndCheck();
	void ResetDemoEndCheck();
	bool IsDemoTimeout(int32_t *);
	void UpdateDemoEndFlag();
	bool IsDemoEnd(SIDE_ID);
	void UpdateCounter();
	const char * GetStateName();
	const char * GetSubStateName();
	BattleEventBase * Duplicate();
	bool IsQuickTrainingReturn();
	void QuickTrainingReturn(BattleEventManager *);
	BattleEventBase & operator=(const BattleEventBase &);
};
class BattleEventManager
{
private:
	BOMEventInfo m_BOMEvent[10] {}; // 0x8
	uint32_t m_BOMEventCount {}; // 0xA8
	BattleEventBase * m_pBattleEvent {}; // 0xB0
	int32_t m_EventArg[4] {}; // 0xB8
	bool m_bFinishUIEnd {}; // 0xC8
	bool m_bEnableMatchWinSecondAction {}; // 0xC9
	bool m_bEndMatchWinSecondAction {}; // 0xCA
	int32_t m_MatchWinFadeOutTime {}; // 0xCC
	bool m_PlayingMatchResultVoice {}; // 0xD0
	bool m_bEnterMatchResult {}; // 0xD1
	int32_t m_DramaSkipInputDisableTime {}; // 0xD4
	BEM_STATE m_CurrentBEMState {}; // 0xD8
	BEM_STATE m_LastBEMState {}; // 0xDC
	void SavePrevStateInfo();
	void InitParam();
	void Reset();
	bool GetEventArgBool(int32_t);
	void ResetEventArg();
	BattleEventBase * BattleEventFactory(BEM_STATE state);
	BOMEventInfo * Pop();
	void ResetOnSetEvent();
public:
	BattleEventManager() {}
	~BattleEventManager() {}
	void Setup();
	void Update();
	BattleEventBase * GetEvent();
	void SetEvent(BEM_STATE state);
	BEM_STATE GetCurrentBEMState();
	BEM_STATE GetLastBEMState();
	void DebugSaveObjectManagerEvent(const BOMEventInfo *);
	void RequestBOMEventBase(BOM_EVENT, int32_t, int32_t, int32_t);
	void RequestBOMEvent(BOM_EVENT);
	const BOMEventInfo * GetBOMEvent(uint32_t index) { return &m_BOMEvent[index]; }
	uint32_t GetBOMEventCount() { return m_BOMEventCount; }
	void ResetBOMEvent()
	{
		for (auto event : m_BOMEvent)
		{
			event.Reset();
		}
		m_BOMEventCount = 0;
	}
	void FinishUIEnd();
	bool IsFinishUIEnd();
	void SetEnableMatchWinSecondAction(bool);
	bool IsEnableMatchWinSecondAction();
	void EndMatchWinSecondAction();
	bool IsEndMatchWinSecondAction();
	void SetMatchWinFadeOutTime(int32_t);
	int32_t GetMatchWinFadeOutTime();
	bool IsPlayingMatchResultVoice();
	void SetPlayingMatchResultVoice(bool);
	void EnterMatchResultScreen();
	bool IsMatchResultScreen();
	void SetDramaSkipInputDisableTime(int32_t);
	int32_t GetDramaSkipInputDisableTime();
	void DebugDisp();
	const char * GetStateText();
	const char * GetSubStateText();
	uint32_t GetSubStateCounter();
	void SetFromBattleEventManager(const BattleEventManager &);
	BattleEventManager & operator=(const BattleEventManager &);
};
