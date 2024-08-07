#pragma once
#include <cstdint>

class BattleSettings
{
public:
	int32_t Time; // 0x0
	int32_t WinCount; // 0x4
	int32_t Difficult; // 0x8
	bool EnableFinalRound; // 0xC
	BattleSettings() {}
	void SetDefault();
	int32_t GetTimeMax();
	uint32_t GetWinCountMax();
	uint32_t GetGameDifficulty();
	bool IsEnableFinalRound();
	static int32_t GetNerworkModeRoundTime();
	static int32_t GetNerworkModeRoundCount();
};