#pragma once
#include <cstdint>
#include "REDGameConstant.h"
#include "BattlePlayerResult.h"
#include "BattleRoundTimer.h"

class BattleState
{
private:
	RoundTimer m_Timer; // 0x8
	PlayerResult m_PlayerResult[2]; // 0x18
	uint32_t m_RoundCount; // 0x118
	uint32_t m_RoundMax; // 0x11C
	bool m_FinalRound; // 0x120
	bool m_IsBattleDoing; // 0x121
	bool m_IsStartedBattle; // 0x122
	SIDE_ID m_Winner; // 0x124
	bool m_PauseUpdate; // 0x128
	bool m_RematchBattle; // 0x129
	uint32_t m_RematchRound; // 0x12C
	bool m_IsBattleTempStop; // 0x130
	SIDE_ID m_timerForcePauseSide; // 0x134
	bool m_BattleQuickEnd; // 0x138
	bool m_TimeLimitForceFinish; // 0x139
	void InitParam();
	void SetWinner(SIDE_ID);
	void SetWinnerDraw();
	void ResetWinner();
public:
	BattleState() {}
	~BattleState() {}
	void Setup();
	void Update();
	void SetPause(bool);
	bool IsPause() { return m_PauseUpdate; }
	void RoundStart();
	void RoundReset();
	void RoundEnd();
	RoundTimer * GetRoundTimer();
	PlayerResult * GetPlayerResult(SIDE_ID);
	PlayerResult GetPlayerResultTmp(SIDE_ID);
	void SetFinalRound();
	bool IsFinalRound();
	bool IsFirstRound();
	uint32_t GetRoundCount();
	uint32_t GetRoundCountForDisp();
	uint32_t GetRoundCountForRoundChange();
	void EndSparring(SIDE_ID);
	void UpdateRoundResult(SIDE_ID, ROUND_RESULT, bool, int32_t);
	bool ReplayFinalRoundCheck(SIDE_ID, ROUND_RESULT, bool);
	void RevertRound();
	bool IsMatchPoint(SIDE_ID);
	SIDE_ID GetWinner() { return m_Winner; }
	bool IsMatchResultDraw();
	bool IsMatchEnd();
	void SetBattleDoing(bool);
	bool IsBattleDoing() { return m_IsBattleDoing; }
	void SetStartedBattle(bool);
	bool IsStartedBattle();
	bool IsStraightWin(SIDE_ID);
	bool IsTimeup();
	void SetRematchBattle(uint32_t);
	bool IsRematchBattle();
	void SetBattleTempStop(bool);
	bool IsBattleTempStop() { return m_IsBattleTempStop; }
	void SetBattleQuickEnd(bool);
	bool IsBattleQuickEnd();
	void BattleQuickEndON();
	void SetBattleQuickEndWinnerInfo(SIDE_ID);
	void SetForceBattleWinner(SIDE_ID);
	void SetTimeLimitForceFinish(bool);
	bool IsTimeLimitForceFinish();
	void SetRoundCount(uint32_t);
	BattleState & operator=(const BattleState &);
};