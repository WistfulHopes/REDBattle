#include "char_Base.h"

#include <Game/Scene/scene_Battle.h>

#include <algorithm>

#include "char_ActCmn.h"

OBJ_CCharBase::OBJ_CCharBase()
{
    ObjectConstructor_ForPlayer();
}

void OBJ_CCharBase::ObjectConstructor_ForPlayer()
{
    m_IsPlayerObj = true;
    m_pParentPly.SetPtr(this);
    m_ActiveState = ACTV_ACTIVE;
}

void OBJ_CCharBase::PlayerInitializeOnEasyReset()
{
    FuncCall("cmn_SkillInit");
    FuncCall("cmn_VoiceInit");
    FuncCall(FN_RoundInit);
    FuncCall("cmnPositiveBonusEnd");

    int startPosition = 0;

    const auto battleScene = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene());
    if (battleScene->GetBattleObjectManager())
    {
        startPosition = battleScene->GetBattleObjectManager()->GetStartupPositionXBase(m_SideID, m_MemberID);
    }

    SetPosXRawinBattle(startPosition);
    if (GetMainPlayerBase(m_SideID) == this)
    {
        ActionRequestForce(AN_CmnActStand);
        m_EntryBattle = true;
        m_EntryBattleDoing = true;
    }
}

const char* OBJ_CCharBase::GetContextActionName(const CXXBYTE<32>& actName)
{
    if (strncmp(actName.GetStr(), ANCX_Neutral.GetStr(), 0x20) != 0) return nullptr;

    if (IsLeaveRequest())
    {
        if (IsDead()) return AN_CmnActHizakuzure.GetStr();
        if (m_PlayerFlag3 & PLFLG3_MOM_TEMP_DIE) return AN_CmnActHizakuzure.GetStr();
        return AN_CmnActChangeLeave.GetStr();
    }

    if (m_ActionFlag & OBJ_ACT_AIR || GetPosY() > 0) return AN_CmnActJump.GetStr();
    if (m_ExKizetsu) return "ExKizetsu";
    if (m_KizetsuTime) return AN_CmnActKizetsu.GetStr();
    if (m_PlayerFlag & PLFLG_CROUCH) return AN_CmnActCrouch.GetStr();
    return AN_CmnActStand.GetStr();
}

int32_t OBJ_CCharBase::CommandFlagUpdate()
{
    const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
        GetBattleObjectManager();

    auto inputAnalayzer = objManager->BattleInputAnalyzer(m_SideID, m_MemberID);

    // TODO training menu

    auto preTenkey = m_PreTenkey;

    if (!(m_PlayerFlag & PLFLG2_CPU))
    {
        m_WinActionButton = 0;

        if (inputAnalayzer->IsHold(RECFLG_A)) m_WinActionButton = 1;
        if (inputAnalayzer->IsHold(RECFLG_B)) m_WinActionButton = 2;
        if (inputAnalayzer->IsHold(RECFLG_C)) m_WinActionButton = 3;
        if (inputAnalayzer->IsHold(RECFLG_D)) m_WinActionButton = 4;
        if (inputAnalayzer->IsHold(RECFLG_E)) m_WinActionButton = 5;
        if (inputAnalayzer->IsHold(RECFLG_F)) m_WinActionButton = 6;
    }

    auto pressA = inputAnalayzer->IsTrgOn(RECFLG_A);
    auto pressB = inputAnalayzer->IsTrgOn(RECFLG_B);
    auto pressC = inputAnalayzer->IsTrgOn(RECFLG_C);
    auto pressD = inputAnalayzer->IsTrgOn(RECFLG_D);
    auto pressE = inputAnalayzer->IsTrgOn(RECFLG_E);
    auto pressF = inputAnalayzer->IsTrgOn(RECFLG_F);
    auto pressG = inputAnalayzer->IsTrgOn(RECFLG_G);
    auto pressH = inputAnalayzer->IsTrgOn(RECFLG_H);

    auto releaseA = inputAnalayzer->IsTrgOff(RECFLG_A);
    auto releaseB = inputAnalayzer->IsTrgOff(RECFLG_B);
    auto releaseC = inputAnalayzer->IsTrgOff(RECFLG_C);
    auto releaseD = inputAnalayzer->IsTrgOff(RECFLG_D);
    auto releaseE = inputAnalayzer->IsTrgOff(RECFLG_E);
    auto releaseF = inputAnalayzer->IsTrgOff(RECFLG_F);
    auto releaseG = inputAnalayzer->IsTrgOff(RECFLG_G);
    auto releaseH = inputAnalayzer->IsTrgOff(RECFLG_H);

    auto holdA = inputAnalayzer->IsHold(RECFLG_A);
    auto holdB = inputAnalayzer->IsHold(RECFLG_B);
    auto holdC = inputAnalayzer->IsHold(RECFLG_C);
    auto holdD = inputAnalayzer->IsHold(RECFLG_D);
    auto holdE = inputAnalayzer->IsHold(RECFLG_E);
    auto holdF = inputAnalayzer->IsHold(RECFLG_F);
    auto holdG = inputAnalayzer->IsHold(RECFLG_G);
    auto holdH = inputAnalayzer->IsHold(RECFLG_H);

    {
        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &releaseA - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
            m_BtnLastTrgOffCount[0] = 0;
        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &pressA - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr)
        {
            int32_t btnHoldCount = 0;

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdA - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
                btnHoldCount = m_BtnHoldCount[0];

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdA - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr || btnHoldCount < 1)
            {
                m_BtnHoldCount[0] = 0;
                m_BtnHoldCountWithoutGuard[0] = 0;
            }
            else
            {
                m_BtnHoldCount[0] = btnHoldCount + 1;

                if (!(m_CollisionFlag & OBJ_CLSN_GUARD_IMPACT) && !(m_PlayerFlag & PLFLG_GUARD_POSING) && m_GuardSustain
                    <= 0)
                {
                    m_BtnHoldCountWithoutGuard[0]++;
                    if (btnHoldCount == 1) m_BtnHoldCountWithoutGuard[0]++;
                }
            }
        }
        else
        {
            m_BtnLastTrgCount[0] = 0;
            m_BtnHoldCount[0] = 1;
        }

        if (m_BtnLastTrgCount[0] < 9999) m_BtnLastTrgCount[0]++;
        if (m_BtnLastTrgOffCount[0] < 9999) m_BtnLastTrgOffCount[0]++;
        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &releaseB - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
            m_BtnLastTrgOffCount[1] = 0;
        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &pressB - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr)
        {
            int32_t btnHoldCount = 0;

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdB - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
                btnHoldCount = m_BtnHoldCount[1];

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdB - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr || btnHoldCount < 1)
            {
                m_BtnHoldCount[1] = 0;
                m_BtnHoldCountWithoutGuard[1] = 0;
            }
            else
            {
                m_BtnHoldCount[1] = btnHoldCount + 1;

                if (!(m_CollisionFlag & OBJ_CLSN_GUARD_IMPACT) && !(m_PlayerFlag & PLFLG_GUARD_POSING) && m_GuardSustain
                    <= 0)
                {
                    m_BtnHoldCountWithoutGuard[1]++;
                    if (btnHoldCount == 1) m_BtnHoldCountWithoutGuard[1]++;
                }
            }
        }
        else
        {
            m_BtnLastTrgCount[1] = 0;
            m_BtnHoldCount[1] = 1;
        }

        if (m_BtnLastTrgCount[1] < 9999) m_BtnLastTrgCount[1]++;
        if (m_BtnLastTrgOffCount[1] < 9999) m_BtnLastTrgOffCount[1]++;

        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &releaseB - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
            m_BtnLastTrgOffCount[1] = 0;
        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &pressB - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr)
        {
            int32_t btnHoldCount = 0;

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdB - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
                btnHoldCount = m_BtnHoldCount[1];

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdB - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr || btnHoldCount < 1)
            {
                m_BtnHoldCount[1] = 0;
                m_BtnHoldCountWithoutGuard[1] = 0;
            }
            else
            {
                m_BtnHoldCount[1] = btnHoldCount + 1;

                if (!(m_CollisionFlag & OBJ_CLSN_GUARD_IMPACT) && !(m_PlayerFlag & PLFLG_GUARD_POSING) && m_GuardSustain
                    <= 0)
                {
                    m_BtnHoldCountWithoutGuard[1]++;
                    if (btnHoldCount == 1) m_BtnHoldCountWithoutGuard[1]++;
                }
            }
        }
        else
        {
            m_BtnLastTrgCount[1] = 0;
            m_BtnHoldCount[1] = 1;
        }

        if (m_BtnLastTrgCount[1] < 9999) m_BtnLastTrgCount[1]++;
        if (m_BtnLastTrgOffCount[1] < 9999) m_BtnLastTrgOffCount[1]++;

        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &releaseC - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
            m_BtnLastTrgOffCount[2] = 0;
        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &pressC - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr)
        {
            int32_t btnHoldCount = 0;

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdC - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
                btnHoldCount = m_BtnHoldCount[2];

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdC - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr || btnHoldCount < 1)
            {
                m_BtnHoldCount[2] = 0;
                m_BtnHoldCountWithoutGuard[2] = 0;
            }
            else
            {
                m_BtnHoldCount[2] = btnHoldCount + 1;

                if (!(m_CollisionFlag & OBJ_CLSN_GUARD_IMPACT) && !(m_PlayerFlag & PLFLG_GUARD_POSING) && m_GuardSustain
                    <= 0)
                {
                    m_BtnHoldCountWithoutGuard[2]++;
                    if (btnHoldCount == 1) m_BtnHoldCountWithoutGuard[2]++;
                }
            }
        }
        else
        {
            m_BtnLastTrgCount[2] = 0;
            m_BtnHoldCount[2] = 1;
        }

        if (m_BtnLastTrgCount[2] < 9999) m_BtnLastTrgCount[2]++;
        if (m_BtnLastTrgOffCount[2] < 9999) m_BtnLastTrgOffCount[2]++;

        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &releaseD - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
            m_BtnLastTrgOffCount[3] = 0;
        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &pressD - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr)
        {
            int32_t btnHoldCount = 0;

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdD - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
                btnHoldCount = m_BtnHoldCount[3];

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdD - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr || btnHoldCount < 1)
            {
                m_BtnHoldCount[3] = 0;
                m_BtnHoldCountWithoutGuard[3] = 0;
            }
            else
            {
                m_BtnHoldCount[3] = btnHoldCount + 1;

                if (!(m_CollisionFlag & OBJ_CLSN_GUARD_IMPACT) && !(m_PlayerFlag & PLFLG_GUARD_POSING) && m_GuardSustain
                    <= 0)
                {
                    m_BtnHoldCountWithoutGuard[3]++;
                    if (btnHoldCount == 1) m_BtnHoldCountWithoutGuard[3]++;
                }
            }
        }
        else
        {
            m_BtnLastTrgCount[3] = 0;
            m_BtnHoldCount[3] = 1;
        }

        if (m_BtnLastTrgCount[3] < 9999) m_BtnLastTrgCount[3]++;
        if (m_BtnLastTrgOffCount[3] < 9999) m_BtnLastTrgOffCount[3]++;

        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &releaseE - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
            m_BtnLastTrgOffCount[4] = 0;
        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &pressE - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr)
        {
            int32_t btnHoldCount = 0;

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdE - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
                btnHoldCount = m_BtnHoldCount[4];

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdE - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr || btnHoldCount < 1)
            {
                m_BtnHoldCount[4] = 0;
                m_BtnHoldCountWithoutGuard[4] = 0;
            }
            else
            {
                m_BtnHoldCount[4] = btnHoldCount + 1;

                if (!(m_CollisionFlag & OBJ_CLSN_GUARD_IMPACT) && !(m_PlayerFlag & PLFLG_GUARD_POSING) && m_GuardSustain
                    <= 0)
                {
                    m_BtnHoldCountWithoutGuard[4]++;
                    if (btnHoldCount == 1) m_BtnHoldCountWithoutGuard[4]++;
                }
            }
        }
        else
        {
            m_BtnLastTrgCount[4] = 0;
            m_BtnHoldCount[4] = 1;
        }

        if (m_BtnLastTrgCount[4] < 9999) m_BtnLastTrgCount[4]++;
        if (m_BtnLastTrgOffCount[4] < 9999) m_BtnLastTrgOffCount[4]++;

        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &releaseF - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
            m_BtnLastTrgOffCount[5] = 0;
        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &pressF - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr)
        {
            int32_t btnHoldCount = 0;

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdF - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
                btnHoldCount = m_BtnHoldCount[5];

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdF - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr || btnHoldCount < 1)
            {
                m_BtnHoldCount[5] = 0;
                m_BtnHoldCountWithoutGuard[5] = 0;
            }
            else
            {
                m_BtnHoldCount[5] = btnHoldCount + 1;

                if (!(m_CollisionFlag & OBJ_CLSN_GUARD_IMPACT) && !(m_PlayerFlag & PLFLG_GUARD_POSING) && m_GuardSustain
                    <= 0)
                {
                    m_BtnHoldCountWithoutGuard[5]++;
                    if (btnHoldCount == 1) m_BtnHoldCountWithoutGuard[5]++;
                }
            }
        }
        else
        {
            m_BtnLastTrgCount[5] = 0;
            m_BtnHoldCount[5] = 1;
        }

        if (m_BtnLastTrgCount[5] < 9999) m_BtnLastTrgCount[5]++;
        if (m_BtnLastTrgOffCount[5] < 9999) m_BtnLastTrgOffCount[5]++;

        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &releaseG - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
            m_BtnLastTrgOffCount[6] = 0;
        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &pressG - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr)
        {
            int32_t btnHoldCount = 0;

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdG - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
                btnHoldCount = m_BtnHoldCount[6];

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdG - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr || btnHoldCount < 1)
            {
                m_BtnHoldCount[6] = 0;
                m_BtnHoldCountWithoutGuard[6] = 0;
            }
            else
            {
                m_BtnHoldCount[6] = btnHoldCount + 1;

                if (!(m_CollisionFlag & OBJ_CLSN_GUARD_IMPACT) && !(m_PlayerFlag & PLFLG_GUARD_POSING) && m_GuardSustain
                    <= 0)
                {
                    m_BtnHoldCountWithoutGuard[6]++;
                    if (btnHoldCount == 1) m_BtnHoldCountWithoutGuard[6]++;
                }
            }
        }
        else
        {
            m_BtnLastTrgCount[6] = 0;
            m_BtnHoldCount[6] = 1;
        }

        if (m_BtnLastTrgCount[6] < 9999) m_BtnLastTrgCount[6]++;
        if (m_BtnLastTrgOffCount[6] < 9999) m_BtnLastTrgOffCount[6]++;

        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &releaseH - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
            m_BtnLastTrgOffCount[7] = 0;
        if ((uintptr_t)m_BtnHoldCountWithoutGuard + &pressH - (uintptr_t)this - offsetof(
            OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr)
        {
            int32_t btnHoldCount = 0;

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdH - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard))
                btnHoldCount = m_BtnHoldCount[7];

            if ((uintptr_t)m_BtnHoldCountWithoutGuard + &holdH - (uintptr_t)this - offsetof(
                OBJ_CCharBase, m_BtnHoldCountWithoutGuard) == nullptr || btnHoldCount < 1)
            {
                m_BtnHoldCount[7] = 0;
                m_BtnHoldCountWithoutGuard[7] = 0;
            }
            else
            {
                m_BtnHoldCount[7] = btnHoldCount + 1;

                if (!(m_CollisionFlag & OBJ_CLSN_GUARD_IMPACT) && !(m_PlayerFlag & PLFLG_GUARD_POSING) && m_GuardSustain
                    <= 0)
                {
                    m_BtnHoldCountWithoutGuard[7]++;
                    if (btnHoldCount == 1) m_BtnHoldCountWithoutGuard[7]++;
                }
            }
        }
        else
        {
            m_BtnLastTrgCount[7] = 0;
            m_BtnHoldCount[7] = 1;
        }

        if (m_BtnLastTrgCount[7] < 9999) m_BtnLastTrgCount[7]++;
        if (m_BtnLastTrgOffCount[7] < 9999) m_BtnLastTrgOffCount[7]++;
    }

    if (pressA)
    {
        m_BtnRendaCount[0]++;
        m_BtnRendaAddTime[0] = 12;
    }
    else
    {
        if (m_BtnRendaAddTime[0] > 0)
        {
            m_BtnRendaAddTime[0]--;
            m_BtnRendaAddTime[0] = std::max(m_BtnRendaAddTime[0], 0);
        }
    }
    
    if (pressB)
    {
        m_BtnRendaCount[1]++;
        m_BtnRendaAddTime[1] = 12;
    }
    else
    {
        if (m_BtnRendaAddTime[1] > 0)
        {
            m_BtnRendaAddTime[1]--;
            m_BtnRendaAddTime[1] = std::max(m_BtnRendaAddTime[1], 0);
        }
    }
    
    if (pressC)
    {
        m_BtnRendaCount[2]++;
        m_BtnRendaAddTime[2] = 12;
    }
    else
    {
        if (m_BtnRendaAddTime[2] > 0)
        {
            m_BtnRendaAddTime[2]--;
            m_BtnRendaAddTime[2] = std::max(m_BtnRendaAddTime[2], 0);
        }
    }
    
    if (pressD)
    {
        m_BtnRendaCount[3]++;
        m_BtnRendaAddTime[3] = 12;
    }
    else
    {
        if (m_BtnRendaAddTime[3] > 0)
        {
            m_BtnRendaAddTime[3]--;
            m_BtnRendaAddTime[3] = std::max(m_BtnRendaAddTime[3], 0);
        }
    }
    
    if (pressE)
    {
        m_BtnRendaCount[4]++;
        m_BtnRendaAddTime[4] = 12;
    }
    else
    {
        if (m_BtnRendaAddTime[4] > 0)
        {
            m_BtnRendaAddTime[4]--;
            m_BtnRendaAddTime[4] = std::max(m_BtnRendaAddTime[4], 0);
        }
    }
    
    if (pressF)
    {
        m_BtnRendaCount[5]++;
        m_BtnRendaAddTime[5] = 12;
    }
    else
    {
        if (m_BtnRendaAddTime[5] > 0)
        {
            m_BtnRendaAddTime[5]--;
            m_BtnRendaAddTime[5] = std::max(m_BtnRendaAddTime[5], 0);
        }
    }
    
    if (pressG)
    {
        m_BtnRendaCount[6]++;
        m_BtnRendaAddTime[6] = 12;
    }
    else
    {
        if (m_BtnRendaAddTime[6] > 0)
        {
            m_BtnRendaAddTime[6]--;
            m_BtnRendaAddTime[6] = std::max(m_BtnRendaAddTime[6], 0);
        }
    }
    
    if (pressH)
    {
        m_BtnRendaCount[7]++;
        m_BtnRendaAddTime[7] = 12;
    }
    else
    {
        if (m_BtnRendaAddTime[7] > 0)
        {
            m_BtnRendaAddTime[7]--;
            m_BtnRendaAddTime[7] = std::max(m_BtnRendaAddTime[7], 0);
        }
    }

    if (IsTrgBtnX(0, 0)
        || IsTrgBtnX(0, 1)
        || IsTrgBtnX(0, 2)
        || IsTrgBtnX(0, 3)) m_UkemiBtnTime = 5;
    else if (m_UkemiBtnTime > 0) m_UkemiBtnTime--;

    if (m_DashTime1st[0] == 0)
    {
        if (m_DashTime2nd[0] != 0)
        {
            
        }
    }

    // TODO finish command flag update

    return 0;
}

bool OBJ_CCharBase::IsDead()
{
    return OBJ_CBase::IsDead() || !m_Entry;
}

void OBJ_CCharBase::SetCooldownTime(int32_t frame, int32_t innerFrame, bool bPlaySE)
{
    const auto battleScene = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene());

    auto cooldownTime = frame + battleScene->GetBattleObjectManager()->GetTeamManager(m_SideID)->GetMainPlayer()->
                                             ply_CooldownHoseiTime;
    if (cooldownTime < 0) cooldownTime = 1;
    m_CooldownTime = cooldownTime;
    m_CooldownTimeMax = cooldownTime;
    m_InnerCooldownTime = innerFrame;
    m_bPlayReadySE = bPlaySE;
}
