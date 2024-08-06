#include "obj_Base.h"

#include <cstring>

bool OBJ_CBase::ActionRequestForce(const class CXXBYTE<32>& actionName)
{
    return ActionRequestEx(actionName, 9, nullptr, CXXBYTE<32>(""), 0);
}

bool OBJ_CBase::ActionRequestEx(const CXXBYTE<32>& actionName, unsigned int flag, OBJ_CBase* pEnemy, CXXBYTE<32> label, unsigned int reqFlag)
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
