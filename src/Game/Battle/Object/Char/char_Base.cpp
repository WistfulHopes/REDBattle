#include "char_Base.h"

#include <Game/Scene/scene_Battle.h>

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
