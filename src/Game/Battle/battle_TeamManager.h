#pragma once
#include <REDGameConstant.h>
#include "Battle/Object/Char/char_Base.h"
#include "Battle/Object/obj_AttackParam.h"

enum TENSION_ADD_ACTION
{
	TENSION_ACT_ATTACK = 0,
	TENSION_ACT_GUARD = 1,
	TENSION_ACT_DAMAGE = 2,
	TENSION_ACT_KIAITAME = 3,
	TENSION_ACT_BONUS = 4,
	TENSION_ACT_INVALID = 5,
	TENSION_ACT_NUM = 6,
};

class BATTLE_TeamManager 
{
private:
    SIDE_ID m_SideID; // 0x0
	OBJ_CCharBase * m_pMainPlayerObject; // 0x8
	OBJ_CCharBase * m_pMemberObjects[3]; // 0x10
	OBJ_CCharBase * m_pPrevMainPlayerObject; // 0x28
	EMemberID m_TeamMemberIndex[3]; // 0x30
	EMemberID m_TeamMemberIndexForResult[3]; // 0x3C
	int32_t m_TensionVal; // 0x48
	int32_t m_BurstStock; // 0x4C
	int32_t m_BurstStockMax; // 0x50
	ESubMemberID m_ChangeMemberID; // 0x54
	ESubMemberID m_ReserveChangeMemberID; // 0x58
	char m_UltimateChangeFlag; // 0x5C
	char m_ReserveUltimateChangeFlag; // 0x5D
	char m_changeType; // 0x5E
	char m_ReserveChangeType; // 0x5F
	uint32_t m_forceChangeDir; // 0x60
	unsigned char m_AlternativeUltimateChange; // 0x64
	int32_t m_AssistActInvalidTime; // 0x68
	bool m_bAssistActInvalidTimeClear; // 0x6C
	int32_t m_AssistCallCount; // 0x70
	bool m_bDoingUltimateChange; // 0x74
	int32_t m_SparkingTime; // 0x78
	int32_t m_SparkingAuraCounter; // 0x7C
	bool m_bSparkingAuraUpdate; // 0x80
	int32_t m_ComboCount[3]; // 0x84
	int32_t m_TotalComboCount; // 0x90
	int32_t m_LastTotalComboCount; // 0x94
	int32_t m_OwnComboCount[3]; // 0x98
	int32_t m_TotalOwnComboCount; // 0xA4
	int32_t m_LastTotalOwnComboCount; // 0xA8
	int32_t m_Damage[3]; // 0xAC
	int32_t m_TotalDamage; // 0xB8
	int32_t m_MaxTotalDamage; // 0xBC
	static const uint32_t ATKSKILL_HISTORY_TEAM_NUM; // 0xFFFFFFFFFFFFFFFF
	unsigned char m_AtkSkillHistory[100]; // 0xC0
	int32_t m_AtkSkillHistoryIndex; // 0x124
	int32_t m_AtkPriority; // 0x128
	TENSION_ADD_ACTION m_TensionAddAct; // 0x12C
	short m_AttackHitCount; // 0x130
	short m_AttackGuardCount; // 0x132
	int32_t m_LiveRushCounter; // 0x134
	static const int32_t LiveRushCounter; // 0xFFFFFFFFFFFFFFFF
	unsigned char m_changeDisableTimeChar; // 0x138
	char m_dispChangeDisableMark[2]; // 0x139
	bool m_bRequestedChangeVoice; // 0x13B
	bool m_bRequestedAssistVoice[2]; // 0x13C
	bool m_TensionPenalty; // 0x13E
	int32_t m_TensionPenaltyTime; // 0x140
	int32_t m_TensionBalance; // 0x144
	int32_t m_TensionNoTouchTime; // 0x148
	int32_t m_TensionSideTime; // 0x14C
	int32_t m_NegativeVal; // 0x150
	int32_t m_NegativeSuspend; // 0x154
	int32_t m_PositiveBonus; // 0x158
	int32_t m_PositiveBonusNum; // 0x15C
	OBJ_CCharBase * GetLatestMainPlayer();
public:
	BATTLE_TeamManager();
	void Initialize(SIDE_ID);
	SIDE_ID GetSideID();
	void RoundReset();
	void SetMember(EMemberID, OBJ_CCharBase *);
	OBJ_CCharBase * GetMember(EMemberID);
	OBJ_CCharBase * GetMemberFromIndex(int32_t);
	OBJ_CCharBase * GetMainPlayer();
	void SetMainPlayer(OBJ_CCharBase *);
	void SetMainPlayerSimple(OBJ_CCharBase *);
	OBJ_CCharBase * GetPrevMainPlayer();
	OBJ_CCharBase * GetSubMember(ESubMemberID);
	OBJ_CCharBase * GetAliveSubMember(ESubMemberID);
	void UpdateMainTarget(BATTLE_TeamManager *);
	void ChangeMainPlayer(OBJ_CCharBase *);
	void Update();
	void UpdateLeaveRequest();
	int32_t GetTensionVal();
	void SetTensionVal(int32_t);
	int32_t GetTensionValMax();
	int32_t GetBurstStock();
	void UseBurstStock(int32_t);
	void AddBurstStock(int32_t);
	void SetBurstStock(int32_t);
	int32_t GetBurstStockMax();
	bool IsDead(EMemberID);
	bool IsSubMemberDead(ESubMemberID);
	bool IsTeamDead();
	bool IsEntry(EMemberID);
	bool IsSubMemberStable(ESubMemberID);
	bool IsAllSubMemberStable();
	int32_t GetTeamTotalHitPoint();
	int32_t GetTeamTotalHitPointRate();
	ESubMemberID GetChangeMemberID();
	bool IsChangeMemberRequest();
	void ChangeMemberRequest(ESubMemberID, char, char);
	void ChangeMemberRequestReserve(ESubMemberID, char, char);
	void ExecChangeMemberRequestReserve();
	void ResetChangeMemberRequest();
	ESubMemberID GetReserveChangeMemberID();
	void SetReserveChangeMemberID(ESubMemberID);
	void SetForceChangeDir(uint32_t);
	uint32_t GetForceChangeDir();
	void SetupWinAction(bool);
	void ActionRequestSpecialFinishWait();
	void ActionRequestHideSubMember();
	void SwapMemberIndex(EMemberID, EMemberID);
	void ResetMemberIndex(EMemberID, bool);
	void SetMemberIndex(EMemberID, EMemberID);
	EMemberID * GetMemberIndexArray() { return m_TeamMemberIndex; }
	EMemberID GetChangedMemberIndex(EMemberID);
	int32_t GetAssistActInvalidTime();
	void SetAssistActInvalidTime(int32_t);
	bool IsValidAssistAct();
	void SetAssistActInvalidTimeClear(bool);
	void ResetAssistActInvalidTime();
	void AddAssistCallCount(int32_t);
	int32_t GetAssistCallCount();
	void SetSparkingBurstTime(int32_t);
	int32_t GetSparkingBurstTime();
	bool IsSparkingBurst();
	int32_t GetSparkingAuraCounter();
	bool IsSparkingAuraUpdate();
	void SetSparkingAuraUpdate(bool);
	void RequestChangeMemberVoice();
	void CheckUltimateChange();
	bool IsDoingUltimateChange();
	void SetAlternativeInputUltimateChange(unsigned char);
	bool IsAlternativeInputUltimateChange();
	int32_t GetComboCount();
	int32_t GetLastComboCount();
	void ClearLastTotalComboCount();
	int32_t GetOwnComboCount();
	int32_t GetLastOwnComboCount();
	void UpdateComboCount();
	void CockpitInfoByComboCount(int32_t);
	int32_t GetMaxTotalDamage();
	void UpdateMaxDamage();
	void ResetAtkSkillHistory();
	void SetAtkSkillHistory(CSkillInfo *);
	void SetAtkSkillHistory(unsigned char);
	bool CheckAtkSkillHistory(CSkillInfo *);
	bool CheckAtkSkillHistory(unsigned char);
	bool CheckAttackHitOnceInCombo(CAtkParam *, CSkillInfo *);
	void SetAttackPriority(int32_t);
	int32_t GetAttackPriority();
	void SetTensionAddAction(TENSION_ADD_ACTION);
	TENSION_ADD_ACTION GetTensionAddAction();
	void SaveMemberIDForResultScreen();
	const OBJ_CCharBase * GetMemberForResultScreen(EMemberID);
	EMemberID GetMemberIDForResultScreen(const OBJ_CBase *);
	void AddAttackHitCount(int32_t);
	void ResetAttackHitCount();
	int32_t GetAttackHitCount();
	void AddAttackGuardCount(int32_t);
	void ResetAttackGuardCount();
	int32_t GetAttackGuardCount();
	int32_t GetLiveRushCounter();
	void ResetLiveRushCounter();
	void SetChangeDisableChar(ESubMemberID);
	short GetDispChangeDisableCharMarkTimer(ESubMemberID);
	void ForceResetDispChangeDisableCharMarkTimer(ESubMemberID);
	bool IsRequestedChangeVoice();
	bool IsRequestedAssistVoice(ESubMemberID);
	void SetRequestedAssistVoice(ESubMemberID, bool);
	void SetTensionPenalty(bool);
	bool IsTensionPenalty();
	void ResetTensionPenalty();
	int32_t GetTensionPenaltyTime();
	int32_t & GetTensionPenaltyTimeRef();
	void SetTensionPenaltyTime(int32_t);
	int32_t GetTensionBalance();
	int32_t & GetTensionBalanceRef();
	void SetTensionBalance(int32_t);
	int32_t GetTensionNoTouchTime();
	int32_t & GetTensionNoTouchTimeRef();
	void SetTensionNoTouchTime(int32_t);
	int32_t GetTensionSideTime();
	int32_t & GetTensionSideTimeRef();
	void SetTensionSideTime(int32_t);
	int32_t GetNegativeVal();
	int32_t & GetNegativeValRef();
	void SetNegativeVal(int32_t);
	int32_t GetNegativeSuspend();
	int32_t & GetNegativeSuspendRef();
	void SetNegativeSuspend(int32_t);
	int32_t GetPositiveBonus();
	int32_t & GetPositiveBonusRef();
	void SetPositiveBonus(int32_t);
	int32_t GetPositiveBonusNum();
	void SetPositiveBonusNum(int32_t);
};