#include "char_Base.h"

#include <Game/Scene/scene_Battle.h>

#include "char_ActCmn.h"

void OBJ_CCharBase::ObjectConstructor_ForPlayer()
{
    const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
        GetBattleObjectManager();

    m_pBBSFile = objManager->GetScriptData(m_SideID, m_MemberID, ScriptData_Body);
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
