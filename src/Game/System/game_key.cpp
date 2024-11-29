#include "game_key.h"

void CBattleInputAnalyzer::UpdateBattleInputAnalyzer(unsigned short recFlg)
{
    m_PreRecFlg = m_CurRecFlg;
    m_CurRecFlg = recFlg;
    if (recFlg != m_RecFlgList[m_CurIndex])
    {
        m_CurIndex++;
        if (m_CurIndex > 31)
            m_CurIndex = 0;
        
        m_RecFlgTime[m_CurIndex] = 0;
        m_RecFlgList[(m_CurIndex + 1) % 31] = 0;
        m_RecFlgTime[(m_CurIndex + 1) % 31] = 0;
    }
    m_RecFlgList[m_CurIndex] = recFlg;
    if (m_RecFlgTime[m_CurIndex] != (uint16_t)-1) m_RecFlgTime[m_CurIndex]++;        
}

bool CBattleInputAnalyzer::IsHold(unsigned short recFlg)
{
    return (recFlg & m_CurRecFlg) != 0;
}

bool CBattleInputAnalyzer::IsTrgOn(unsigned short recFlg)
{
    return (recFlg & m_PreRecFlg) == 0 && (recFlg & m_CurRecFlg) != 0;
}

bool CBattleInputAnalyzer::IsTrgOff(unsigned short recFlg)
{
    return (recFlg & m_PreRecFlg) != 0 && (recFlg & m_CurRecFlg) == 0;
}

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
