#include "battle_TeamManager.h"

void BATTLE_TeamManager::RoundReset()
{
    m_ChangeMemberID = SubMemberID_INVALID;
    m_TensionVal = 0;
    m_BurstStock = 0;
    m_BurstStockMax = 0;
    m_AssistActInvalidTime = 0;
    m_bDoingUltimateChange = false;
    m_AssistCallCount = 0;
    m_AtkPriority = 0;
    m_AlternativeUltimateChange = 0;
    m_TensionAddAct = TENSION_ACT_INVALID;
    m_bAssistActInvalidTimeClear = true;
    m_ComboCount[0] = 0;
    m_ComboCount[1] = 0;
    m_ComboCount[2] = 0;
    m_Damage[0] = 0;
    m_Damage[1] = 0;
    m_Damage[2] = 0;
    m_OwnComboCount[0] = 0;
    m_OwnComboCount[1] = 0;
    m_OwnComboCount[2] = 0;
    m_LastTotalComboCount = 0;
    m_MaxTotalDamage = 0;
    m_LastTotalComboCount = 0;
    m_AttackHitCount = 0;
    m_AttackGuardCount = 0;
    m_LiveRushCounter = 0;
    m_changeDisableTimeChar = 0;
    m_dispChangeDisableMark[0] = 0;
    m_dispChangeDisableMark[1] = 0;
    m_bRequestedAssistVoice[0] = false;
    m_bRequestedAssistVoice[1] = false;
    m_TensionPenalty = 0;
    m_TensionPenaltyTime = 0;
    m_TensionBalance = 0;
    m_TensionNoTouchTime = 0;
    m_TensionSideTime = 0;
    m_NegativeVal = 0;
    m_NegativeSuspend = 0;
    m_PositiveBonus = 0;
    m_PositiveBonusNum = 0;

    m_pPrevMainPlayerObject = m_pMainPlayerObject;
    if (!m_pPrevMainPlayerObject) m_pPrevMainPlayerObject = m_pMemberObjects[0];
    m_pMainPlayerObject = m_pMemberObjects[0];

    if (!m_SparkingTime) 
    {
        m_SparkingAuraCounter = 0;
        m_bSparkingAuraUpdate = false;
    }

    m_SparkingTime = 0;

    for (auto& skillHistory : m_AtkSkillHistory)
    {
        skillHistory = 0;
    }
}

void BATTLE_TeamManager::Update()
{
    for (int i = 0; i < 2; i++)
    {
        auto 
    }
}
