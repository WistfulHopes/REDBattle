#include <cstdint>
#include "game_key_cmdtbl.h"
class CBattleInputAnalyzer
{
public:
	CBattleInputAnalyzer();
	void ResetBattleInputAnalyzer();
	enum
	{
		NUM = 30,
	};
	unsigned short m_PreRecFlg; // 0x0
	unsigned short m_CurRecFlg; // 0x2
	unsigned short m_RecFlgList[30]; // 0x4
	unsigned short m_RecFlgTime[30]; // 0x40
	unsigned short m_CurIndex; // 0x7C
	static const unsigned short RECFLGTIME_MAX; // 0xFFFFFFFFFFFFFFFF
	void UpdateBattleInputAnalyzer(unsigned short);
	bool CheckCommand(CMD_KeyCommandID, uint32_t);
	bool CheckRotateCommand(uint32_t, uint32_t);
	bool CheckHighJump();
	bool IsHold(unsigned short);
	bool IsTrgOn(unsigned short);
	bool IsTrgOff(unsigned short);
	unsigned short GetCurRecFlg();
	void ResetRecFlag();
	void ResetRecFlagSafe(bool);
};
