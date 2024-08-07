#include "battle_TeamManager.h"

#include <AASystemRED.h>
#include <Scene/scene_Battle.h>

void BATTLE_TeamManager::Initialize(SIDE_ID sideID)
{
    m_SideID = sideID;
}

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

void BATTLE_TeamManager::SetMember(EMemberID memberID, OBJ_CCharBase* charBase)
{
    m_pMemberObjects[memberID] = charBase;
    charBase->m_SideID = m_SideID;
    charBase->m_MemberID = memberID;
}

OBJ_CCharBase* BATTLE_TeamManager::GetAliveSubMember(ESubMemberID SubMemberID)
{
    auto subMember = m_pMemberObjects[m_TeamMemberIndex[SubMemberID + 1]];
    if (!subMember->IsDead()) return subMember;

    auto teamMemberIndex = &m_TeamMemberIndex[1];

    for (int i = 0; i < 2; i++)
    {
        if (i != SubMemberID)
        {
            subMember = m_pMemberObjects[*teamMemberIndex];
            if (!subMember->IsDead()) return subMember;
        }
    }

    return nullptr;
}

void BATTLE_TeamManager::Update()
{
    auto isObjAvailable = [this]
    {
        int plyIdx = 0;
        const auto state = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->GetBattleState();
        if (state->IsBattleDoing() && !state->IsBattleTempStop() && !state->IsPause())
        {
            for (OBJ_CCharBase** i = m_pMemberObjects; !*i || (*i)->CheckForceStop(); ++i)
            {
                if (++plyIdx >= 3) return false;
            }
        }
        return true;
    };

    if (!isObjAvailable())
    {
        if (m_AssistActInvalidTime)
        {
            m_AssistActInvalidTime--;
            if (m_AssistActInvalidTime <= 0 && !m_bAssistActInvalidTimeClear)
            {
                m_AssistActInvalidTime = 1;
            }
        }
        if (m_SparkingTime)
        {
            m_SparkingTime--;
            if (m_SparkingTime <= 0) m_SparkingAuraCounter = 0;
        }
        if (m_LiveRushCounter)
        {
            m_LiveRushCounter--;
            if (m_LiveRushCounter <= 0) m_AttackHitCount = 0;
        }
        if (m_dispChangeDisableMark[0])
        {
            m_dispChangeDisableMark[0]--;
            if (m_dispChangeDisableMark[0] <= 0)
            {
                m_changeDisableTimeChar &= ~1;
            }
        }
        if (m_dispChangeDisableMark[1])
        {
            m_dispChangeDisableMark[1]--;
            if (m_dispChangeDisableMark[1] <= 0)
            {
                m_changeDisableTimeChar &= ~2;
            }
        }
    }
    if (m_bSparkingAuraUpdate) ++m_SparkingAuraCounter;

    CheckUltimateChange();
    if (m_ChangeMemberID != SubMemberID_INVALID)
    {
        auto subMember = GetAliveSubMember(m_ChangeMemberID);
        if (!subMember || m_pMainPlayerObject->IsDead())
        {
            m_ChangeMemberID = SubMemberID_INVALID;
            m_UltimateChangeFlag = -1;
            m_ReserveUltimateChangeFlag = -1;
            m_ReserveChangeMemberID = SubMemberID_INVALID;
            return;
        }
        
        bool bImmediate = false;
        if (m_UltimateChangeFlag)
        {
            if (m_UltimateChangeFlag != 1)
            {
                if (m_changeType == 1)
                {
                    if (m_pMainPlayerObject->m_HitStopTime) return;
                    subMember->m_bChangeHomingDash = true;
                    subMember->m_bGCHomingDash = true;
                    subMember->GuardCancelChangeEnterAttackRequest();
                    m_pMainPlayerObject->SetCooldownTime(m_pMainPlayerObject->GetGuardCancelCDT(),
                                                         m_pMainPlayerObject->GetInnerCDT(),
                                                         true);
                    bImmediate = true;
                    m_pMainPlayerObject->CommonSE("ARC_BTL_SYS_GuardCancel");
                }
                else
                {
                    short cooldownTime; 
                    if (m_changeType == 2)
                    {
                        subMember->ChangeEnterRequest();
                        cooldownTime = m_pMainPlayerObject->GetForceChangeCDT();
                    }
                    else
                    {
                        if (m_pMainPlayerObject->m_HitStopTime) return;
                        subMember->m_bChangeHomingDash = true;
                        subMember->ChangeEnterAttackRequest();
                        cooldownTime = m_pMainPlayerObject->GetChangeCDT();
                        bImmediate = m_pMainPlayerObject->IsAir();
                    }
                    m_pMainPlayerObject->SetCooldownTime(cooldownTime,
                                     m_pMainPlayerObject->GetInnerCDT(),
                                     true);
                }
                auto objDir = m_pMainPlayerObject->GetObjDir();
                if (m_pMainPlayerObject->m_pLinkObject_Direction.GetPtr())
                    objDir = m_pMainPlayerObject->m_pLinkObject_Direction.GetPtr()->GetObjDir();

                subMember->m_ChangeDir = objDir;
                subMember->m_ChangeHeight = m_pMainPlayerObject->GetPosY();
                goto CHANGE;
            }
            if (m_pMainPlayerObject->m_HitStopTime) return;
            subMember->ChangeAttackUltimate2ReadyRequest();
        }
        else
        {
            if (m_pMainPlayerObject->m_HitStopTime) return;
            subMember->ChangeAttackUltimate1ReadyRequest();
        }
        m_pMainPlayerObject->SetCooldownTime(m_pMainPlayerObject->GetUltimateChangeCDT(),
                 m_pMainPlayerObject->GetInnerCDT(),
                 true);
        m_pMainPlayerObject->AddPlayerFlag4(PLFLG4_NOMORE_ULTIMATECHANGE);
        m_bDoingUltimateChange = true;
CHANGE:
        subMember = GetAliveSubMember(m_ChangeMemberID);
        if (subMember)
        {
            if (m_UltimateChangeFlag == -1 && !m_changeType)
            {
                m_pMainPlayerObject->SetCallingChar(subMember->m_MemberID);
                subMember->SetCalledChar(m_pMainPlayerObject->m_MemberID);
                m_bRequestedChangeVoice = false;
                if (AASystemRED::GetInstance()->GetRandomManager().Get(1)->GenS32() % 1)
                {
                    m_pMainPlayerObject->Voice("vxxx503");
                    m_bRequestedChangeVoice = true;
                }
            }
        }

        m_pMainPlayerObject->SetImmLeaveRequest(bImmediate);
        m_pMainPlayerObject->ScreenCollision(0);
        m_pMainPlayerObject->WorldCollision(0);
        subMember->m_RecoverHitPoint = 0;

        const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->GetBattleObjectManager();
        objManager->TransferAirActionCount(subMember, m_pMainPlayerObject);

        if (!m_pMainPlayerObject->IsAir() && m_changeType <= 1)
        {
            subMember->ResetAirDashCount();
            subMember->ResetAirJumpCount();
        }

        auto teamMemberIndex = m_TeamMemberIndex;
        auto idx = 0;
        
        while (*teamMemberIndex != m_pMainPlayerObject->m_MemberID)
        {
            idx++;
            teamMemberIndex++;
            if (idx >= 3) goto CHANGE_FINAL;
        }
        if (idx != 4)
        {
            auto teamIdx = m_TeamMemberIndex[idx];
            auto idx2 = 0;
            
            while (*teamMemberIndex != subMember->m_MemberID)
            {
                idx2++;
                teamMemberIndex++;
                if (idx2 >= 3) goto CHANGE_FINAL;
            }
            *((uint32_t*)(&m_SideID + idx) + 12) = subMember->m_MemberID;
            teamMemberIndex[idx2] = teamIdx;
        }
CHANGE_FINAL:
        if (subMember != m_pMainPlayerObject)
        {
            m_pPrevMainPlayerObject = m_pMainPlayerObject;
            m_pMainPlayerObject = subMember;
            if (!m_pPrevMainPlayerObject) m_pPrevMainPlayerObject = subMember;
        }

        m_ChangeMemberID = SubMemberID_INVALID;
        m_UltimateChangeFlag = -1;
        m_ReserveUltimateChangeFlag = -1;
        m_ReserveChangeMemberID = SubMemberID_INVALID;
    }
}

void BATTLE_TeamManager::CheckUltimateChange()
{
    if (m_bDoingUltimateChange)
    {
        auto chrIdx = 0;
        for (OBJ_CCharBase** i = m_pMemberObjects; ; i++)
        {
            auto charObj = *i;
            if (charObj->IsEntry() && !charObj->IsDead())
            {
                auto curActionName = charObj->m_CurActionName;
                if (!strncmp(curActionName.GetStr(), "ChangeEnterAttackUltimate1", 0x20)
                    || !strncmp(curActionName.GetStr(), "ChangeEnterAttackUltimate2", 0x20)
                    || charObj->CheckAttackFlag(PLATK_ULTIMATECHANGESKILL) && charObj->CheckAttackFlag(
                        PLATK_ULTIMATESKILL))
                    break;
            }
            if (++chrIdx >= 3)
            {
                for (int j = 0; j < chrIdx; j++)
                {
                    if (charObj->IsEntry() && !charObj->IsDead() && charObj->CheckPlayerFlag4(PLFLG4_SLOWTIME_HOSEI))
                        charObj->DelPlayerFlag4(PLFLG4_SLOWTIME_HOSEI);
                }
                if (m_bDoingUltimateChange)
                {
                    const auto battleScene = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene());
                    m_AssistActInvalidTime = 120;
                    m_bDoingUltimateChange = false;
                    auto mainPlayer = battleScene->GetBattleObjectManager()->GetTeamManager(m_SideID)->GetMainPlayer();
                    if (mainPlayer && !mainPlayer->IsDead() && mainPlayer->IsDamage())
                        m_bAssistActInvalidTimeClear = false;
                }
                m_AlternativeUltimateChange = 0;
                return;
            }
        }
    }
}
