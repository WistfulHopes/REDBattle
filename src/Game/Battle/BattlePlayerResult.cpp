#include "BattlePlayerResult.h"

void PlayerResult::Reset()
{
    for (auto& result : m_Result)
    {
        result = ROUND_RESULT_INVALID;
    }
    m_WinCount = 0;
    m_WinCountMax = 0;
    for (auto& round : m_ResultRounds)
    {
        round = RR_INVALID;
    }
}