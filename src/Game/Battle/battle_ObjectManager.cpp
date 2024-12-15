#include "battle_ObjectManager.h"
#include "Object/Char/char_ActCmn.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <Game/REDGameCommon.h>
#include <vector>
#include <Game/Scene/scene_Battle.h>
#include "AALib/AASystemRED.h"

constexpr int StartupPositionX[2][3]{{-252000, -504000, -756000}, {252000, 504000, 756000}};

int32_t IsControlPrioritySmallSub_(const void* _a, const void* _b)
{
    auto objA = *(OBJ_CCharBase**)_a;
    auto objB = *(OBJ_CCharBase**)_b;

    if (objA->m_ActiveState == ACTV_ACTIVE || objB->m_ActiveState == ACTV_ACTIVE)
    {
        if ((uint8_t)(objA->m_ObjFlag4 >> 19) ^ (uint8_t)(objB->m_ObjFlag4 >> 19) & 1)
        {
            return (objA->m_ObjFlag4 & OBJ_FLG_4_HIGH_PRIORITY) == 0;
        }
        if (objA->m_IsPlayerObj == objB->m_IsPlayerObj)
        {
            if (objA->m_IsPlayerObj || objB->m_IsPlayerObj)
            {
                auto aIsPlayer = objA->GetMainPlayerBase(objA->m_SideID) == objA;
                auto bIsPlayer = objB->GetMainPlayerBase(objB->m_SideID) == objB;
                if (!objB->m_IsPlayerObj) bIsPlayer = false;
                if (aIsPlayer != bIsPlayer)
                {
                    if (!objA->m_IsPlayerObj) aIsPlayer = false;
                    return aIsPlayer;
                }
            }
            if (objA->m_ObjectSortPriority == objB->m_ObjectSortPriority)
            {
                if (objA->m_AtkPriority == objB->m_AtkPriority)
                {
                    if (objA->m_UniqID == objB->m_UniqID)
                    {
                        return 0;
                    }
                    return objA->m_UniqID < objB->m_UniqID;
                }
                return objA->m_AtkPriority < objB->m_AtkPriority;
            }
            return objA->m_ObjectSortPriority < objB->m_ObjectSortPriority;
        }
        return !objA->m_IsPlayerObj;
    }
    return objA->m_ActiveState != ACTV_ACTIVE;
}

int32_t IsControlPriorityBig_(const void* _a, const void* _b)
{
    if (IsControlPrioritySmallSub_(_a, _b)) return 1;
    return -1;
}

void BATTLE_CObjectManager::ExecuteObjectManagerEvent(BattleEventManager* pBEM)
{
    if (!pBEM) return;

    for (uint32_t i = 0; i < pBEM->GetBOMEventCount(); i++)
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

BATTLE_CObjectManager::BATTLE_CObjectManager()
{
    m_MultiBufferLarge.Reset();
    m_MultiBufferSmall.Reset();
    m_IchigekiBGMName = "";
    m_BGSaturation.Init();
    m_CommonActionHash.Release();
}

int32_t BATTLE_CObjectManager::BOM_MatchOneceInitialize(bool bIs2ndCall)
{
    if (!bIs2ndCall)
        m_BOMRandomSeed = AASystemRED::GetInstance()->GetRandomManager().Get(1)->GenU32();

    m_BattleCheckSumTimeCount = 0;
    m_BattleCheckSum = 0;
    m_BattleCheckSumErrorFound = 0;
    m_BattleCheckSumErrorFoundList[0] = 0;
    m_BattleCheckSumErrorFoundList[1] = 0;
    m_RequestFadeOut = false;
    m_bForceBGHide = false;

    m_BurstVal[0] = 15000;
    m_BurstVal[1] = 15000;
    m_MatchStaticValue0[0] = 0;
    m_MatchStaticValue0[1] = 0;
    m_MatchStaticValue1[0] = 0;
    m_MatchStaticValue1[1] = 0;
    m_Rakusyo[0] = 0;
    m_Rakusyo[1] = 0;
    m_YogoreLevel[0] = 0;
    m_YogoreLevel[1] = 0;

    m_PreBurstVal[0] = 15000;
    m_PreBurstVal[1] = 15000;
    m_PreMatchStaticValue0[0] = 0;
    m_PreMatchStaticValue0[1] = 0;
    m_PreMatchStaticValue1[0] = 0;
    m_PreMatchStaticValue1[1] = 0;
    m_PreRakusyo[0] = 0;
    m_PreRakusyo[1] = 0;
    m_PreYogoreLevel[0] = 0;
    m_PreYogoreLevel[1] = 0;


    m_YogoreLv[0][0] = 0;
    m_YogoreLv[0][1] = 0;
    m_YogoreLv[1][0] = 0;
    m_YogoreLv[1][1] = 0;
    m_YogoreLv[2][0] = 0;
    m_YogoreLv[2][1] = 0;
    m_BattleHandiCap[0] = HANDICAP_TYPE_LOWEST;
    m_BattleHandiCap[1] = HANDICAP_TYPE_LOWEST;

    m_OnlineTraining_IsSwitch = false;
    m_OnlineTraining_IsSwitchHold[0] = 0;
    m_OnlineTraining_IsSwitchHold[1] = 1;
    m_OnlineTraining_SwitchCoolTime = 0;
    m_OnlineTraining_IsResetDone = false;
    m_OnlineTraining_StartSideFrip = false;
    m_OnlineTraining_StartPos = MAAI_TYPE_NORMAL_GAME;
    m_OnlineTraining_Wins[0] = 0;
    m_OnlineTraining_Wins[1] = 0;

    m_LastLoadedCharID[0] = REDGameCommon::GetInstance()->GetBattleCharaID(SIDE_BEGIN, MemberID_Begin);
    m_LastLoadedCharID[1] = REDGameCommon::GetInstance()->GetBattleCharaID(SIDE_2P, MemberID_Begin);

    for (auto& chara : m_CharVector)
    {
        chara.SetEntry(true);
    }
    for (int i = 0; i < 2; i++)
    {
        m_TeamManager[i].Initialize(static_cast<SIDE_ID>(i));
        m_TeamManager[i].SetMember(MemberID_01, &m_CharVector[i * 3]);
        m_TeamManager[i].SetMember(MemberID_02, &m_CharVector[i * 3 + 1]);
        m_TeamManager[i].SetMember(MemberID_03, &m_CharVector[i * 3 + 2]);
        m_TeamManager[i].RoundReset();
    }

    m_DrawTimer = 0;
    m_CommonActionHash.Release();
    for (auto& name : CmnActNameTable)
    {
        const auto hash = AA_MakeHashEasy(name->GetStr());
        m_CommonActionHash.Insert(*name, hash);
    }

    m_MultiBufferLarge.Reset();
    m_MultiBufferSmall.Reset();

    memset(m_ObjPtrVector, 0, sizeof(m_ObjPtrVector));
    memset(m_SortedObjPtrVector, 0, sizeof(m_SortedObjPtrVector));
    m_UsesObjPtrVectorNum = 0;

    int numActivePlayers = 0;

    for (int i = 0; i < CHARA_OBJECT_NUM; i++)
    {
        if (m_CharVector[i].IsEntry())
        {
            numActivePlayers++;
            m_ObjPtrVector[i] = &m_CharVector[i];
        }
    }

    for (int i = 0; i < OBJECT_NUM; i++)
    {
        m_ObjPtrVector[i + numActivePlayers] = &m_ObjVector[i];
    }

    m_UsesObjPtrVectorNum = 100 + numActivePlayers;
    m_ActiveObjectCount = 0;
    m_CreateChokugoObjectCount = 0;
    m_NoActiveObjectCount = 0;
    m_EtcActiveObjectCount = 0;
    m_ActiveForceEffectNum = 0;

    return 0;
}

int32_t BATTLE_CObjectManager::BOM_RoundAndEasyResetInitialize(bool use2ndInitialize)
{
    m_BattleCheckSumTimeCount = 0;
    m_BattleCheckSumErrorFound = 0;
    const auto battleScene = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene());
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

    int order[2] = {0, 1};

    for (int& i : order)
    {
        auto rand = AASystemRED::GetInstance()->GetRandomManager().Get(1)->GenS32() % 2;
        auto val = i;
        i = order[rand];
        order[rand] = val;
    }

    for (uint32_t i = 0; i < m_UsesObjPtrVectorNum; i++)
    {
        auto obj = m_ObjPtrVector[i];
        if (!obj) break;
        obj->ReleaseResource();
        // if (obj->m_IsDirty)
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

    for (int playerIdx : order)
    {
        auto chara = &m_SortedObjPtrVector[3 * playerIdx];
        for (int j = 0; j < 3; j++)
        {
            auto initArg = CInitializeObjectExArg();
            initArg.actName = "";
            initArg.argparent = nullptr;
            initArg.flag = 0;
            initArg.exPoint = POS_WORLD_ZERO;
            initArg.argsideID = (SIDE_ID)playerIdx;
            initArg.argFixedSideID = (SIDE_ID)playerIdx;
            initArg.memberID = (EMemberID)j;
            initArg.fixedMemberID = (EMemberID)j;
            initArg.isPlayer = true;

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

                charObj->ObjectInitializeOnActivate(&initArg);
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
        if (charObj->IsEntry()) memberID = charObj->m_FixedMemberID;
        *(teamMemberIndex + 1) = memberID;

        m_TeamManager->RoundReset();
        m_TeamManager->Update();
    }

    for (auto teamManager : m_TeamManager)
    {
        if (auto member = teamManager.GetMemberFromIndex(0))
        {
            auto enemy = m_TeamManager[1].GetMemberFromIndex(0);
            if (teamManager.GetSideID() == SIDE_2P) enemy = m_TeamManager[1].GetMemberFromIndex(0);

            member->m_pTargetObj.ClearPtr();
            member->m_pTargetObj.SetPtr(enemy);

            member->m_pAttackSlave[0].ClearPtr();
            member->m_pAttackSlave[0].SetPtr(enemy);

            member->m_pAttackSlaveNewest.ClearPtr();
            member->m_pAttackSlaveNewest.SetPtr(enemy);
        }
        if (auto member = teamManager.GetMemberFromIndex(1))
        {
            auto enemy = m_TeamManager[1].GetMemberFromIndex(0);
            if (teamManager.GetSideID() == SIDE_2P) enemy = m_TeamManager[1].GetMemberFromIndex(0);

            member->m_pTargetObj.ClearPtr();
            member->m_pTargetObj.SetPtr(enemy);

            member->m_pAttackSlave[0].ClearPtr();
            member->m_pAttackSlave[0].SetPtr(enemy);

            member->m_pAttackSlaveNewest.ClearPtr();
            member->m_pAttackSlaveNewest.SetPtr(enemy);
        }
        if (auto member = teamManager.GetMemberFromIndex(2))
        {
            auto enemy = m_TeamManager[1].GetMemberFromIndex(0);
            if (teamManager.GetSideID() == SIDE_2P) enemy = m_TeamManager[1].GetMemberFromIndex(0);

            member->m_pTargetObj.ClearPtr();
            member->m_pTargetObj.SetPtr(enemy);

            member->m_pAttackSlave[0].ClearPtr();
            member->m_pAttackSlave[0].SetPtr(enemy);

            member->m_pAttackSlaveNewest.ClearPtr();
            member->m_pAttackSlaveNewest.SetPtr(enemy);
        }
    }

    for (auto& battleInputAnalyzer : m_BattleInputAnalyzer)
    {
        memset(&battleInputAnalyzer, 0, sizeof(CBattleInputAnalyzer));
        battleInputAnalyzer.ResetRecFlagSafe(false);
    }
    AllActiveCheck();

    m_CharVector[order[0] * 3].FuncCall("cmn_EnvInit");

    for (const int i : order)
    {
        for (int j = 0; j < 3; j++)
        {
            if (m_CharVector[i * 3 + j].IsEntry())
            {
                m_CharVector[i * 3 + j].ZLine(ZLINE_FAR, ZLL_LV0);
            }
        }
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!&m_CharVector[i * 3 + j]) continue;
            m_CharVector[i * 3 + j].m_CharName = "";
            m_CharVector[i * 3 + j].FuncCall(FN_PreInit);
        }
    }

    for (int i = 0; i < 2; i++)
    {
        if (!&m_CharVector[i * 3]) continue;
        m_CharVector[i * 3].FuncCall(FN_PreInit2nd);
    }

    m_RoundTimer = 0;
    m_WorldStopper.ClearPtr();
    m_WorldStopTimer = 0;
    m_WorldStopTimerSelf = 0;
    m_FinishStopCount = 0;
    m_OverrideFinishStopTime[0] = -1;
    m_OverrideFinishStopTime[1] = -1;
    m_OverrideSlashUITime[0] = -1;
    m_OverrideSlashUITime[1] = -1;
    m_FadeOut01 = 1.0;
    m_BGSaturation.Init();
    m_BGMVolume.SetVal(1, 1, 0);
    m_AmbientVolume.SetVal(1, 1, 0);

    m_ShinSousaiTimer = 0;
    m_DiffusionFilter2LevelMax = 0;
    m_DiffusionFilter2SaturationMin = 1000;
    m_BOMFlag = m_BOMFlag & 0xF83FE417 | 0x200;
    m_BGFadeInSpeed = 0.1f;
    m_BGFadeOutSpeed = 0.1f;
    m_BGFadeAlpha = 0.25f;
    GameSpeedControlParam.StartGameSpeed = 100;
    GameSpeedControlParam.EndGameSpeed = 100;
    GameSpeedControlParam.CurrentGameSpeed = 0;
    GameSpeedControlParam.CurrentGameSpeedFrame = 0;
    GameSpeedControlParam.InFrame = 0;
    GameSpeedControlParam.StayFrame = 0;
    GameSpeedControlParam.OutFrame = 0;
    GameSpeedControlParam.CurrentFrame = 0;
    GameSpeedControlParam.InCurve = 0;
    GameSpeedControlParam.OutCurve = 0;
    GameSpeedControlParam.bRequestApplyParticle = false;
    GameSpeedControlParam.bCurrentApplyParticle = false;

    m_RequestFadeOut = false;
    m_bForceBGHide = false;
    m_bRequestDisplayFade = false;
    m_bDrawDisplayFade = false;

    // TODO reset screen pos

    m_BOMFlag &= ~1;

    m_WorldBlacker = false;
    m_bBackGroundStop = false;

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!&m_CharVector[i * 3 + j]) continue;
            m_CharVector[i * 3 + j].PlayerInitializeOnEasyReset();
        }
    }

    // TODO update screen pos

    m_BOMFlag &= ~10;
    m_IchigekiBGMRequestSideID = SIDE_ID_INVALID;
    m_StartInputTimeAC15 = 0;

    m_CharVector[3].m_Direction = 1;

    return 0;
}

OBJ_CBase* BATTLE_CObjectManager::GetNextSortedActiveObjectWithCreateChokugo(int32_t* itr)
{
    if (*itr < m_ActiveObjectCount)
    {
        *itr += 1;
        return m_SortedObjPtrVector[*itr - 1];
    }

    auto chokugoObjectCount = *itr - m_ActiveObjectCount;

    if (chokugoObjectCount >= m_CreateChokugoObjectCount) return nullptr;

    *itr += 1;
    return m_SortedObjPtrVector[chokugoObjectCount];
}

void BATTLE_CObjectManager::AllActiveCheck()
{
    m_ActiveObjectCount = 0;
    m_CreateChokugoObjectCount = 0;
    m_NoActiveObjectCount = 0;
    m_EtcActiveObjectCount = 0;

    std::vector<OBJ_CBase*> objVector{};
    auto inactiveCount = 0;
    auto activeCount = 0;

    if (m_UsesObjPtrVectorNum)
    {
        auto num = m_UsesObjPtrVectorNum;
        auto objPtr = m_ObjPtrVector;
        while (true)
        {
            auto active = (*objPtr)->m_ActiveState;
            switch (active)
            {
            case ACTV_ACTIVE:
                ++activeCount;
                objVector.push_back(*objPtr);
                break;
            case ACTV_REQ_ACTIVE:
                ++activeCount;
                (*objPtr)->m_ActiveState = ACTV_ACTIVE;
                objVector.push_back(*objPtr);
                break;
            case ACTV_REQ_NO_ACTIVE:
                (*objPtr)->OnDelete();
                inactiveCount++;
                break;
            default:
                break;
            }

            objPtr++;
            --num;
            if (!num)
            {
                break;
            }
        }
    }
    m_NoActiveObjectCount = (int32_t)objVector.size();
    m_EtcActiveObjectCount = inactiveCount;

    objVector.push_back(&m_ObjVector[OBJECT_NUM - 1]);

    for (uint32_t i = 0; i < objVector.size() - 1; i++)
    {
        if (objVector[i]->m_ActiveState == ACTV_REQ_NO_ACTIVE)
        {
            ++m_EtcActiveObjectCount;
            --activeCount;
        }
    }

    m_ActiveObjectCount = activeCount;

    auto sortCount = 0;

    if (m_UsesObjPtrVectorNum)
    {
        auto sortedObj = m_SortedObjPtrVector;
        for (int i = 0; i < m_ActiveObjectCount; i++)
        {
            if ((*sortedObj)->m_ActiveState == ACTV_ACTIVE)
            {
                sortCount = i;
                activeCount--;
                if (activeCount <= 0) break;
            }
        }
    }
    qsort(m_SortedObjPtrVector, sortCount + 1, sizeof(uintptr_t), IsControlPriorityBig_);
}

void BATTLE_CObjectManager::DeleteCheck()
{
    int i = 0;
    bool objDel;

    do
    {
        objDel = false;
        int chokugoObjCount = 0;
        auto vecIdx = 0;

        while (true)
        {
            OBJ_CBase* objPtr = nullptr;
            if (i == 0)
            {
                if (chokugoObjCount >= m_CreateChokugoObjectCount)
                {
                    if (chokugoObjCount - m_CreateChokugoObjectCount < m_ActiveObjectCount)
                    {
                        auto unk = m_ActiveObjectCount - (chokugoObjCount - m_CreateChokugoObjectCount);
                        chokugoObjCount++;
                        i++;
                        vecIdx++;

                        objPtr = m_ObjPtrVector[106 + unk];
                    }
                }
                else
                {
                    auto unk = m_CreateChokugoObjectCount - chokugoObjCount;
                    chokugoObjCount++;
                    i++;
                    vecIdx++;

                    objPtr = m_SortedObjPtrVector[106 + unk];
                }
            }
            else
            {
                if (chokugoObjCount >= m_ActiveObjectCount)
                {
                    auto unk = chokugoObjCount - m_ActiveObjectCount;

                    if (unk < m_CreateChokugoObjectCount)
                    {
                        chokugoObjCount++;
                        i++;
                        vecIdx++;
                        objPtr = m_CreateChokugoObjPtrVector[chokugoObjCount - m_ActiveObjectCount];
                    }
                }
                else
                {
                    chokugoObjCount++;
                    objPtr = m_CreateChokugoObjPtrVector[i];
                    i++;
                    vecIdx++;
                }
            }

            if (objPtr == nullptr) break;

            if (objPtr->ObjIsUsing())
            {
                if ((objPtr->m_ObjSignal & 0x200) == 0)
                {
                    auto changeToEliminate = objPtr->m_pLinkObject_ChangeToEliminate.GetPtr();

                    auto unk = objPtr->m_ObjSignal >> 10 & 1;

                    if (changeToEliminate)
                    {
                        auto tmp = unk | 2;
                        if ((changeToEliminate->m_ObjSignal & 0x200) == 0)
                        {
                            tmp = unk;
                        }
                        unk = tmp;

                        if (!changeToEliminate->ObjIsUsing()) unk |= 4;
                    }

                    if (unk)
                    {
                        objPtr->ObjUnactivate();
                        objDel = true;
                    }
                }
            }
        }

        i = 1 - i;
    }
    while (objDel);
}

void BATTLE_CObjectManager::ControlBattleObject()
{
    const auto battleScene = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene());
    if (battleScene->GetBattleState()->IsBattleDoing())
    {
        if (m_RoundTimer < 0xFFFFFFF) m_RoundTimer++;
    }
    if (m_UsesObjPtrVectorNum)
    {
        for (uint32_t i = 0; i < m_UsesObjPtrVectorNum; i++)
        {
            const auto objPtr = m_ObjPtrVector[i];
            switch (objPtr->m_ActiveState)
            {
            case ACTV_WAITING_BEGIN:
                if (!objPtr->m_WatchedCount) objPtr->m_ActiveState = ACTV_NOT_ACTIVE;
                break;
            case ACTV_WAITING_1:
                objPtr->m_ActiveState = ACTV_WAITING_BEGIN;
                break;
            case ACTV_WAITING_2:
                objPtr->m_ActiveState = ACTV_WAITING_1;
                break;
            default:
                break;
            }
        }
    }

    // TODO world stop (super freeze) countdown

    // TODO key renewal (input check)

    m_DrawTimer++;

    if (!battleScene->GetBattleState()->IsBattleTempStop())
    {
        battleScene->GetBattleState()->GetRoundTimer()->SetPause(false);
    }

    m_BOMFlag &= 0xFFFFFEDF;
    m_DiffusionFilter2LevelMax = 0;
    m_DiffusionFilter2SaturationMin = 1000;

    // TODO world stop (super freeze) update;

    for (int i = 0; i < m_ActiveObjectCount; i++)
    {
        if (!m_SortedObjPtrVector[i]) break;

        m_SortedObjPtrVector[i]->ControlPhase_PreFrameStep();
    }

    for (int i = 0; i < m_ActiveObjectCount; i++)
    {
        if (!m_SortedObjPtrVector[i]) break;

        m_SortedObjPtrVector[i]->m_ObjSignal &= 0xFFFFF1EF;
    }

    for (int i = 0; i < m_ActiveObjectCount; i++)
    {
        if (!m_SortedObjPtrVector[i]) break;

        m_SortedObjPtrVector[i]->m_ObjSignal &= ~0x10u;
        m_SortedObjPtrVector[i]->ControlPhase_FrameStep();
    }

    battleScene->GetBattleScreenManager()->StopScreenPositionUpdate(false);

    for (int i = 0; i < m_ActiveObjectCount; i++)
    {
        if (!m_SortedObjPtrVector[i]) break;

        m_SortedObjPtrVector[i]->ControlPhase_AfterFrameStep();
    }

    DeleteCheck();

    // TODO apply hit stop time

    AllActiveCheck();
    ControlBattleObject_Move();
    ControlBattleObject_HitCollision();
    AllActiveCheck();

    // TODO finish
}

void BATTLE_CObjectManager::ControlBattleObject_KeyRenewal()
{
    const auto battleScene = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene());
    if (battleScene->GetBattleState()->IsBattleDoing())
    {
        // TODO replay
    }

    if (m_BOMFlag & 1)
    {
        // TODO trial (mission)
    }

    auto padId1P = red::cmn::Side2Pad(SIDE_1P);
    auto padId2P = red::cmn::Side2Pad(SIDE_2P);

    // TODO training menu

    uint16_t keyFlagReg;

    for (int i = 0; i < 2; i++)
    {
        uint16_t recflg;
        for (int j = 0; j < 3; j++)
        {
            keyFlagReg = 0;
            recflg = 0;
            OBJ_CCharBase* player = &m_CharVector[i * 3 + j];

            // TODO online training

            if (!player->CheckPlayerFlag2(PLFLG2_CPU) || player->m_CPUInfo.m_RecipePlayStructType != 1)
            {
                // TODO replay recordings
                /* else */
                recflg = keyFlagReg;
            }
            else
                recflg = player->m_CPUInfo.m_KeyFlagReg;

            m_BattleInputAnalyzer[i * 3 + j].UpdateBattleInputAnalyzer(recflg);
            keyFlagReg = recflg;

            if (player->IsEntry() && player->GetMainPlayerBase(player->m_SideID) == player)
            {
                // TODO training key info update
            }
        }
    }

    // TODO training stuff

    for (auto player : m_CharVector)
    {
        if (player.IsEntry()) player.CommandFlagUpdate();
    }
}

void BATTLE_CObjectManager::ControlBattleObject_Move()
{
}

void BATTLE_CObjectManager::ControlBattleObject_HitCollision()
{
}

OBJ_CCharBase* BATTLE_CObjectManager::GetWinnerObj()
{
    if (m_WinnerSideID != SIDE_ID_NUM)
    {
        return m_TeamManager[m_WinnerSideID].GetMainPlayer();
    }
    return nullptr;
}

void BATTLE_CObjectManager::TransferAirActionCount(OBJ_CCharBase* dst, OBJ_CCharBase* src)
{
    int v3;
    int ply_AirJumpCountMax;
    int ply_AirDashCountMax;
    int m_HomingDashCountMax;
    int m_MikiwameMoveCountMax;

    if (dst->IsEntry() && src->IsEntry())
    {
        v3 = src->ply_AirDashCountMax - src->m_AirDashCount;
        ply_AirJumpCountMax = dst->ply_AirJumpCountMax;
        if (ply_AirJumpCountMax + src->m_AirJumpCount - src->ply_AirJumpCountMax < ply_AirJumpCountMax)
            ply_AirJumpCountMax += src->m_AirJumpCount - src->ply_AirJumpCountMax;
        dst->m_AirJumpCount = ply_AirJumpCountMax;
        ply_AirDashCountMax = dst->ply_AirDashCountMax;
        if (ply_AirDashCountMax - v3 < ply_AirDashCountMax)
            ply_AirDashCountMax = dst->ply_AirDashCountMax - v3;
        dst->m_AirDashCount = ply_AirDashCountMax;
        m_HomingDashCountMax = dst->m_HomingDashCountMax;
        m_HomingDashCountMax = std::min(src->m_HomingDashCount, m_HomingDashCountMax);
        dst->m_HomingDashCount = m_HomingDashCountMax;
        m_MikiwameMoveCountMax = dst->m_MikiwameMoveCountMax;
        m_MikiwameMoveCountMax = std::min(src->m_MikiwameMoveCount, m_MikiwameMoveCountMax);
        dst->m_MikiwameMoveCount = m_MikiwameMoveCountMax;
    }
}

int32_t BATTLE_CObjectManager::GetStartupPositionXBase(SIDE_ID side, EMemberID memberId)
{
    return StartupPositionX[side][memberId];
}

void BATTLE_CObjectManager::PushFuncCallArg(int arg0, int arg1, int arg2, int arg3)
{
    if (m_FuncCallArgStack < 9)
    {
        m_FuncCallArg[0][m_FuncCallArgStack] = arg0;
        m_FuncCallArg[1][m_FuncCallArgStack] = arg1;
        m_FuncCallArg[2][m_FuncCallArgStack] = arg2;
        m_FuncCallArg[3][m_FuncCallArgStack] = arg3;
        m_FuncCallArgStack++;
    }
}

void BATTLE_CObjectManager::PopFuncCallArg()
{
    if (m_FuncCallArgStack > 0)
    {
        m_FuncCallArgStack--;
        m_FuncCallArg[0][m_FuncCallArgStack] = 0;
        m_FuncCallArg[1][m_FuncCallArgStack] = 0;
        m_FuncCallArg[2][m_FuncCallArgStack] = 0;
        m_FuncCallArg[3][m_FuncCallArgStack] = 0;
    }
}

void BATTLE_CObjectManager::ScriptAnalyze()
{
    for (int i = 0; i < 7; i++)
    {
        m_BBSFileAnalyzeData[0][i].BBSAnalyzeExe(REDGameCommon::GetInstance()->GetCharaData().CharaBBSData[i],
                                                 REDGameCommon::GetInstance()->GetCharaData().CharaBBSDataSize[i]);
        m_BBSFileAnalyzeData[1][i].BBSAnalyzeExe(REDGameCommon::GetInstance()->GetCharaData().EffectBBSData[i],
                                                 REDGameCommon::GetInstance()->GetCharaData().EffectBBSDataSize[i]);
    }
}
