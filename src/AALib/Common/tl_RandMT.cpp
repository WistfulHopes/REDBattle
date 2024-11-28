#include "tl_RandMT.h"

AA_CRandMT s_Rand {};

bool AA_CRandMT::Init(uint32_t start)
{
    m_State[0] = start / 10000 % 1000;

    auto state = &m_State[1];

    for (int i = 1; i < 624; i++)
    {
        *state = i + 1812433253 * (*(state - 1) ^ *(state - 1) >> 30);
    }

    m_Left = 1;
    m_Initf = 1;

    return true;
}

uint32_t AA_CRandMT::GenU32()
{
    // TODO rand
    if (m_Left-- == 1)
    {

    }
    return 0;
}

AA_CRandMT::AA_CRandMT()
{
    for (auto& state : m_State)
    {
        state = 0;
    }    
    m_Left = 1;
    m_Initf = 0;
    m_pNext = nullptr;
}
