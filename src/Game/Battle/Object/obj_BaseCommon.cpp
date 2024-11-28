#include "obj_BaseCommon.h"

void CFloatWithTimer::Init()
{
    m_Val = 0;
    m_BeginVal = 0;
    m_DestVal = 0;
    m_DestTimer = 0;
    m_DestTimerMax = 0;
    m_bSet = false;
    m_bPause = false;
}

void CFloatWithTimer::SetVal(float beginVal, float destVal, int time)
{
    if (time)
        m_Val = beginVal;
    else
        m_Val = destVal;

    m_BeginVal = beginVal;
    m_DestVal = destVal;
    m_DestTimer = 0;
    m_DestTimerMax = time;
    m_bSet = true;
}
