#include "obj_Base.h"
#include <cstring>
#include <intrin.h>
#include <Game/Scene/scene_Battle.h>

#include "obj_Flag.h"
#include "Char/char_Base.h"

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

bool OBJ_CBase::ActionRequestForce(const class CXXBYTE<32>& actionName)
{
    return ActionRequestEx(actionName, 9, nullptr, CXXBYTE<32>(""), 0);
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

uint32_t OBJ_CBase::GetObjDir()
{
    const OBJ_CBase* finalObj = this;
    for (auto i = m_pLinkObject_Direction.GetPtr(); i; i = i->m_pLinkObject_Direction.GetPtr())
        finalObj = i;

    return finalObj->m_Direction;
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
        bool isIfBegin = command == ID_IfBegin || (command - 6) <= ID_CheckTeamMemberName &&
            _bittest64((const __int64*)&bits, (unsigned __int16)(command - 6))
            || (command - ID_IfBeginCoType) <= 2
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
        addr = m_GotoForLoopAddr;
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
    // TODO implement instructions
    return 0;
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

void OBJ_CBase::CommonSE(const class CXXBYTE<32>& name)
{
    // TODO soundrequestforobj
    m_SoundReq.m_Volume = 100;
    m_SoundReq.m_Channel = 0;
    m_SoundReq.m_Pitch = 100;
    m_SoundReq.m_RandomChannel = -1;
    m_SoundReq.m_Bank = SND_BANK_INVALID;
}

void OBJ_CBase::Voice(const class CXXBYTE<16>& name)
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