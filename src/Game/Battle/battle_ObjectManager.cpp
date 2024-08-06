#include "battle_ObjectManager.h"
#include "Object/Char/char_ActCmn.h"
#include <cstring>
#include <REDGameCommon.h>
#include <Scene/scene_Battle.h>
#include "AASystemRED.h"

void BATTLE_CObjectManager::ExecuteObjectManagerEvent(BattleEventManager* pBEM)
{
    if (!pBEM) return;

    for (int i = 0; i < pBEM->GetBOMEventCount(); i++)
    {
        ExecuteObjectManagerEvent(pBEM->GetBOMEvent(i));
        pBEM->ResetBOMEvent();
    }
}

void BATTLE_CObjectManager::ExecuteObjectManagerEvent(const BOMEventInfo* pEvent)
{
    if (!pEvent) return;

    auto id = (BOM_EVENT)(pEvent->eventID - 1);
    switch (id)
    {
    case BOM_EVENT_ENTRY:
    {
        BOM_RoundAndEasyResetInitialize(true);
        std::memset(&m_EventData, 0, sizeof(SEventData));
        m_CharVector[pEvent->param0].ActionRequestForce(AN_CmnActEntryWait);
        auto charOffset = 0;
        if (!pEvent->param0) charOffset = 3;
        m_CharVector[charOffset].ActionRequestForce(AN_CmnActEntryWait);
    }
    default:
        break;
    }
}

int32_t BATTLE_CObjectManager::BOM_RoundAndEasyResetInitialize(bool use2ndInitialize)
{
    m_BattleCheckSumTimeCount = 0;
    m_BattleCheckSumErrorFound = 0;
    auto battleScene = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene());
    if (battleScene->GetBattleState()->GetWinner() == SIDE_ID_INVALID)
    {
        m_BurstVal[0] = m_PreBurstVal[0];
        m_MatchStaticValue0[0] = m_PreMatchStaticValue0[0];
        m_MatchStaticValue1[0] = m_PreMatchStaticValue1[0];
        m_Rakusyo[0] = m_PreRakusyo[0];
        m_YogoreLevel[0] = m_PreYogoreLevel[0];
        m_BurstVal[1] = m_PreBurstVal[1];
        m_MatchStaticValue0[1] = m_PreMatchStaticValue0[1];
        m_MatchStaticValue1[1] = m_PreMatchStaticValue1[1];
        m_Rakusyo[1] = m_PreRakusyo[1];
        m_YogoreLevel[1] = m_PreYogoreLevel[1];
    }

    m_DokiDokiStopByDokiDokiKill = 0;
    m_DokiDokiStopIgnoreTime = 0;
    m_EventVsVoiceRandomIndex = -1;
    m_EventVsVoiceNum = -1;
    m_TrialBossHP = 0;
    m_TrialBossHPMax = 0;
    m_TrialBossBarrier = 0;
    m_TrialExVal0 = 0;
    m_TrialExVal1 = 0;
    m_TrialExVal2 = 0;
    m_TrialExVal3 = 0;

    int order[2] = { 0, 1 };

    for (int i = 0; i < 2; i++)
    {
        auto rand = AASystemRED::GetInstance()->GetRandomManager().Get(1)->GenS32() % 2;
        auto val = order[i];
        order[i] = order[rand];
        order[rand] = val;
    }

    for (int i = 0; i < m_UsesObjPtrVectorNum; i++)
    {
        auto obj = m_ObjPtrVector[i];
        if (!obj) break;
        obj->ReleaseResource();
        if (obj->m_IsDirty)
        {
            obj->ObjectConstructor_ForObject();
            if (obj->m_IsPlayerObj) ((OBJ_CCharBase*)obj)->ObjectConstructor_ForPlayer();
        }
    }

    m_MultiBufferLarge.Reset();
    m_MultiBufferSmall.Reset();

    m_UniqIDGen = 1;
    m_AttackHitUniqIDGen = 1;
    m_AtkHitCount = 0;
    m_ActionChangeCount = 0;
    m_WorldBlacker = false;
    m_bBackGroundStop = false;

    for (int i = 0; i < 2; i++)
    {
        auto playerIdx = order[i];
        auto chara = &m_SortedObjPtrVector[3 * playerIdx];
        for (int j = 0; j < 3; j++)
        {
            auto initArg = new CInitializeObjectExArg();
            initArg->actName = "";
            initArg->argparent = nullptr;
            initArg->flag = 0;
            initArg->exPoint = POS_WORLD_ZERO;
            initArg->memberID = MemberID_01;
            initArg->fixedMemberID = MemberID_01;
            initArg->isPlayer = true;

            auto charObj = &m_CharVector[(playerIdx & 0xff) * 3 + (j & 0xFF)];
            if (charObj != nullptr)
            {
                charObj->m_CreateArgFromParent.m_CreateArg_OffsetPosZ = 0;
                charObj->m_CreateArgFromParent.m_CreateArg_Delay = 0;
                charObj->m_CreateArgFromParent.m_CreateArg_SocketName = "";
                charObj->m_CreateArgFromParent.m_CreateArg_Angle = 0;
                charObj->m_CreateArgFromParent.m_CreateArg_Angle = 0;
                charObj->m_CreateArgFromParent.m_CreateArg_OffsetPosX = 0;
                charObj->m_CreateArgFromParent.m_CreateArg_OffsetPosY = 0;
                charObj->m_CreateArgFromParent.m_CreateArg_ScaleX = 1000;
                charObj->m_CreateArgFromParent.m_CreateArg_ScaleY = 1000;
                charObj->m_CreateArgFromParent.m_CreateArg_ScaleZ = 1000;
                charObj->m_CreateArgFromParent.m_CreateArg_Hikitsugi0 = 0;
                charObj->m_CreateArgFromParent.m_CreateArg_Hikitsugi1 = 0;
                charObj->m_CreateArgFromParent.m_CreateArg_HkrColor = 0;
                charObj->m_CreateArgFromParent.m_CreateArg_MltColor = -1;
                charObj->m_CreateArgFromParent.m_CreateArg_TransPriority = 0;
                charObj->m_CreateArgFromParent.m_CreateArg_Direction = PTDIR_SELF;
                charObj->m_CreateArgFromParent.m_CreateArg_SocketOwner = CO_NULL;
                charObj->m_CreateArgFromParent.m_CreateArg_LinkMaterialParticle = 0;
                charObj->m_CreateArgFromParent.m_CreateArg_ParticleUnuseMatInstance = 0;
                charObj->m_CreateArgFromParent.m_CreateArg_PointLightSide = -1;
                charObj->m_CreateArgFromParent.m_CreateArg_PointLightMember = -1;

                charObj->ObjectInitializeOnActivate(initArg);
            }
            *chara = charObj;
            ++chara;
        }
    }

    auto teamMemberIndex = &m_TeamManager[0].GetMemberIndexArray()[1];
    auto charObj = &m_CharVector[2];

    for (int i = 0; i < 2; i++)
    {
        auto memberID = MemberID_01;
        if ((charObj - 2)->IsEntry()) memberID = (charObj - 2)->m_FixedMemberID;
        *(teamMemberIndex - 1) = memberID;

        memberID = MemberID_02;
        if ((charObj - 1)->IsEntry()) memberID = (charObj - 1)->m_FixedMemberID;
        *teamMemberIndex = memberID;

        memberID = MemberID_03;
        if ((charObj)->IsEntry()) memberID = (charObj)->m_FixedMemberID;
        *(teamMemberIndex + 1) = memberID;

        m_TeamManager->RoundReset();
        m_TeamManager->Update();
    }

    return 0;
}
