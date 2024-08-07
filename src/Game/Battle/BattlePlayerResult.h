#pragma once
#include <cstdint>

enum ROUND_RESULT
{
	ROUND_RESULT_WIN = 0,
	ROUND_RESULT_DOUBLEKO = 1,
	ROUND_RESULT_TIMEUP = 2,
	ROUND_RESULT_CHEAP = 3,
	ROUND_RESULT_SPECIAL = 4,
	ROUND_RESULT_ULTIMATE = 5,
	ROUND_RESULT_ICHIGEKI = 6,
	ROUND_RESULT_PERFECT = 7,
	ROUND_RESULT_MAINMEMBER_DEAD = 8,
	ROUND_RESULT_INVALID = 9,
	ROUND_RESULT_DRAW = 10,
	ROUND_RESULT_LOSE = 11,
	ROUND_RESULT_SILENT = 12,
};
enum ROUND_RESULT_EX
{
	RR_INVALID = 0,
	RR_WIN = 1,
	RR_WIN_SPECIAL = 2,
	RR_WIN_ULTIMATE = 3,
	RR_WIN_ICHIGEKI = 4,
	RR_WIN_TIMEUP = 5,
	RR_DRAW = 6,
	RR_LOSE = 7,
	RR_LOSE_SPECIAL = 8,
	RR_LOSE_ULTIMATE = 9,
	RR_LOSE_ICHIGEKI = 10,
	RR_LOSE_TIMEUP = 11,
	RR_NUM = 12,
};
class PlayerResult
{
private:
	ROUND_RESULT m_Result[10]; // 0x0
	uint32_t m_WinCount; // 0x28
	uint32_t m_WinCountMax; // 0x2C
	ROUND_RESULT_EX m_ResultRounds[20]; // 0x30
	void InitParam();
public:
	PlayerResult() {}
	void Reset();
	void Setup(uint32_t);
	void UpdateWinResult(ROUND_RESULT, bool);
	void UpdateResultRounds(uint32_t, ROUND_RESULT_EX, ROUND_RESULT, bool, int32_t);
	bool IsMatchPoint();
	bool IsBattleWinner();
	uint32_t GetWinCount();
	ROUND_RESULT_EX GetRoundResult(uint32_t);
	bool IsPerfectWinner();
	void RollbackWin();
	void SetBattleQuickEndPlayerResult(bool);
};