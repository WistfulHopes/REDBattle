#include "game_key.h"

void CBattleInputAnalyzer::ResetRecFlagSafe(bool isTime0)
{
    for (auto& recFlg : m_RecFlgList)
    {
        recFlg = 0;
    }
    auto time = 0;
    if (!isTime0) time = -1;
    for (auto& recFlgTime : m_RecFlgTime)
    {
        recFlgTime = time;
    }
}