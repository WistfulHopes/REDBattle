#pragma once
#include <cstdint>
#include "REDGameConstant.h"

class REDBattlePlayerInfo 
{
public:
    REDBattlePlayerInfo();

    FMemberCharaInfo m_MemberCharaInfoList[3]; // 0x28
	bool DecideChara; // 0x4C
	uint32_t Handicap; // 0x50
	unsigned char PlayerState; // 0x54
	bool bUseCard; // 0x55
	bool bPadAssign; // 0x56
	bool bPlayTimeLimit; // 0x57
	PAD_ID PadID; // 0x58
	GAME_MODE PlayGameMode; // 0x5C
	int32_t SystemContinueTimer; // 0x60
	int32_t StageNo; // 0x64
	int32_t ContinueCount; // 0x68
	bool bStraightAll; // 0x6C
	bool bRandomChara; // 0x6D
	int32_t WinCount; // 0x70
	int32_t TmpWinCount; // 0x74
	int32_t TmpLoseCount; // 0x78
	wchar_t EntryName[4]; // 0x7C
	enum BATTLE_DRAMA_ID BattleDramaID; // 0x84
	bool bStylishMode; // 0x88
	bool bSelectMySet; // 0x89
	float PauseMenuLeftTime; // 0x8C
	void InitializeParam();
};