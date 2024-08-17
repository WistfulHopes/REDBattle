#include "AALib/Common/cmn_typedef.h"

void CCmnRect::Normalize() 
{
    if (m_W < 0)
    {
        m_X += m_W;
        m_W = -m_W;
    }
    if (m_H < 0)
    {
        m_Y += m_H;
        m_H = -m_H;
    }
}