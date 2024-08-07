#include "BattleEventManager.h"

void BattleEventManager::Setup()
{
    SetEvent(BEM_ModeCheck);
    m_BOMEventCount++;
    m_BOMEvent[m_BOMEventCount].eventID = BOM_EVENT_SET_KEY_FLAG;
    m_BOMEvent[m_BOMEventCount].param0 = 0;
    m_BOMEvent[m_BOMEventCount].param1 = 0;
    m_BOMEvent[m_BOMEventCount].param2 = 0;
    m_BOMEventCount++;
    m_BOMEvent[m_BOMEventCount].eventID = BOM_EVENT_RESET;
    m_BOMEvent[m_BOMEventCount].param0 = 0;
    m_BOMEvent[m_BOMEventCount].param1 = 0;
    m_BOMEvent[m_BOMEventCount].param2 = 0;
}


void BattleEventManager::SetEvent(BEM_STATE state)
{
    m_LastBEMState = m_CurrentBEMState;
    m_CurrentBEMState = state;
    m_bFinishUIEnd = false;
    m_bEnableMatchWinSecondAction = false;
    m_bEndMatchWinSecondAction = false;
    m_MatchWinFadeOutTime = 60;
    delete m_pBattleEvent;
    m_pBattleEvent = BattleEventFactory(state);
}

BattleEventBase* BattleEventManager::BattleEventFactory(BEM_STATE state)
{
    switch (state)
    {
    default: 
        break;
    }
    m_EventArg[0] = 0;
    m_EventArg[1] = 0;
    m_EventArg[2] = 0;
    m_EventArg[3] = 0;
    return nullptr;
}
