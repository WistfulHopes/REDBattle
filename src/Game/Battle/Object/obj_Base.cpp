#include "obj_Base.h"
#include <cstring>
#include <dinput.h>
#include <intrin.h>
#include <iostream>
#include <Game/Scene/scene_Battle.h>

#include "obj_Flag.h"
#include "Char/char_ActCmn.h"
#include "Char/char_Base.h"

const char* nullstr = "\x0";
int32_t RED_SIDE_OFFSET = 50000;

void OBJ_CBaseRelativePtr::SetPtr(OBJ_CBase* ptr)
{
    m_Ptr = ptr;
    ptr->m_WatchedCount++;
}

void OBJ_CBaseRelativePtr::ClearPtr()
{
    if (!m_Ptr) return;
    --GetPtr()->m_WatchedCount;
    m_Ptr = nullptr;
}

OBJ_CBase::OBJ_CBase()
{
    ObjectConstructor_ForObject();
}

int OBJ_CBase::ObjectInitializeOnActivate(const CInitializeObjectExArg* arg)
{
    return 0;
}

int OBJ_CBase::OnDelete()
{
    if (m_pMultiBufferLarge)
    {
        const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
            GetBattleObjectManager();
        objManager->m_MultiBufferLarge.Release(m_pMultiBufferLarge);
        *((uint64_t*)m_pMultiBufferLarge + 2) = (uint64_t)m_pMultiBufferLarge;
        *((uint64_t*)m_pMultiBufferLarge + 1) = (uint64_t)nullptr;
        m_pMultiBufferLarge = nullptr;
    }
    if (m_pMultiBufferSmall)
    {
        const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
            GetBattleObjectManager();
        objManager->m_MultiBufferSmall.Release(m_pMultiBufferSmall);
        *((uint64_t*)m_pMultiBufferSmall + 2) = (uint64_t)m_pMultiBufferSmall;
        *((uint64_t*)m_pMultiBufferSmall + 1) = (uint64_t)nullptr;
        m_pMultiBufferSmall = nullptr;
    }
    ReleaseResource();
    return 0;
}

int OBJ_CBase::ReleaseResource()
{
    if (m_IsPlayerObj)
    {
    }

    m_pParentObj.ClearPtr();
    m_pParentPly.ClearPtr();
    m_pTargetObj.ClearPtr();
    m_pPrevChild.ClearPtr();
    m_pTrialObj.ClearPtr();
    for (auto& child : m_pChildStack)
    {
        child.ClearPtr();
    }

    for (auto& slave : m_pAttackSlave)
    {
        slave.ClearPtr();
    }
    m_pAttackSlaveNewest.ClearPtr();
    m_pLockLinkObj.ClearPtr();
    m_pControlObject.ClearPtr();
    // TODO add more relative objects

    m_pLinkObject_PushCollision.ClearPtr();
    m_pLinkObject_Angle.ClearPtr();
    m_pLinkObject_Position.ClearPtr();
    m_pLinkObject_Direction.ClearPtr();
    m_pLinkObject_DamageToEliminate.ClearPtr();
    m_pLinkObject_ChangeToEliminate.ClearPtr();
    m_pLinkObject_Stop.ClearPtr();
    m_pLinkObject_PositionCenter.ClearPtr();
    m_pLinkObject_Scale.ClearPtr();
    m_pLinkObject_Color.ClearPtr();
    m_pLinkObject_MaterialSet.ClearPtr();
    m_pLinkObject_CmnMaterialParam.ClearPtr();
    m_pLinkObject_Z.ClearPtr();
    m_pLinkObject_Collision.ClearPtr();

    return 0;
}

void OBJ_CBase::ObjectConstructor_ForObject()
{
}

void OBJ_CBase::ObjUnactivate()
{
    if (m_ActiveState == ACTV_NOT_ACTIVE || (m_ActiveState != ACTV_ACTIVE && m_ActiveState != ACTV_REQ_ACTIVE &&
        m_ActiveState == ACTV_REQ_NO_ACTIVE))
        return;

    m_ObjSignal |= 0x200;
    m_ActiveState = ACTV_REQ_NO_ACTIVE;
    ActionChangeSignal();
}

bool OBJ_CBase::ObjIsUsing()
{
    if (m_ActiveState == ACTV_NOT_ACTIVE || (m_ActiveState != ACTV_ACTIVE && m_ActiveState != ACTV_REQ_ACTIVE &&
        m_ActiveState == ACTV_REQ_NO_ACTIVE))
        return false;

    return true;
}

void OBJ_CBase::ActionChangeSignal()
{
    if (!m_IsPlayerObj)
    {
        auto itr = 0;
        const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
            GetBattleObjectManager();

        while (true)
        {
            auto nextSortedActiveObj = objManager->GetNextSortedActiveObjectWithCreateChokugo(&itr);

            if (nextSortedActiveObj == nullptr) break;

            if (m_ActiveState != ACTV_NOT_ACTIVE)
            {
                if (m_ActiveState != ACTV_ACTIVE && m_ActiveState != ACTV_REQ_ACTIVE && m_ActiveState ==
                    ACTV_REQ_NO_ACTIVE)
                    continue;

                if (nextSortedActiveObj->m_SideID == SIDE_ID_NUM && nextSortedActiveObj->m_MemberID == m_MemberID)
                {
                    nextSortedActiveObj->DoInterrupt(ON_PLAYER_ACTION_CHANGE);

                    if (nextSortedActiveObj->m_KowareCur == 0 && (m_CollisionFlag2 & OBJ_CLSN_2_KOWARE_ACT) != 0)
                    {
                        RequestKoware(CO_SELF);
                    }
                }
            }
        }
    }

    auto itr = 0;
    const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
        GetBattleObjectManager();

    while (true)
    {
        auto nextSortedActiveObj = objManager->GetNextSortedActiveObjectWithCreateChokugo(&itr);

        if (nextSortedActiveObj == nullptr) break;

        if (m_ActiveState != ACTV_NOT_ACTIVE)
        {
            if (m_ActiveState != ACTV_ACTIVE && m_ActiveState != ACTV_REQ_ACTIVE && m_ActiveState ==
                ACTV_REQ_NO_ACTIVE)
                continue;

            if (nextSortedActiveObj->m_SideID == SIDE_ID_NUM && nextSortedActiveObj->m_MemberID == m_MemberID &&
                nextSortedActiveObj->m_pLinkObject_ChangeToEliminate == this)
            {
                nextSortedActiveObj->m_ObjSignal |= 0x400;
            }
        }
    }
}

OBJ_CBase* OBJ_CBase::GetControlObject(CO_TYPE type)
{
    switch (type)
    {
    case CO_PREV:
        return m_pPrevChild;
    case CO_PARENT:
        return m_pParentObj;
    case CO_PLAYER:
        return m_pParentPly;
    case CO_STACK0:
        return m_pChildStack[0];
    case CO_STACK1:
        return m_pChildStack[1];
    case CO_STACK2:
        return m_pChildStack[2];
    case CO_STACK3:
        return m_pChildStack[3];
    case CO_STACK4:
        return m_pChildStack[4];
    case CO_STACK5:
        return m_pChildStack[5];
    case CO_STACK6:
        return m_pChildStack[6];
    case CO_STACK7:
        return m_pChildStack[7];
    case CO_STACK_FOR_CMN_ACT:
        return m_pChildStack[8];
    case CO_WINNER:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetWinnerObj();
        }
    case CO_LOSER:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetWinnerObj()->m_pTargetObj;
        }
    case CO_LOCKED:
        return m_pLockLinkObj;
    case CO_ENEMY:
        return m_pTargetObj;
    case CO_SELF:
        return this;
    case CO_ATTACK_MASTER:
        return m_pAttackMaster;
    case CO_ATTACK_SLAVE:
        return m_pAttackSlaveNewest;
    case CO_TRIAL:
        return m_pTrialObj;
    case CO_PLAYER1:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetMainPlayer(SIDE_1P);
        }
    case CO_PLAYER2:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetMainPlayer(SIDE_2P);
        }
    case CO_SELF_MAIN_PLAYER:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetMainPlayer(m_SideID);
        }
    case CO_SELF_SUB_MEMBER1:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetSubMember(m_SideID, SubMemberID_01);
        }
    case CO_SELF_SUB_MEMBER2:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetSubMember(m_SideID, SubMemberID_02);
        }
    case CO_ENEMY_MAIN_PLAYER:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetMainPlayer(static_cast<SIDE_ID>(m_SideID == 0 ? 1 : 0));
        }
    case CO_ENEMY_SUB_MEMBER1:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetSubMember(static_cast<SIDE_ID>(m_SideID == 0 ? 1 : 0), SubMemberID_01);
        }
    case CO_ENEMY_SUB_MEMBER2:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetSubMember(static_cast<SIDE_ID>(m_SideID == 0 ? 1 : 0), SubMemberID_02);
        }
    case CO_PREV_MAIN_PLAYER:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetTeamManager(m_SideID)->GetPrevMainPlayer();
        }
    case CO_PREV_ENEMY_MAIN_PLAYER:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetTeamManager(static_cast<SIDE_ID>(m_SideID == 0 ? 1 : 0))->GetPrevMainPlayer();
        }
    case CO_MAIN_PLAYER1:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetMainPlayer(SIDE_1P);
        }
    case CO_MAIN_PLAYER2:
        {
            const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
                GetBattleObjectManager();
            return objManager->GetMainPlayer(SIDE_2P);
        }
    default:
        return nullptr;
    }
}

void OBJ_CBase::GetPushWorldRect(int* L, int* T, int* R, int* B)
{
    auto posX = GetPosX();
    auto posY = GetPosY();

    auto dirObj = m_pLinkObject_Direction;
    uint32_t direction;

    if (!dirObj) direction = m_Direction;
    else direction = GetObjDir();

    auto pushFront = direction ? GetPushColW() / 2 : GetPushColW() / 2 + m_PushColWidthFront;
    auto pushBack = direction ? GetPushColW() / 2 + m_PushColWidthFront : GetPushColW() / 2;

    *T = GetPushColH() + posY;
    *B = posY - GetPushColHLow();

    *L = posX - pushBack;
    *R = posX + pushFront;

    if (L && R)
    {
        if (m_ClsnAnalyzer.m_CollisionNum[5])
        {
            float tmpL;
            float tmpR;

            auto worldRect = m_ClsnAnalyzer.m_CollisionAddr[5]->m_WorldRect;

            if (direction != 0)
            {
                tmpL = worldRect.m_X * -1000.f;
                tmpR = (worldRect.m_W + worldRect.m_X) * 1000.f;
            }
            else
            {
                tmpL = (worldRect.m_W + worldRect.m_X) * 1000.f;
                tmpR = worldRect.m_X * -1000.f;
            }

            *L = posX - (int)tmpL;
            *R = posX + (int)tmpR;
        }
    }
    
    if ((m_CollisionFlag & OBJ_CLSN_LOCKING) != 0 && (m_CollisionFlag3 & OBJ_CLSN_3_NOFAT_PUSHCOL_LOCKING) == 0)
    {
        if (L && R)
        {
            int tmpL, tmpT, tmpR, tmpB = 0;
            m_pLockLinkObj.GetPtr()->GetPushWorldRect(&tmpL, &tmpT, &tmpR, &tmpB);

            if (*T < tmpT) *T = tmpT;
            if (*B > tmpB) *B = tmpB;
            if (*L > tmpL) *L = tmpL;
            if (*R < tmpR) *R = tmpR;
        }
        else
        {
            int tmpT, tmpB = 0;
            m_pLockLinkObj.GetPtr()->GetPushWorldRect(nullptr, &tmpT, nullptr, &tmpB);

            if (*T < tmpT) *T = tmpT;
            if (*B > tmpB) *B = tmpB;
        }
    }
    
    if (m_pLinkObject_PushCollision)
    {
        if (L && R)
        {
            int tmpL, tmpT, tmpR, tmpB = 0;
            m_pLinkObject_PushCollision.GetPtr()->GetPushWorldRect(&tmpL, &tmpT, &tmpR, &tmpB);

            if (*T < tmpT) *T = tmpT;
            if (*B > tmpB) *B = tmpB;
            if (*L > tmpL) *L = tmpL;
            if (*R < tmpR) *R = tmpR;
        }
        else
        {
            int tmpT, tmpB = 0;
            m_pLinkObject_PushCollision.GetPtr()->GetPushWorldRect(nullptr, &tmpT, nullptr, &tmpB);

            if (*T < tmpT) *T = tmpT;
            if (*B > tmpB) *B = tmpB;
        }
    }
}

void OBJ_CBase::GetPushWorldRectForWorldClip(int* L, int* R)
{
    auto posX = GetPosX();
    *L = posX - RED_SIDE_OFFSET - 35000;
    *R = RED_SIDE_OFFSET + posX + 35000;

    if (m_CollisionFlag & OBJ_CLSN_LOCKING)
    {
        int tmpL, tmpR = 0;
        m_pLockLinkObj.GetPtr()->GetPushWorldRectForWorldClip(&tmpL, &tmpR);

        if (*L > tmpL) *L = tmpL;
        if (*R < tmpR) *R = tmpR;
    }
    
    if (m_pLinkObject_PushCollision)
    {
        int tmpL, tmpR = 0;
        m_pLinkObject_PushCollision.GetPtr()->GetPushWorldRectForWorldClip(&tmpL, &tmpR);

        if (*L > tmpL) *L = tmpL;
        if (*R < tmpR) *R = tmpR;
    }
}

void OBJ_CBase::GetPushScreenRect(int& L, int& T, int& R, int& B)
{
    GetPushWorldRect(nullptr, &T, nullptr, &B);
    GetPushWorldRectForWorldClip(&L, &R);
    
    auto dirObj = m_pLinkObject_Angle.GetPtr()->m_pLinkObject_Direction;
    uint32_t direction;

    if (!dirObj) direction = m_Direction;
    else direction = GetObjDir();

    if (direction != 0)
    {
        L -= m_PushScreenOffsetFront;
        R += m_PushScreenOffsetBack;
    }
    else
    {
        R += m_PushScreenOffsetFront;
        L -= m_PushScreenOffsetBack;
    }

    T += m_PushScreenOffsetTop;
    B += m_PushScreenOffsetBottom;
}

bool OBJ_CBase::ActionRequestForce(const CXXBYTE<32>& actionName)
{
    return ActionRequestEx(actionName, 9, nullptr, CXXBYTE<32>(nullstr), 0);
}

bool OBJ_CBase::ActionRequestEx(const CXXBYTE<32>& actionName, unsigned int flag, OBJ_CBase* pEnemy, CXXBYTE<32> label,
                                unsigned int reqFlag)
{
    if (!(flag & 1) && (flag & 2 && !strncmp(m_CurActionName.GetStr(), actionName.GetStr(), 32)
        || flag & 8 && *m_ActionRequestInfo.m_RequestName.GetStr()))
        return false;

    m_ActionRequestInfo.CActionRequestInfoInit();
    m_ActionRequestInfo.m_RequestName = actionName;
    m_ActionRequestInfo.m_RequestGotoLabel = label;
    m_ActionRequestInfo.m_RequestFlag = reqFlag;
    if (flag) m_ActionRequestInfo.m_RequestFlag = reqFlag | 0x20000;

    return true;
}

STOP_TYPE OBJ_CBase::CheckForceStop()
{
    return CheckForceStopSub();
}

STOP_TYPE OBJ_CBase::CheckForceStopSub()
{
    OBJ_CBase* obj = this;
    OBJ_CBase* prevObj;
    do
    {
        do
        {
            prevObj = obj;
            obj = obj->m_pLockLinkObj;
        }
        while (obj && prevObj->m_CollisionFlag & OBJ_CLSN_LOCKED);
        obj = prevObj->m_pLinkObject_Stop;
    }
    while (obj && obj->m_ActiveState == ACTV_ACTIVE);
    if (prevObj->m_ObjFlag & OBJ_FLG_STOP_BY_WORLD) return STOP_TYPE_ANTEN;
    if (prevObj->m_ObjFlag2 & OBJ_FLG_2_STOP_BY_SLOW) return STOP_TYPE_SLOW;
    return (STOP_TYPE)(prevObj->m_HitStopTime || prevObj->m_HitStopTimeBySousai);
}

bool OBJ_CBase::ControlPhase_FrameStep()
{
    bool scriptReturn;
    do
    {
        scriptReturn = SubControlPhase_ScriptFrameStep(m_DebugActionChangeCount);
        m_DebugActionChangeCount++;
    }
    while (m_DebugActionChangeCount != 10 && IsActionRequested() && scriptReturn);

    return false;
}

bool OBJ_CBase::ControlPhase_PreFrameStep()
{
    if (m_IsPlayerObj)
    {
    }
    return false;
}

bool OBJ_CBase::ControlPhase_AfterFrameStep()
{
    return false;
}

bool OBJ_CBase::SubControlPhase_ScriptFrameStep(int count)
{
    if (IsActionRequested() && m_ActionRequestInfo.m_RequestFlag & 0x10 && m_HitStopTime)
    {
        m_HitStopTimeReq = 0;
        m_HitStopTimeReqLevel = 0;
        m_HitStopTime = 0;
        m_bSlowHitstop = false;
        m_HitStopTimeMax = 0;
    }

    auto forceStop = CheckForceStopSub();
    if (!forceStop || forceStop == STOP_TYPE_ANTEN && IsActionRequested() && m_CollisionFlag & (OBJ_CLSN_GUARD_IMPACT |
        OBJ_CLSN_DAMAGE_IMPACT))
    {
        ScriptFrameStep();
        if (m_IsPlayerObj)
        {
            auto playerObj = (OBJ_CCharBase*)this;
            // TODO check dizzy
            playerObj->DelPlayerFlag2(PLFLG2_KIZETSU_ANIME_X_2);
        }
        m_ActionTime++;

        DoInterrupt(ON_IDLING);
    }

    // TODO finish
    return false;
}

bool OBJ_CBase::IsDead()
{
    auto hpPercent = 10000 * m_HitPoint / m_HitPointMax;
    if (hpPercent <= 0)
    {
        if (m_HitPoint > 0) hpPercent = 1;
    }
    return hpPercent <= 0;
}

OBJ_CCharBase* OBJ_CBase::GetMainPlayerBase(SIDE_ID side)
{
    const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
        GetBattleObjectManager();
    return objManager->GetTeamManager(side)->GetMainPlayer();
}

int OBJ_CBase::GetPosX()
{
    auto angleY = 0;
    auto angleY2 = 0;
    if (m_pLinkObject_Angle != nullptr)
    {
        auto linkObj = m_pLinkObject_Angle.GetPtr()->m_pLinkObject_Angle;
        if (!linkObj)
        {
            angleY2 = angleY = m_pLinkObject_Angle.GetPtr()->m_AngleYDeg_x1000;
        }
        else
        {
            angleY2 = m_pLinkObject_Angle.GetPtr()->m_AngleYDeg_x1000;
            angleY = linkObj.GetPtr()->GetAngleY() + angleY2;
        }
    }

    int pos_x;

    if (m_pLinkObject_Angle == nullptr || angleY == 0)
        pos_x = m_PosX;
    else
    {
        if (m_pLinkObject_Angle.GetPtr()->m_pLinkObject_Angle)
        {
            angleY2 += m_pLinkObject_Angle.GetPtr()->m_pLinkObject_Angle.GetPtr()->GetAngleY();
        }

        auto dirObj = m_pLinkObject_Angle.GetPtr()->m_pLinkObject_Direction;
        uint32_t direction;

        if (!dirObj) direction = m_Direction;
        else direction = GetObjDir();

        if (direction > 0) angleY2 = -angleY2;

        auto deg = angleY2 / 1000;
        auto degWrap = deg % 360000;

        if (deg % 360000 < 0) degWrap += 360000;

        auto rad = (float)deg * M_PI / 180.0f;

        pos_x = (int32_t)(cosf(rad) * (float)m_PosX - sinf(rad) * (float)m_PosY);
    }

    auto posObj = m_pLinkObject_Position;

    if (posObj == nullptr)
    {
        posObj = m_pLinkObject_PositionCenter;

        if (posObj == nullptr)
        {
            if ((m_CollisionFlag & OBJ_CLSN_LOCK_LINK_POSITION) != OBJ_CLSN_LOCK_LINK_POSITION) return pos_x;

            posObj = m_pLockLinkObj;
        }
    }

    return posObj.GetPtr()->GetPosX() + pos_x;
}

int OBJ_CBase::GetPosY()
{
    if (m_pLinkObject_Position) return m_PosY + m_pLinkObject_Position.GetPtr()->GetPosY();
    if (m_pLinkObject_PositionCenter) return m_PosY + m_pLinkObject_Position.GetPtr()->GetPosYCenter();
    if (m_CollisionFlag & OBJ_CLSN_LOCK_LINK_POSITION && m_CollisionFlag & OBJ_CLSN_LOCKED)
        return m_PosY + m_pLockLinkObj.GetPtr()->GetPosY();
    return m_PosY;
}

int OBJ_CBase::GetPosYCenter()
{
    if (!m_IsPlayerObj) return GetPosY();

    auto player = (OBJ_CCharBase*)this;
    if (player->CheckPlayerFlag(PLFLG_CROUCH)) return m_PosY + 90000;
    if (player->CheckPlayerFlag(PLFLG_LOW_BALANCE)) return m_PosY + 40000;
    return m_PosX + 200000;
}

int OBJ_CBase::GetAngleY()
{
    if (!m_pLinkObject_Angle) return m_AngleYDeg_x1000;

    return m_pLinkObject_Angle.GetPtr()->GetAngleY() + m_AngleYDeg_x1000;
}

int OBJ_CBase::GetPushColW()
{
    if (m_PushColWidth >= 0) return m_PushColWidth;
    if (m_IsPlayerObj == false) return 120;

    auto player = (OBJ_CCharBase*)this;

    if ((m_ActionFlag & OBJ_ACT_AIR) == 0 && GetPosY() <= 0)
    {
        if (player->CheckPlayerFlag(PLFLG_CROUCH) == 0 && player->CheckPlayerFlag(PLFLG_LOW_BALANCE) == 0)
            return player->ply_PushColWidthStand;

        return player->ply_PushColWidthCrouch;
    }

    return player->ply_PushColWidthAir;
}

int OBJ_CBase::GetPushColH()
{
    if (m_PushColHeight >= 0) return m_PushColHeight;
    if (m_IsPlayerObj == false) return 100;

    auto player = (OBJ_CCharBase*)this;

    if ((m_ActionFlag & OBJ_ACT_AIR) == 0 && GetPosY() <= 0)
    {
        if (player->CheckPlayerFlag(PLFLG_CROUCH) == 0 && player->CheckPlayerFlag(PLFLG_LOW_BALANCE) == 0)
            return player->ply_PushColHeightStand;

        return player->ply_PushColHeightCrouch;
    }

    return player->ply_PushColHeightAir;
}

int OBJ_CBase::GetPushColHLow()
{
    if (m_PushColHeightLow != 0xFFFFFFF) return m_PushColHeightLow;
    if (m_IsPlayerObj)
    {
        auto player = (OBJ_CCharBase*)this;

        if (m_ActionFlag & OBJ_ACT_AIR || GetPosY() > 0)
        {
            return player->ply_PushColHeightLowAir;
        }
    }

    return 0;
}

uint32_t OBJ_CBase::GetObjDir()
{
    const OBJ_CBase* finalObj = this;
    for (auto i = m_pLinkObject_Direction.GetPtr(); i; i = i->m_pLinkObject_Direction.GetPtr())
        finalObj = i;

    return finalObj->m_Direction;
}

bool OBJ_CBase::IsActionRequested()
{
    return m_ActionRequestInfo.m_RequestName.GetStr() != nullptr || m_ActionRequestInfo.m_SomeSkillIsRequested ||
        m_ActionRequestInfo.m_RequestFlag & 0x400000;
}

void OBJ_CBase::ScriptFrameStep()
{
    if (*(uint32_t*)m_CurAddr == ID_ActionEnd || m_ScriptFlag & 0x20 || *(uint32_t*)m_CurAddr == ID_ReqActionEnd)
    {
        if (m_CellTime + 1 >= m_CellTimeMax && !m_IsCellTimeStop && m_CellTimeMax != 0x7FFFFFFF)
        {
            DoInterrupt(ON_ACTION_END);
            OnActionEnd();
        }
    }
    if (!(m_ScriptFlag & 1) && !m_IsCellTimeStop)
    {
        if (m_CellTimeStopOnece) m_CellTimeStopOnece = false;
        else
        {
            if (m_CellTime != 0x7FFFFFFE)
            {
                m_CellTime++;
                if (m_CellTime < 0) m_CellTime = 0;
            }
            else m_CellTime = 0x7FFFFFFE;
        }
    }

    // TODO a bunch of stuff

    if (m_ActionRequestInfo.m_RequestName.GetStr()[0] != '\0')
    {
        m_CurAddr = GetActionAddr(m_ActionRequestInfo.m_RequestName, nullptr);
        ExecuteCellBeginToCellEnd(m_CurAddr);

        if (!strncmp(m_ActionRequestInfoReg.m_RequestGotoLabel.GetStr(), nullstr, 0x20)) return;

        m_CurAddr = m_pBBSFile->GetGotoAddrBBSF(m_CurActionTopAddr, m_ActionRequestInfoReg.m_RequestGotoLabel);
        m_GotoTimes = 0;
        m_CurAddr = ExecuteCellBeginToCellEnd(m_CurAddr);
        return;
    }

    if (*(uint32_t*)m_CurAddr != ID_ActionEnd)
    {
        if (m_CellTime >= m_CellTimeMax && !m_IsCellTimeStop && m_CellTimeMax != 0x7FFFFFFF)
        {
            m_CurAddr = ExecuteCellBeginToCellEnd(m_CurAddr);
        }
    }
}

void OBJ_CBase::BBST_OnActionBegin(const CXXBYTE<32>& actName)
{
    const auto battleScene = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene());

    m_ActionChangeID = battleScene->GetBattleObjectManager()->GetActionChangeCount();
    battleScene->GetBattleObjectManager()->SetActionChangeCount(m_ActionChangeID + 1);
    this->m_ScriptFlag &= 0xFFFFFFDE;

    if (m_IsPlayerObj)
    {
        m_pLinkObject_PushCollision.ClearPtr();
        m_pLinkObject_Angle.ClearPtr();
        m_pLinkObject_Position.ClearPtr();
        m_pLinkObject_Direction.ClearPtr();
        m_pLinkObject_DamageToEliminate.ClearPtr();
        m_pLinkObject_ChangeToEliminate.ClearPtr();
        m_pLinkObject_Stop.ClearPtr();
        m_pLinkObject_PositionCenter.ClearPtr();
        m_pLinkObject_Scale.ClearPtr();
        m_pLinkObject_Z.ClearPtr();
        m_pLinkObject_Collision.ClearPtr();
    }
    m_pControlObject.ClearPtr();

    m_IsCellTimeStop = false;
    m_CellTimeStopOnece = false;
    m_CellBeginCount = 0;
    DoInterrupt(ON_FINALIZE);
    m_ValidInterruptFlag[0][0].Del(2);
    m_ValidInterruptFlag[1][0].Del(2);
    m_ValidInterruptFlag[2][0].Del(2);
    m_ValidInterruptFlag[3][0].Del(2);
    m_ValidInterruptFlag[4][0].Del(2);
    FuncCall(FN_OnFinalize);

    m_CurActionTopAddr = GetActionAddr(actName, nullptr);
    m_CellTime = 0;
    m_CellTimeMax = 0;
    m_CellNoStopCellNum = 0;

    m_ActionRequestInfo.m_RequestName = "\00";
    m_ActionRequestInfo.m_RequestFlag = 0;
    m_ActionRequestInfo.m_RequestGotoLabel = "\00";
    m_ActionRequestInfo.m_RequestSkillID = -1;
    m_ActionRequestInfo.m_SomeSkillIsRequested = false;
    m_ActionRequestInfo.m_SomeSkillIsRequestReserved = false;
    m_ActionRequestInfo.m_RequestGCSkill = -1;

    m_PreActionName = m_CurActionName;
    m_CurActionName = actName;

    for (auto& interruptFlag0 : m_ValidInterruptFlag)
    {
        for (auto& interruptFlag1 : interruptFlag0)
        {
            interruptFlag1 = 0;
        }
    }

    auto addr = &m_CurActionTopAddr[commandSizeTable[*(uint32_t*)this->m_CurActionTopAddr]];
    auto cmd = *(uint32_t*)addr;
    if (cmd != ID_ActionEnd)
    {
        while (cmd != ID_InterruptBegin || *(uint32_t*)(addr + 4))
        {
            auto nestLevel = 0;
            do
            {
                cmd = *(uint32_t*)addr;
                auto beginVal = BeginEndList;
                auto beginFound = true;

                while (*(uint32_t*)beginVal != cmd)
                {
                    if ((int64_t)++beginVal >= (int64_t)&BeginEndList + 0x88)
                    {
                        beginFound = false;
                        break;
                    }
                }

                if (beginFound) nestLevel++;

                auto endVal = &BeginEndList[0][1];
                auto endFound = true;
                while (*(uint32_t*)endVal != cmd)
                {
                    if ((int64_t)++endVal >= (int64_t)&BeginEndList[0][1] + 0x88)
                    {
                        endFound = false;
                        break;
                    }
                }

                if (endFound) nestLevel--;

                addr += commandSizeTable[cmd];
            }
            while (nestLevel);
        }

        if (cmd != ID_ActionEnd) FuncCallBySwitchCaseTable(addr);
    }

    if (m_IsPlayerObj)
    {
        // TODO initialize player action by category
    }

    DoInterrupt(ON_INITIALIZE);
}

int OBJ_CBase::DoInterrupt(ON_XXXX_INTRPT)
{
    return 0;
}

void OBJ_CBase::OnActionBegin(const CXXBYTE<32>& actName)
{
    const char* plyActName = nullptr;
    if (m_IsPlayerObj)
    {
        plyActName = actName.GetStr();
    }

    m_ActionFlag2 &= ~OBJ_ACT_AFTER_IMAGE;
    m_HideFlag &= 0xF0FF00FF;
    m_ObjFlag &= ~OBJ_FLG_SHADOW_OFF;
    m_ObjFlag3 &= 0x4FFFFE84u;
    m_ObjFlag4 &= ~OBJ_FLG_4_IGNORE_ZLINE;
    m_ObjFlag5 &= 0xFFFFFFFC;
    m_CollisionFlag2 &= 0xC0BFFFFF;
    m_ObjFlag2 &= 0x4B7FBFFF;
    m_NaguruSignal = ON_SIGNAL_NULL;
    m_KowareDone = false;
    m_KowareCur = 0;
    m_KowareMax = 1;
    m_KowareOnEnemyDamage = 0;
    m_KowareOnEnemyGuard = 0;
    m_KowareOnSousai = 0;
    m_KowareOnDamageCollision = 0;
    m_KowareTenmetsuTime = 0;
    m_KowareOnDamageOnly = 0;
    m_KowareDispGauge = false;
    m_KowareDispOffsetX = 0;
    m_KowareDispOffsetY = 0;
    m_KowareDispWidth = 0;

    // TODO lots more obj initialization

    FuncCall(FN_OnActionBeginPre);
    BBST_OnActionBegin(actName);

    FuncCall(FN_OnActionBegin);
}

void OBJ_CBase::OnActionEnd()
{
}

void OBJ_CBase::OnCellBegin(const CXXBYTE<32>& name, int time)
{
    m_ScriptFlag |= 2;
    ++m_CellBeginCount;
    m_CellTime = 0;
    m_CellNoStopCellNum = 0;
    m_CellTimeReserve = time;
    m_CellTimeMax = time;
    OnCellChange(name, true);
    m_CollisionFlag &= ~OBJ_CLSN_NO_ATTACK_CELL;
}

void OBJ_CBase::OnCellChange(const CXXBYTE<32>& name, bool isUsePrimary)
{
    if (!strncmp(name.GetStr(), CN_Null.GetStr(), 0x20))
    {
        m_ClsnAnalyzer.AnalyzeCollisionFile(nullptr);
        m_ClsnAnalyzer.SetCollisionFileName(nullptr);
        m_CellName = name;
    }
    if (!strncmp(name.GetStr(), CN_Keep.GetStr(), 0x20)) return;

    const auto fileId = (int32_t)m_ColPac.SearchFileID(name.GetStr());
    if (fileId != -1)
    {
        const auto offset = m_ColPac.GetPackOffsetAddr(fileId);
        m_ClsnAnalyzer.AnalyzeCollisionFile(offset);
        m_ClsnAnalyzer.SetCollisionFileName(m_ColPac.GetPackFileNum2FileName(fileId));

        m_CellName = name;
    }
}

void OBJ_CBase::ActionBegin(const CXXBYTE<32>& actName)
{
    OnActionBegin(actName);
}

void OBJ_CBase::CellBegin(const CXXBYTE<32>& name, int time)
{
    if (!strncmp(name.GetStr(), AN_CmnActLockWait.GetStr(), 0x20)) m_ScriptFlag |= 1;
    else OnCellBegin(name, time);
}

void OBJ_CBase::Goto(CXXBYTE<32> label)
{
    m_ScriptFlag |= 8;
    m_ScriptGotoAddr = m_pBBSFile->GetGotoAddrBBSF(m_CurActionTopAddr, label);
}

uint8_t* OBJ_CBase::ExecuteCellBeginToCellEnd(uint8_t* addr)
{
    m_ScriptFlag &= 0xFFFFFFE1;
    bool jumpDone = false;
    uint8_t* returnAddr;
    do
    {
        auto cmd = *(uint32_t*)addr;
        returnAddr = addr;
        if (cmd == ID_ActionEnd || cmd == ID_ReqActionEnd)
        {
            m_ScriptFlag |= 0x10;
        }
        else
        {
            if (cmd < ID_IfBegin && m_ScriptFlag & 2)
            {
                m_ScriptFlag |= 4;
                addr = returnAddr;
                continue;
            }

            LONG64 bittestVal = 0xC00000020100000FuLL;
            bool bIsNestCommand = cmd == ID_IfBegin || (cmd - 6 <= ID_CheckTeamMemberName && BitTest64(
                &bittestVal,
                cmd - 6)) || cmd - ID_IfBeginCoType <= 2 || cmd == ID_IfBeginGameMode || cmd == ID_IfBeginCharaID;

            if (bIsNestCommand)
            {
                if (cmd != ID_ElseBegin)
                {
                    FuncCallBySwitchCaseTable(addr);
                    auto newAddr = GetSkipBeginEndAddr(addr);
                    if (m_IfReturnVal)
                    {
                        returnAddr = &addr[commandSizeTable[*(uint32_t*)addr]];
                        if (returnAddr != newAddr)
                        {
                            do
                            {
                                returnAddr = ExecuteNestCommand(returnAddr, 1, &jumpDone, false, nullptr);
                            }
                            while (!(m_ScriptFlag & 8) && returnAddr != newAddr);
                        }
                        else
                        {
                            returnAddr = newAddr;
                            if (*(uint32_t*)returnAddr == ID_ElseBegin)
                            {
                                returnAddr += 4;
                                newAddr = GetSkipBeginEndAddr(returnAddr);
                                do
                                {
                                    returnAddr = ExecuteNestCommand(returnAddr, 1, &jumpDone, false, nullptr);
                                }
                                while (!(m_ScriptFlag & 8) && !(m_ScriptFlag & 10) && returnAddr != newAddr);
                            }
                        }
                        addr = returnAddr;
                        continue;
                    }
                }

                returnAddr = GetSkipBeginEndAddr(addr);
                addr = returnAddr;
                continue;
            }

            FuncCallBySwitchCaseTable(addr);
            if (cmd == ID_InterruptBegin)
            {
                returnAddr = GetSkipBeginEndAddr(addr);
                addr = returnAddr;
                continue;
            }

            returnAddr = m_GotoForLoopAddr;
            if (returnAddr)
                m_GotoForLoopAddr = nullptr;
            else
                returnAddr = &addr[commandSizeTable[*(uint32_t*)addr]];

            if (m_ScriptGotoAddr)
            {
                returnAddr = m_ScriptGotoAddr;
                m_ScriptGotoAddr = nullptr;
            }
        }
        addr = returnAddr;
    }
    while (!(m_ScriptFlag & 0x14));

    if (*(uint32_t*)returnAddr == ID_CellEnd)
        return returnAddr + 4;

    return returnAddr;
}

uint8_t* OBJ_CBase::ExecuteNestCommand(uint8_t* addr, int recCount, bool* jumpDone, bool bJumpCheckOnly,
                                       bool* pForceStop)
{
    auto command = *(uint32_t*)addr;
    if (command == ID_ActionEnd || command == ID_ReqActionEnd)
    {
        m_ScriptFlag |= 0x10;
        if (pForceStop) *pForceStop = true;
    }
    else
    {
        if (command >= 3)
        {
            if (m_ScriptFlag & 2)
            {
                m_ScriptFlag |= 4;
                return addr;
            }
        }
        uint64_t bits = 0xC00000020100000F;
        bool isIfBegin = command == ID_IfBegin || command - 6 <= ID_CheckTeamMemberName &&
            _bittest64((const __int64*)&bits, (unsigned __int16)(command - 6))
            || command - ID_IfBeginCoType <= 2
            || command == ID_IfBeginGameMode
            || command == ID_IfBeginCharaID;

        if (isIfBegin)
        {
            if (command != ID_ElseBegin)
            {
                FuncCallBySwitchCaseTable(addr);
                auto skipBeginEndAddr = GetSkipBeginEndAddr(addr);
                if (m_IfReturnVal)
                {
                    addr += commandSizeTable[*(uint32_t*)addr];
                    if (m_GotoForLoopAddr != skipBeginEndAddr)
                    {
                        do
                        {
                            addr = ExecuteNestCommand(addr, recCount + 1, jumpDone, bJumpCheckOnly, nullptr);
                        }
                        while ((m_ScriptFlag & 8) == 0 && addr != skipBeginEndAddr);
                    }
                }
                else
                {
                    addr = skipBeginEndAddr;
                    if (*(uint32_t*)addr == ID_ElseBegin)
                    {
                        addr += 4;
                        skipBeginEndAddr = GetSkipBeginEndAddr(skipBeginEndAddr);
                        if (addr != skipBeginEndAddr)
                        {
                            do
                            {
                                addr = ExecuteNestCommand(addr, recCount + 1, jumpDone, bJumpCheckOnly, nullptr);
                            }
                            while ((m_ScriptFlag & 8) == 0 && (m_ScriptFlag & 0x10) == 0 && addr != skipBeginEndAddr);
                        }
                    }
                }
                return addr;
            }
            return GetSkipBeginEndAddr(addr);
        }
        FuncCallBySwitchCaseTable(addr);
        if (command == ID_InterruptBegin)
        {
            return GetSkipBeginEndAddr(addr);
        }
        if (m_GotoForLoopAddr)
        {
            m_GotoForLoopAddr = nullptr;
        }
        else
        {
            addr += commandSizeTable[*(uint32_t*)addr];
        }
        if (m_ScriptGotoAddr)
        {
            addr = m_ScriptGotoAddr;
            m_ScriptGotoAddr = nullptr;
        }
    }
    return addr;
}

int OBJ_CBase::ExecuteFunctionBlock(const CXXBYTE<32>& funcName)
{
    const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
        GetBattleObjectManager();

    uint8_t* funcAddrBase = nullptr;

    if (!strncmp(funcName.GetStr(), "cmn", 3))
    {
        auto bbsFile = objManager->GetCommonScriptData(ScriptData_Effect);
        funcAddrBase = bbsFile->GetFuncAddrBase(funcName, bbsFile->m_FuncAddrTable.get());
    }
    else if (m_IsPlayerObj)
    {
        funcAddrBase = m_pBBSFile->GetFuncAddrBase(funcName, m_pBBSFile->m_FuncAddrTable.get());
        if (!funcAddrBase)
        {
            auto bbsFile = objManager->GetScriptData(m_SideID, m_MemberID, ScriptData_Effect);
            funcAddrBase = bbsFile->GetFuncAddrBase(funcName, bbsFile->m_FuncAddrTable.get());
        }
    }

    if (!funcAddrBase) return 0;

    uint8_t* preFuncAddrBase = nullptr;

    if (!strncmp(funcName.GetStr(), "cmn", 3))
    {
        auto bbsFile = objManager->GetCommonScriptData(ScriptData_Effect);
        preFuncAddrBase = bbsFile->GetFuncAddrBase(funcName, bbsFile->m_PreFuncAddrTable.get());
    }
    else if (m_IsPlayerObj)
    {
        preFuncAddrBase = m_pBBSFile->GetFuncAddrBase(funcName, m_pBBSFile->m_PreFuncAddrTable.get());
        if (!funcAddrBase)
        {
            auto bbsFile = objManager->GetScriptData(m_SideID, m_MemberID, ScriptData_Effect);
            preFuncAddrBase = bbsFile->GetFuncAddrBase(funcName, bbsFile->m_PreFuncAddrTable.get());
        }
    }

    uint8_t* postFuncAddrBase = nullptr;

    if (!strncmp(funcName.GetStr(), "cmn", 3))
    {
        auto bbsFile = objManager->GetCommonScriptData(ScriptData_Effect);
        postFuncAddrBase = bbsFile->GetFuncAddrBase(funcName, bbsFile->m_PostFuncAddrTable.get());
    }
    else if (m_IsPlayerObj)
    {
        postFuncAddrBase = m_pBBSFile->GetFuncAddrBase(funcName, m_pBBSFile->m_PostFuncAddrTable.get());
        if (!funcAddrBase)
        {
            auto bbsFile = objManager->GetScriptData(m_SideID, m_MemberID, ScriptData_Effect);
            postFuncAddrBase = bbsFile->GetFuncAddrBase(funcName, bbsFile->m_PostFuncAddrTable.get());
        }
    }

    bool jumpDone = false;

    if (preFuncAddrBase && *(int32_t*)preFuncAddrBase == ID_PreFuncBegin)
    {
        for (auto i = preFuncAddrBase + 36; *(uint32_t*)i != ID_FuncEnd; i = ExecuteNestCommand(
                 i,
                 0,
                 &jumpDone,
                 true,
                 nullptr));
    }

    if (funcAddrBase && *(int32_t*)funcAddrBase == ID_FuncBegin)
    {
        for (auto i = funcAddrBase + 36; *(uint32_t*)i != ID_FuncEnd; i = ExecuteNestCommand(
                 i,
                 0,
                 &jumpDone,
                 true,
                 nullptr));
    }

    if (postFuncAddrBase && *(int32_t*)postFuncAddrBase == ID_PostFuncBegin)
    {
        for (auto i = postFuncAddrBase + 36; *(uint32_t*)i != ID_FuncEnd; i = ExecuteNestCommand(
                 i,
                 0,
                 &jumpDone,
                 true,
                 nullptr));
    }

    return 0;
}

int OBJ_CBase::FuncCallBySwitchCaseTable(uint8_t* addr)
{
    m_TmpArgAddr = addr;
    auto id = *(BBS_COMMAND_ID*)addr;
    auto obj = this;
    if (m_pControlObject && id != ID_ControlObjectEnd) obj = m_pControlObject;

    switch (id)
    {
    case ID_ActionBegin:
        obj->ActionBegin(*(const CXXBYTE<32>*)(addr + 4));
        return 0;
    case ID_ActionEnd:
        return 0;
    case ID_CellBegin:
        obj->CellBegin(*(const CXXBYTE<32>*)(addr + 4), *(int32_t*)(addr + 36));
        return 0;
    case ID_Goto:
        obj->Goto(*(const CXXBYTE<32>*)(addr + 4));
        return 0;
    case ID_InitCharName:
        obj->InitCharName(*(const CXXBYTE<16>*)(addr + 4));
        return 0;
    default:
        return 0;
    }
}

uint8_t* OBJ_CBase::GetSkipBeginEndAddr(uint8_t* addr)
{
    int nestLv = 0;
    do
    {
        auto beginEnd = BeginEndList;
        bool beginEndFound = true;
        while (*(uint32_t*)beginEnd != *(uint32_t*)addr)
        {
            if ((int64_t)++beginEnd >= (int64_t)&BeginEndList + 0x88)
            {
                beginEndFound = false;
            }
        }

        auto nestAdd = nestLv + 1;

        auto end = &BeginEndList[0][1];

        if (beginEndFound == false)
        {
            nestAdd = nestLv;
        }

        bool endFound = true;

        while (*end != *(int32_t*)addr)
        {
            end += 2;
            if (end >= &BeginEndList[0][1] + 0x88)
            {
                endFound = false;
            }
        }

        addr += commandSizeTable[*(int32_t*)addr];
        if (endFound)
            nestLv = nestAdd;
        else nestLv = nestAdd - 1;
    }
    while (nestLv);
    return addr;
}

uint8_t* OBJ_CBase::GetActionAddr(const CXXBYTE<32> actionName, int* pOutIndex)
{
    auto s = actionName;
    if (actionName.GetStr()[0] == '_')
    {
        auto contextActionName = GetContextActionName(actionName);
        if (contextActionName) s = contextActionName;
    }

    auto hash = AA_MakeHash(s.GetStr());
    const auto key = new CHashKey();
    key->SetKey(hash);

    auto node = m_pBBSFile->m_ActIndexTable->SearchNode(key);

    if (!node || &m_pBBSFile->m_ScriptTopAddr[node->GetData()] == nullptr)
    {
        hash = AA_MakeHash(AN_CmnActStand.GetStr());
        key->SetKey(hash);

        node = m_pBBSFile->m_ActIndexTable->SearchNode(key);

        m_ActionRequestInfo.m_RequestName = AN_CmnActStand;
    }

    return &m_pBBSFile->m_ScriptTopAddr[node->GetData()];
}

const char* OBJ_CBase::GetContextActionName(const CXXBYTE<32>& actName)
{
    return nullptr;
}

void OBJ_CBase::FuncCall(const CXXBYTE<32>& funcName)
{
    const auto objManager = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene())->
        GetBattleObjectManager();
    objManager->PushFuncCallArg(0, 0, 0, 0);
    auto tmpReg = m_TmpReg;
    m_TmpReg = 0;
    ExecuteFunctionBlock(funcName);
    m_TmpReg = tmpReg;
    objManager->PopFuncCallArg();
}

void OBJ_CBase::SetPosXRawinBattle(int val)
{
    m_PosX = val;

    const auto battleScene = dynamic_cast<SCENE_CBattle*>(REDGameCommon::GetInstance()->GetScene());
    m_PosX += 1000 * battleScene->GetBattleScreenManager()->GetWorldSideMove() * battleScene->GetBattleScreenManager()->
        GetWorldSideMoveValue();
}

void OBJ_CBase::WorldCollision(int on)
{
    m_ObjFlag |= OBJ_FLG_PUSH_OBJ2WRLD;
    if (!on)
        m_ObjFlag &= ~OBJ_FLG_PUSH_OBJ2WRLD;
}

void OBJ_CBase::ScreenCollision(int on)
{
    m_ObjFlag |= OBJ_FLG_PUSH_OBJ2SCRN;
    if (!on)
        m_ObjFlag &= ~OBJ_FLG_PUSH_OBJ2SCRN;
}

void OBJ_CBase::CommonSE(const CXXBYTE<32>& name)
{
    // TODO soundrequestforobj
    m_SoundReq.m_Volume = 100;
    m_SoundReq.m_Channel = 0;
    m_SoundReq.m_Pitch = 100;
    m_SoundReq.m_RandomChannel = -1;
    m_SoundReq.m_Bank = SND_BANK_INVALID;
}

void OBJ_CBase::Voice(const CXXBYTE<16>& name)
{
    if (!IsDead() && (m_VoiceInfo.m_IgnoreForceVoicePlay || m_VoiceInfo.m_ForceVoicePlay))
    {
        // TODO soundrequestforobj
        m_SoundReq.m_Volume = 100;
        m_SoundReq.m_Channel = 0;
        m_SoundReq.m_Pitch = 100;
        m_SoundReq.m_RandomChannel = -1;
        m_SoundReq.m_Bank = SND_BANK_INVALID;
    }
}

void OBJ_CBase::InitCharName(const CXXBYTE<16>& name)
{
    ((OBJ_CCharBase*)m_pParentPly.GetPtr())->m_CharName = name;
}

void OBJ_CBase::ResetAirDashCount()
{
    auto ply = (OBJ_CCharBase*)m_pParentPly.GetPtr();
    ply->m_AirDashCount = ply->ply_AirDashCountMax;
}

void OBJ_CBase::ResetAirJumpCount()
{
    auto ply = (OBJ_CCharBase*)m_pParentPly.GetPtr();
    ply->m_AirJumpCount = ply->ply_AirJumpCountMax;
}

void OBJ_CBase::ZLine(ZLINE line, ZLINE_LEVEL level)
{
    ZLINE newLine = ZLINE_NEAR;
    if (line == ZLINE_NEAR)
    {
        line = ZLINE_FAR;
    }
    if (m_IsPlayerObj)
    {
        if (level >= m_pTargetObj.GetPtr()->m_ZLevel || line != m_pTargetObj.GetPtr()->m_ZLine)
        {
            m_ZLine = line;
            m_ZLevel = level;
            if (line == m_pTargetObj.GetPtr()->m_ZLine && m_pTargetObj.GetPtr()->m_ZLevel < ZLL_LVMAX)
            {
                auto player = GetMainPlayerBase(m_SideID);
                m_ZLevel = ZLL_LV0;
                if (player == this)
                    m_ZLevel = ZLL_LV3;
                m_ZLine = newLine;
            }
        }
    }
    else
    {
        m_ZLine = line;
        m_ZLevel = level;
    }
}

void OBJ_CBase::RequestKoware(CO_TYPE obj)
{
    auto co = GetControlObject(obj);

    if (co != nullptr && co->m_KowareCur == 0)
    {
        if (co->m_IsPlayerObj)
        {
            ((OBJ_CCharBase*)co)->DelAttackFlag(PLATK_FLEXCANCEL);
            co->m_CollisionFlag &= ~OBJ_CLSN_CHAIN_READY;
        }

        co->m_ActionFlag &= ~OBJ_ACT_COUNTER_UKERU;
        co->m_ActionFlag |= OBJ_ACT_ATTACK_END;
        co->DoInterrupt(ON_KOWARE);
        co->m_ValidInterruptFlag[0][1].Del(0x2000);
        co->m_ValidInterruptFlag[1][1].Del(0x2000);
        co->m_ValidInterruptFlag[2][1].Del(0x2000);
        co->m_ValidInterruptFlag[3][1].Del(0x2000);
        co->m_ValidInterruptFlag[4][1].Del(0x2000);
        co->m_KowareDone = true;
        co->m_ValidInterruptFlag[0][0].Del(0x4);
        co->m_ValidInterruptFlag[1][0].Del(0x4);
        co->m_ValidInterruptFlag[2][0].Del(0x4);
        co->m_ValidInterruptFlag[3][0].Del(0x4);
        co->m_ValidInterruptFlag[4][0].Del(0x4);
        co->m_ValidInterruptFlag[0][0].Del(0x20);
        co->m_ValidInterruptFlag[1][0].Del(0x20);
        co->m_ValidInterruptFlag[2][0].Del(0x20);
        co->m_ValidInterruptFlag[3][0].Del(0x20);
        co->m_ValidInterruptFlag[4][0].Del(0x20);
    }
}
